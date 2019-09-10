import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

global survived
global titanic
'''
功能说明：           统计生还和遇难的总人数和占比的基本情况统计
'''
def overview(show = True):
    survivedNum = titanic["Survived"].sum()
    unsurvivedNum = titanic["Survived"].count() - survivedNum
    print("生还 %d 人，遇难 %d 人" % (survivedNum, unsurvivedNum))

    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Survived', data=titanic, order=[0, 1])
    plt.xlabel("是否生还")
    plt.ylabel("人数")
    plt.title('生还与遇难人数基本情况统计')

    plt.subplot(122)
    plt.pie([unsurvivedNum, survivedNum], \
        explode=(0, 0.05),                              # 添加突出
        startangle=180,                                 # 开始绘图的角度
        shadow=True,                                    # 是否有阴影
        labeldistance=0.75,                             # 文本位置
        labels=['遇难', '生还'],
        autopct='%1.1f%%')                              # 数据标签
    plt.title('生还与遇难人数占比统计')

    if show:
        plt.show()
    else:
        fig.savefig("titanic_overview.png")

'''
功能说明:       研究客舱级别对生还率的影响
'''
def PclassFact(show = True):
    # 不同级别客舱的人数和比例
    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Pclass', data=titanic)
    plt.xlabel("级别")
    plt.ylabel("人数")
    plt.title('海难发生前各级别客舱人数情况')

    plt.subplot(122)
    plt.pie(titanic[['Pclass', 'Survived']].groupby(['Pclass']).count(),\
            labels=['1', '2', '3'], autopct='%0.1f%%')
    plt.title("海难发生前各级别客舱人数占比统计")
    print("海难发生前各客舱人数总计和占比\n", \
          titanic[['Pclass', 'Survived']].groupby("Pclass").count())
    if show:
        plt.show()
    else:
        fig.savefig("titanic_pclass_fact0.png")

    # 不同级别客舱生还人数和占总生还人数的比例
    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Pclass', data=survived)
    plt.xlabel("级别")
    plt.ylabel('生还人数')
    plt.title('客舱级别与生还人数之间的关系')

    plt.subplot(122)
    plt.pie(survived[['Pclass', 'Survived']].groupby(['Pclass']).sum(),
            labels=['1', '2', '3'], autopct='%.1f%%')
    plt.title('客舱级别与生还人数占比统计')
    print("客舱级别与生还人数\n",\
          titanic[['Pclass', 'Survived']].groupby(['Pclass']).sum())
    if show:
        plt.show()
    else:
        fig.savefig("titanic_pclass_fact1.png")


    # 不同客舱分别的生还和遇难人数及占比
    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x="Pclass", hue='Survived', data=titanic)
    plt.xlabel("级别")
    plt.ylabel("人数")
    plt.title('级别与是否生还人数情况统计')

    plt.subplot(122)
    sns.barplot(x="Pclass", y='Survived', data=titanic,\
                ci=0)               # 允许的误差的范围,0到100的float
    plt.xlabel("级别")
    plt.ylabel("生还人数占比")
    plt.title("各级别生还人数占相应级别总数情况")
    print("各级别生还人数占相应级别总数情况\n",
          titanic.groupby("Pclass")["Survived"].mean())
    if show:
        plt.show()
    else:
        fig.savefig("titanic_pclass_fact2.png")
'''
功能说明:       研究性别对生还率的影响
'''
def sexFact(show = True):
    # 海难发生前，男女数量及男女比例
    maleNum = titanic['Sex'][titanic['Sex'] == 'male'].count()
    femaleNum = titanic['Sex'][titanic['Sex'] == 'female'].count()
    print("海难发生前，男性 %d, 女性 %d" % (maleNum, femaleNum))

    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Sex', data=titanic)
    plt.xlabel("性别")
    plt.ylabel("人数")
    plt.title("海难发生前，男女数量")

    plt.subplot(122)
    plt.pie([maleNum, femaleNum], \
            labels=['男性', '女性'], autopct='%.1f%%')
    plt.title("海难发生前，男女占比")
    if show:
        plt.show()
    else:
        fig.savefig("titanic_sex_fact0.png")

    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Sex', hue="Survived", data=titanic)
    plt.xlabel("性别")
    plt.ylabel("生还人数")
    plt.title("海难发生后，性别与是否生还统计关系")

    plt.subplot(122)
    sns.barplot(x="Sex", y='Survived', data=titanic, ci=0)
    plt.xlabel("性别")
    plt.ylabel("生还人数占比")
    plt.title("海难发生后，性别与生还人数占比")
    print("性别与生还人数总数和占比\n", \
          titanic[['Sex', 'Survived']].groupby(['Sex']).sum(),
          titanic[['Sex', 'Survived']].groupby(['Sex']).mean())
    if show:
        plt.show()
    else:
        fig.savefig("titanic_sex_fact1.png")

