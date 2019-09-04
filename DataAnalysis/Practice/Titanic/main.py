import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

global survived
global titanic
'''
功能说明：           统计生还和遇难的总人数和占比的基本情况统计
'''
def overview():
    survivedNum = titanic["Survived"].sum()
    unsurvivedNum = titanic["Survived"].count() - survivedNum
    print("生还 %d 人，遇难 %d 人" % (survivedNum, unsurvivedNum))

    plt.figure(figsize=(10, 5))
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
    plt.show()

'''
功能说明:       研究客舱级别对生还率的影响
'''
def PclassFact():
    # 不同级别客舱的人数和比例
    plt.figure(figsize=(10, 5))
    plt.subplot(221)
    sns.countplot(x='Pclass', data=titanic)
    plt.xlabel("级别")
    plt.ylabel("人数")
    plt.title('海难发生前各级别客舱人数情况')

    plt.subplot(222)
    plt.pie(titanic[['Pclass', 'Survived']].groupby(['Pclass']).count(),
            labels=['1', '2', '3'], autopct='%1.0f%%')
    plt.show()

    # 不同级别客舱生还人数和占总生还人数的比例
    survived[['Pclass', 'Survived']].groupby(['Pclass']).sum()

    plt.figure(figsize=(10, 5))
    plt.subplot(223)
    sns.countplot(x='Pclass', data=survived)
    plt.xlabel("级别")
    plt.ylabel('生还人数')
    plt.title('级别与生还人数之间的关系')

    plt.subplot(224)
    plt.pie(survived[['Pclass', 'Survived']].groupby(['Pclass']).sum(),
            labels=['1', '2', '3'], autopct='%1.0f%%')
    plt.show()

    # 不同客舱分别的生还和遇难人数及占比
    pclass1 = titanic[titanic['Pclass'] == 1]
    pclass2 = titanic[titanic['Pclass'] == 2]
    pclass3 = titanic[titanic['Pclass'] == 3]

    plt.figure(figsize=(10, 20))
    plt.subplot(421)
    sns.countplot(x='Survived', data=pclass1)
    plt.xlabel("是否生还")
    plt.ylabel("人数")
    plt.title('1级别生还与遇难人数情况')

    plt.subplot(422)
    plt.pie([pclass1['Survived'][pclass1['Survived'] == 0].count(), \
        pclass1['Survived'][pclass1['Survived'] == 1].count()], \
        labels=['遇难', '生还'], autopct='%1.0f%%')

    plt.subplot(423)
    sns.countplot(x='Survived', data=pclass2)
    plt.xlabel("是否生还")
    plt.ylabel("人数")
    plt.title('2级别生还与遇难人数情况')

    plt.subplot(424)
    plt.pie([pclass2['Survived'][pclass2['Survived'] == 0].count(), \
        pclass2['Survived'][pclass2['Survived'] == 1].count()], \
        labels=['遇难', '生还'], autopct='%1.0f%%')

    plt.subplot(425)
    sns.countplot(x='Survived', data=pclass3)
    plt.xlabel("是否生还")
    plt.ylabel("人数")
    plt.title('3级别生还与遇难人数情况')

    plt.subplot(426)
    plt.pie([pclass3['Survived'][pclass3['Survived'] == 0].count(), \
        pclass3['Survived'][pclass3['Survived'] == 1].count()], \
        labels=['遇难', '生还'], autopct='%1.1f%%')

    plt.subplot(427)
    survived_by_pclass = titanic.groupby('Pclass')['Survived'].mean()
    ax = survived_by_pclass.plot(kind='bar', x="级别",\
        title="各级别生还人数占相应级别总数情况")
    ax.set_xlabel("级别")
    plt.show()
'''
功能说明:       研究性别对生还率的影响
'''
def sexFact():
    # 生还的男女数量及男女比例
    survivedMaleNum = survived['Sex'][survived['Sex'] == 'male'].count()
    survivedFemaleNum = survived['Sex'][survived['Sex'] == 'female'].count()
    print("生还男性 %d, 女性 %d" % (survivedMaleNum, survivedFemaleNum))

    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Sex', data=survived)
    plt.xlabel("性别")
    plt.ylabel("生还人数")
    plt.title("生还者中男女数量")

    plt.subplot(122)
    plt.pie([survivedMaleNum, survivedFemaleNum], \
            labels=['男性', '女性'], autopct='%1.0f%%')
    plt.title("生还者中男女占比")
    plt.show()


    # 男性的生还数量及生还率
    male = titanic[titanic['Sex'] == 'male']

    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Survived', data=male)
    plt.xlabel("是否生还")
    plt.ylabel("人数")
    plt.title("男性中生还与遇难人数")

    plt.subplot(122)
    plt.pie([male['Survived'][male['Survived'] == 0].count(), \
        male['Survived'][male['Survived'] == 1].count()], \
        labels=['遇难', '生还'], autopct='%1.0f%%')
    plt.show()

    # 女性的生还数量及生还率
    female = titanic[titanic["Sex"] == "female"]
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x="Survived", data=female)
    plt.xlabel("是否生还")
    plt.ylabel("人数")
    plt.title("女性中生还与遇难人数")

    plt.subplot(122)
    plt.pie([female["Survived"][female["Survived"] == 0].count(), \
            female["Survived"][female["Survived"] == 1].count()], \
            labels=['遇难', '生还'], autopct='%1.0f%%')
    plt.show()

    survived_by_sex = titanic.groupby('Sex')['Survived'].mean()
    survived_by_sex.plot(kind='bar')
    plt.show()

