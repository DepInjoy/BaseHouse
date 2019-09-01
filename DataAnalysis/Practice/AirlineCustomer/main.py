import os
import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

'''
数据探索，根据RFM模型重点关注的参数
    会员卡号:               MEMBER_NO
    入会时间:               FFP_DATE
    飞行次数:               FLIGHT_COUNT
    总飞行公里数:            SEG_KM_SUM
    平均折扣率:              avg_discount
    第一年总票价:            SUM_YR_1
    第二年总票价:            SUM_YR_2
    平均乘机间隔:            AVG_INTERVAL
    观察窗口内最大乘机间隔:    MAX_INTERVAL
'''
def explore(data, save = False):
    exploredDataFile = "./tmp/explored_airline_customer_data.xls"
    explore = data.describe(include="all").T
    #计算缺失值的个数
    explore["null"] = len(data) - explore["count"]
    if not save:
        return
    if not os.path.exists("./tmp"):
        os.mkdir("./tmp")
    # 将筛选部分探索结果保存至excel文件，便于分析
    explore = explore[["min", "max", "null"]]
    explore.to_excel(exploredDataFile)
    '''
    观察探索结果可以看到：
    SUM_YR_1和SUM_YR_2分别有551和138个空值，且两者的最小值都是0
    SEG_KM_SUM的最小值为368，FLIGHT_COUNT的最小值为2，avg_discount的最小值也是0
    票价为0，总飞行公里数大于0且平均折扣率不为0的数据异常
    '''

'''
数据清洗
'''
def clean(data, save = False):
    data = data[data["SUM_YR_1"].notnull() & data["SUM_YR_2"].notnull()]
    flag1 = data["SUM_YR_1"] != 0
    flag2 = data["SUM_YR_2"] != 0
    flag3 = (data["SEG_KM_SUM"] == 0) & (data["avg_discount"] == 0)
    data = data[flag1 | flag2 | flag3]
    if save:
        if not os.path.exists("./tmp"):
            os.mkdir("./tmp")
        data.to_excel("./tmp/cleaned_data.xls")
    return data

'''
特征属性构造
    L:
        入会时间:                                 FFP_DATE
        观测窗口结束时间：                          LOAD_TIME
    R:
        最后一次乘机时间至观察窗口末端时长(月):        LAST_TO_END
    F:
        飞行次数:                                 FLIGHT_COUNT
    M:
        平均折扣率:                               avg_discount
        总飞行公里数:                             SEG_KM_SUM
'''
def makeAttr(data, save = False):
    data["FFP_DATE"] = pd.to_datetime(data["FFP_DATE"])
    data["LOAD_TIME"] = pd.to_datetime(data["LOAD_TIME"])
    data["入会时间"] = data["LOAD_TIME"] - data["FFP_DATE"]
    filteredData = data.rename(
        columns = {
            "FLIGHT_COUNT"  : "飞行次数",
            "avg_discount"  : "平均折扣率",
            "SEG_KM_SUM"    : "总飞行公里数",
            "LAST_TO_END"   : "最近乘坐间隔",
            "MEMBER_NO"     : "会员卡号"
        },
        inplace = False
    )
    # 入会时间的数据类型为timedelta64[ns],L R F M C
    filteredData = filteredData[["入会时间", "最近乘坐间隔",
        "飞行次数", "总飞行公里数", "平均折扣率"]]
    # 将入会时间隔转化为月
    filteredData["入会时间"] = filteredData["入会时间"].astype(np.int64) / (30*60*60*24*10**9)
    if save:
        if not os.path.exists("./tmp"):
            os.mkdir("./tmp")
        filteredData.to_excel("./tmp/score_data.xls")
    return filteredData

'''
    数据标准化
'''
def normalise(data, save = False):
    zscoredData = (data - data.mean(axis = 0)) / data.std(axis = 0)
    if save:
        if not os.path.exists("./tmp"):
            os.mkdir("./tmp")
        zscoredData.to_excel("./tmp/scored_data.xls")
    return zscoredData