'''
功能说明:       研究年纪对生还率的影响
'''
def ageFact(show = True):
    # 研究年龄和生还率之间的关系
    '''
    年龄缺失值处理
    '''
    # 年龄中缺失值较多，首先对缺失值处理，填充的年龄为年龄平均值的上下一个标准差范围内的随机数。
    # 求年龄的平均值，标准差以及丢失值的数量
    average_age_titanic = titanic["Age"].mean()
    std_age_titanic = titanic["Age"].std()
    count_nan_age_titanic = titanic["Age"].isnull().sum()
    # 求年龄随机数，范围在 (mean - std, mean + std)
    rand_1 = np.random.randint(average_age_titanic - std_age_titanic, \
        average_age_titanic + std_age_titanic,\
        size=count_nan_age_titanic)
    # 将随机数填充进 Age 的丢失值中
    titanic["Age"][np.isnan(titanic["Age"])] = rand_1.copy()

    '''
    绘制年龄分布
    '''
    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    titanic['Age'].hist(bins=70)
    plt.xlabel('年龄')
    plt.ylabel('人数')
    plt.title("年龄分布直方图")

    plt.subplot(122)
    titanic.boxplot(column='Age', showfliers=False)
    plt.title("年龄分布箱线图")
    if show:
        plt.show()
    else:
        fig.savefig("titanic_age_fact0.png")
    print(titanic['Age'].describe())


    '''
    按照年龄，将乘客划分为儿童、少年、成年人和老年人，分析四个群体生还情况
    '''
    ageBins = [0, 12, 18, 65, 100]
    titanic["ageGroup"] = pd.cut(titanic["Age"], ageBins)
    ageGroupsRate = titanic.groupby("ageGroup")["Survived"].mean()
    ageGroupsRate.index = ['儿童', '少年', '成年人', '老年人']
    ageGroupsNum = titanic.groupby("ageGroup")["Survived"].sum()
    ageGroupsNum.index = ['儿童', '少年', '成年人', '老年人']

    fig = plt.figure(figsize=(12, 5))
    plt.subplot(121)
    ageGroupsNum.plot(kind="bar", title='四个年龄群体生还人数')

    plt.subplot(122)
    ageGroupsRate.plot(kind="bar", title='四个年龄群体生还率')
    print(ageGroupsNum, ageGroupsRate)
    if show:
        plt.show()
    else:
        fig.savefig("titanic_age_fact1.png")

def sibSpFact(show = True):
    # 分为有兄弟姐妹和没有兄弟姐妹两组
    titanic["hasSibSp"] = titanic['SibSp'] != 0

    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x="hasSibSp", hue="Survived", data=titanic)
    plt.xlabel("是否有兄弟姐妹")
    plt.ylabel("人数")
    plt.title("是否有兄弟姐妹和生还的关系")

    # 有兄弟姐妹的乘客的生还人数和生还率
    plt.subplot(122)
    sns.barplot(x="hasSibSp", y="Survived", data=titanic, ci=0)
    plt.xlabel("是否有兄弟姐妹")
    plt.ylabel("占比")
    plt.title("是否有兄弟姐妹和生还率统计关系")
    print(titanic[["hasSibSp", "Survived"]].groupby("hasSibSp").count(),
          titanic[["hasSibSp", "Survived"]].groupby("hasSibSp").sum(),
          titanic[["hasSibSp", "Survived"]].groupby("hasSibSp").mean())
    if show:
        plt.show()
    else:
        fig.savefig("titanic_slibsp_fact.png")