'''
功能说明:       研究年纪对生还率的影响
'''
def ageFact():
    # 研究年龄和生还率之间的关系

    # 年龄中缺失值较多，首先对缺失值处理，填充的年龄为年龄平均值的上下一个标准差范围内的随机数。
    # 求年龄的平均值，标准差以及丢失值的数量
    average_age_titanic = titanic["Age"].mean()
    std_age_titanic = titanic["Age"].std()
    count_nan_age_titanic = titanic["Age"].isnull().sum()
    # 求年龄随机数，范围在 (mean - std， mean + std)
    rand_1 = np.random.randint(average_age_titanic - std_age_titanic, \
        average_age_titanic + std_age_titanic,\
        size=count_nan_age_titanic)
    # 将随机数填充进 Age 的丢失值中
    titanic["Age"][np.isnan(titanic["Age"])] = rand_1.copy()

    '''
    绘制年龄分布
    '''
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    titanic['Age'].hist(bins=70)
    plt.xlabel('年龄')
    plt.ylabel('人数')

    plt.subplot(122)
    titanic.boxplot(column='Age', showfliers=False)
    plt.show()
    #print(titanic['Age'].describe())
    '''
    count    891.000000
    mean      29.354848
    std       13.518461
    min        0.420000
    25%       20.250000
    50%       28.000000
    75%       37.000000
    max       80.000000
    '''


    '''
    按照年龄，将乘客划分为儿童、少年、成年人和老年人，分析四个群体生还情况
    '''
    children = titanic[titanic['Age'] <= 12]
    juvenile = titanic[(titanic['Age'] > 12) & (titanic['Age'] < 18)]
    adults = titanic[(titanic['Age'] >= 18) & (titanic['Age'] < 65)]
    agedness = titanic[titanic['Age'] >= 65]

    # 各年龄段生还人数
    children_survived_sum = children['Survived'].sum()
    juvenile_survived_sum = juvenile['Survived'].sum()
    adults_survived_sum = adults['Survived'].sum()
    agedness_survived_sum = agedness['Survived'].sum()
    print("儿童、少年、成年人、老年人")
    print(children_survived_sum, juvenile_survived_sum, adults_survived_sum, agedness_survived_sum)

    # 各年龄段生还率
    children_survived_rate = children["Survived"].mean()
    juvenile_survived_rate = juvenile['Survived'].mean()
    adults_survived_rate = adults['Survived'].mean()
    agedness_survived_rate = agedness['Survived'].mean()
    print(children_survived_rate, juvenile_survived_rate, adults_survived_rate, agedness_survived_rate)

    x = ['儿童', '少年', '成年人', '老年人']
    b = [children_survived_sum, juvenile_survived_sum, adults_survived_sum, agedness_survived_sum]
    y = [children_survived_rate, juvenile_survived_rate, adults_survived_rate, agedness_survived_rate]
    plt.figure(figsize=(12, 5))
    plt.subplot(121)
    # 画条
    x_pos = list(range(len(x)))
    rects = plt.bar(x_pos, b, align='center', alpha=0.5)
    # 标签
    def autolabel(rects):
        for ii, rect in enumerate(rects):
            height = rect.get_height()
            plt.text(rect.get_x() + rect.get_width() / 2., 1.02 * height, '%s' % (b[ii]),
                     ha='center', va='bottom')
    autolabel(rects)

    # 设置标题
    plt.ylabel('生还人数')
    plt.xticks(x_pos, x)

    plt.subplot(122)
    # 画条
    x_pos = list(range(len(x)))
    rects = plt.bar(x_pos, y, align='center', alpha=0.5)


    # 标签
    def autolabel(rects):
        for ii, rect in enumerate(rects):
            height = rect.get_height()
            plt.text(rect.get_x() + rect.get_width() / 2.,\
                     1.02 * height, '%0.3f' % (y[ii]),\
                     ha='center', va='bottom')
    autolabel(rects)

    # 设置标题
    plt.ylabel('生还率')
    plt.xticks(x_pos, x)
    plt.show()

    ageBins = [0, 12, 18, 65, 100]
    titanic["ageGroup"] = pd.cut(titanic["Age"], ageBins)
    ageGroupsRate = titanic.groupby("ageGroup")["Survived"].mean()
    ageGroupsNum = titanic.groupby("ageGroup")["Survived"].sum()

    plt.figure(figsize=(12, 5))
    plt.subplot(121)
    ageGroupsNum.plot(kind="bar")

    plt.subplot(122)
    ageGroupsRate.plot(kind="bar", x=['儿童', '少年', '成年人', '老年人'])
    plt.show()

