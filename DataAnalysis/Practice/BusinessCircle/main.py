import pandas as pd
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import linkage, dendrogram
from sklearn.cluster import AgglomerativeClustering            # 导入sklearn的层次聚类函数

plt.rcParams['font.sans-serif'] = ['SimHei']                   # 正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False                     # 正常显示负号

fileName = "./data/business_circle.xls"
data = pd.read_excel(fileName,
    index_col=u'基站编号')                                      # 指定索引列
# 无缺失值，无需特殊处理
# print(data.info())

# 数据标准化
normalisedData = (data-data.min())/(data.max()-data.min())
normalisedData.to_excel("./normalised_business_circle.xls")

# 模型构建
Z = linkage(data, method='ward', metric='euclidean')            # 谱系聚类图
P = dendrogram(Z, 0)                                            # 画谱系聚类图
plt.show()

# 层次聚类
k = 3                                                           # 定义聚类数
model = AgglomerativeClustering(n_clusters=k, linkage='ward')
model.fit(normalisedData)                                       # 训练模型

# 详细输出原始数据及其类别
r = pd.concat([normalisedData, pd.Series(model.labels_,
    index=normalisedData.index)], axis=1)                       # 详细输出每个样本对应的类别
r.columns=list(normalisedData.columns)+[u'聚类类别']              # 重命名表头

style = ['ro-', 'go-', 'bo-']
xlabels = [u'工作日人均停留时间', u'凌晨人均停留时间', u'周末人均停留时间', u'日均人流量']
pic_output = './type_'  # 聚类图文件名前缀

for i in range(k):  # 逐一作图，作出不同样式
    plt.figure()
    tmp = r[r[u'聚类类别'] == i].iloc[:, :4]  # 提取每一类
    for j in range(len(tmp)):
        plt.plot(range(1, 5), tmp.iloc[j], style[i])

    plt.xticks(range(1, 5), xlabels, rotation=20)  # 坐标标签
    plt.title(u'商圈类别%s' % (i + 1))  # 我们计数习惯从1开始
    plt.subplots_adjust(bottom=0.15)  # 调整底部
    plt.savefig(u'%s%s.png' % (pic_output, i + 1))  # 保存图片