def parchFact(show = True, save = False):
    # 有父母子女的乘客的生还人数和生还率
    titanic["hasParch"] = titanic['Parch'] != 0
    fig = plt.figure(figsize=(10, 5))
    plt.subplot(121)
    ax = sns.countplot(x='hasParch', hue='Survived', data=titanic)
    ax.set_xlabel("是否有父母子女")
    ax.set_ylabel("人数")
    plt.title("是否有父母子女和是否生还人数关系")

    plt.subplot(122)
    ax = sns.barplot(x='hasParch', y='Survived', data=titanic, ci=0)
    ax.set_xlabel("是否有父母子女")
    ax.set_ylabel("生还率")
    plt.title("是否有父母子女和生还率关系")
    print(titanic[['hasParch', 'Survived']].groupby("hasParch").count(),
        titanic[['hasParch', 'Survived']].groupby("hasParch").sum(),
        titanic[['hasParch', 'Survived']].groupby("hasParch").mean())
    if show:
        plt.show()
    if save:
        fig.savefig("titanic_parch_fact.png")

def fareFact(show = True, save = False):
    print("Fare describe\n", titanic["Fare"].describe())

    # 票价分布
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 5))
    titanic['Fare'].hist(bins=70, ax=ax1)
    plt.title("票价分布")

    titanic.boxplot(column='Fare', by='Pclass',\
        showfliers=False, ax=ax2)
    plt.title("级别和票价之间的关系")
    if show:
        plt.show()
    if save:
        fig.savefig("titanic_fare_fact0.png")

    fig, axes = plt.subplots(1, 1)
    fare_not_survived = titanic["Fare"][titanic["Survived"] == 0]
    fare_survived = titanic["Fare"][titanic["Survived"] == 1]
    average_fare = pd.DataFrame([fare_not_survived.mean(), fare_survived.mean()])
    std_fare = pd.DataFrame([fare_not_survived.std(), fare_survived.std()])
    ax = average_fare.plot(yerr=std_fare, kind='bar', ax=axes, legend=False)
    ax.set_xlabel("是否生还")
    ax.set_title("是否生还和票价分布")
    if show:
        plt.show()
    if save:
        fig.savefig("titanic_fare_fact1.png")

def embarkedFact(show = True, save = False):
    #两个丢失值，用众数填充
    titanic["Embarked"] = titanic["Embarked"].fillna("S")

    # 各港口上船人数、生还人数及生还率
    fig, (axis1, axis2, axis3) = plt.subplots(1, 3, figsize=(20, 5))
    ax = sns.countplot(x='Embarked', data=titanic, ax=axis1)
    ax.set_xlabel("港口")
    ax.set_ylabel("人数")
    ax.set_title("海难发生前，各港口乘客人数")

    ax = sns.countplot(x='Embarked', hue="Survived", \
        data=titanic, order=['S', 'C', 'Q'], ax=axis2)
    ax.set_xlabel("港口")
    ax.set_ylabel("人数")
    ax.set_title("海难发生后，各港口是否生还乘客人数")

    embark_perc = titanic[["Embarked", "Survived"]].groupby(['Embarked'],\
        as_index=False).mean()
    sns.catplot(x='Embarked', y='Survived',\
        data=embark_perc, height=3, aspect=2,\
        ax=axis3, order=['S', 'C', 'Q'],\
        markers=["o"], linestyles=["--"], kind="point")

    print(embark_perc)
    if show:
        plt.show()
    if save:
        fig.savefig("titanic_embarked_fact1.png")

if __name__ == "__main__":
    sns.set(style="whitegrid")
    # 正常显示中文标签
    plt.rcParams['font.sans-serif'] = ['SimHei']
    # 正常显示负号
    plt.rcParams['axes.unicode_minus'] = False

    titanic = pd.read_csv("./data/titanic-data.csv")
    # 删除和生还无关的信息
    titanic.drop(["PassengerId", "Name", "Ticket"], axis=1)
    #print(titanic.info())
    '''    
    Cabin(204)、Embarked(889), Age(714)存在数据丢失
    '''
    # Cabin丢失数据太多，删除相关数据
    titanic.drop("Cabin", axis=1)
    survived = titanic[titanic['Survived'] == 1]
    overview()
    PclassFact()
    sexFact()
    ageFact()
    sibSpFact()
    parchFact()
    fareFact()
    embarkedFact()