def sibSpFact():
    # 分为有兄弟姐妹和没有兄弟姐妹两组
    sibsp = titanic[titanic['SibSp'] != 0]
    no_sibsp = titanic[titanic['SibSp'] == 0]
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Survived', data=sibsp)

    # 有兄弟姐妹的乘客的生还人数和生还率
    plt.subplot(122)
    plt.pie([sibsp['Survived'][sibsp['Survived'] == 0].count(), \
            sibsp['Survived'].sum()], \
            labels=['No Survived', 'Survived'], autopct='%1.0f%%')
    plt.show()
    print(sibsp['Survived'][sibsp['Survived'] == 0].count(), sibsp['Survived'].sum())

    # 没有兄弟姐妹的乘客的生还人数和生还率
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Survived', data=no_sibsp)

    plt.subplot(122)
    plt.pie([no_sibsp['Survived'][no_sibsp['Survived'] == 0].count(), \
            no_sibsp['Survived'].sum()], \
            labels=['No Survived', 'Survived'], autopct='%1.0f%%')
    plt.show()
    print(no_sibsp['Survived'].sum())

def parchFact():
    # 分为有父母子女和没有父母子女两组
    parch = titanic[titanic['Parch'] != 0]
    no_parch = titanic[titanic['Parch'] == 0]

    # 有父母子女的乘客的生还人数和生还率
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Survived', data=parch)

    plt.subplot(122)
    plt.pie([parch['Survived'][parch['Survived'] == 0].count(),\
            parch['Survived'].sum()], \
            labels=['No Survived', 'Survived'], autopct='%1.0f%%')
    plt.show()
    print(parch['Survived'].sum())

    #没有父母子女的乘客的生还人数和生还率
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    sns.countplot(x='Survived', data=no_parch)

    plt.subplot(122)
    plt.pie([no_parch['Survived'][no_parch['Survived'] == 0].count(),\
            no_parch['Survived'].sum()], \
            labels=['No Survived', 'Survived'], autopct='%1.0f%%')
    plt.show()
    print(no_parch['Survived'].sum())

def fareFact():
    # 票价分布
    plt.figure(figsize=(10, 5))
    titanic['Fare'].hist(bins=70)
    titanic.boxplot(column='Fare', by='Pclass', showfliers=False)
    plt.show()

    fare_not_survived = titanic["Fare"][titanic["Survived"] == 0]
    fare_survived = titanic["Fare"][titanic["Survived"] == 1]
    avgerage_fare = pd.DataFrame([fare_not_survived.mean(), fare_survived.mean()])
    std_fare = pd.DataFrame([fare_not_survived.std(), fare_survived.std()])
    avgerage_fare.plot(yerr=std_fare, kind='bar', legend=False)
    plt.show()

def embarkedFact():
    #两个丢失值，计划用众数填充
    titanic["Embarked"] = titanic["Embarked"].fillna("S")
    sns.factorplot(x='Embarked', y='Survived', \
        data=titanic, height=3, aspect=2)
    plt.show()

    # 各港口上船人数、生还人数及生还率
    fig, (axis1, axis2, axis3) = plt.subplots(1, 3, figsize=(15, 5))
    sns.countplot(x='Embarked', data=titanic, ax=axis1)
    sns.countplot(x='Survived', hue="Embarked", \
        data=titanic, order=[1, 0], ax=axis2)
    embark_perc = titanic[["Embarked", "Survived"]].groupby(['Embarked'],\
        as_index=False).mean()
    sns.barplot(x='Embarked', y='Survived', \
        data=embark_perc, order=['S', 'C', 'Q'], ax=axis3)
    plt.show()

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
    if 0:
        PclassFact()
        sexFact()
        ageFact()
        sibSpFact()
        parchFact()
        fareFact()
        embarkedFact()