'''
研究簇数K对计算SSE的影响
'''
def testKmeansNClusters(data, startIndex = 2, endIndex = 11):
    # 存放设置不同簇数时的SSE值
    distortions = []
    for i in range(startIndex, endIndex):
        km = KmeanClusters(data, i)
        # 获取K-means算法的SSE
        distortions.append(km.inertia_)
    # 绘制曲线
    plt.plot(range(startIndex, endIndex), distortions, marker="o")
    plt.xlabel("簇数量")
    plt.ylabel("簇内误方差(SSE)")
    plt.show()

'''
调用K-Mean算法，进行聚类分析
    @:param k:                  聚类类别数
'''
def KmeanClusters(data, k):
    '''
    n_clusters:     设置簇的个数
    init:           使用Kmeans算法，默认是k-means++,还支持random
    n_init:         设置初始样本中心的个数
    max_iter:       设置最大迭代次数
    tol:            设置算法的容错范围SSE(簇内误平方差)
    n_jobs:         并行数，一般等于CPU数较好
    '''
    kmodel = KMeans(n_clusters=k, n_jobs = 4, init="k-means++")
    '''
                n_init=10, max_iter=500,
                tol=1e-04, random_state=0
    '''
    # 训练模型
    kmodel.fit(data)
    return kmodel
'''
绘制特征雷达图
'''
def plotRadar(kmodel, data):
    labels = data.columns  # 标签
    plot_data = kmodel.cluster_centers_
    colors= ['#2De1C2', '#ED254E', '#FFAF87', '#399E5A', '#256EFF', '#573280']
    # 设置雷达图角度，来平分切开圆面
    angles = np.linspace(0, 2*np.pi, len(labels), endpoint=False)
    # 使得雷达图闭合起来
    plot_data = np.concatenate((plot_data, plot_data[:, [0]]), axis=1)
    angles = np.concatenate((angles, [angles[0]]))

    fig = plt.figure()
    ax = fig.add_subplot(111, polar=True)
    for i in range(len(plot_data)):
        ax.plot(angles, plot_data[i], 'o-', color=colors[i], label=u'第%d簇顾客群' % (i + 1), linewidth=2)  # 画线
        ax.fill(angles, plot_data[i], color=colors[i], alpha=0.5)
        plt.title('客户群特征分析图', fontsize=20)
    ax.set_rgrids(np.arange(0.01, 3.5, 0.5), np.arange(-1, 2.5, 0.5), fontproperties="SimHei")
    ax.set_thetagrids(angles * 180 / np.pi, labels, fontproperties="SimHei")
    plt.legend(loc=4)
    plt.show()

def saveResult(data, kmodel):
    # 统计各个类别的数目
    r1 = pd.Series(kmodel.labels_).value_counts()
    # 找出聚类中心
    r2 = pd.DataFrame(kmodel.cluster_centers_)
    # 横向连接（0是纵向），得到聚类中心对应的类别下的数目
    r = pd.concat([r2, r1], axis=1)
    # 重命名表头
    r.columns = list(data.columns) + [u'类别数目']

    # 详细输出原始数据及其类别
    r = pd.concat([data, pd.Series(kmodel.labels_, index=data.index)], axis=1)
    r.columns = list(data.columns) + [u'聚类类别']  # 重命名表头
    if not os.path.exists("./out"):
        os.mkdir("./out")
    r.to_excel("./out/trained_data.xls")  # 保存结果

if __name__ == "__main__":
    # 正常显示中文标签
    plt.rcParams['font.sans-serif'] = ['SimHei']
    # 正常显示负号
    plt.rcParams['axes.unicode_minus'] = False
    inputDataFile = "./data/airline_customer_data.csv"
    data = pd.read_csv(inputDataFile, encoding="utf-8")
    #explore(data)
    data = clean(data)
    filteredData = makeAttr(data)
    normalisedData = normalise(filteredData)
    if not os.path.exists("./tmp"):
        os.mkdir("./tmp")
    normalisedData.to_excel("./tmp/scored_data.xls")
    #testKmeansNClusters(normalisedData)
    for i in range(4, 7):
        kmodel = KmeanClusters(normalisedData, i)
        plotRadar(kmodel, normalisedData)
        saveResult(normalisedData, kmodel)
