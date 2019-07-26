D3全称是(Data-Driven Documents),一个JavaScript实现的开源项目，主要用于数据的可视化。

该工程师我的D3学习过程的记录

- ch0
    - DynamicCircle.js
    功能描述：绘制一个圆，添加事件监听器，监听鼠标悬浮、点击、双击和离开，改变圆的颜色和大小。
    
    - HelloWorld.html<br/>
    功能描述：将所有的段落的字体更改为36px
              展示和元素的选择和数据的绑定
              选择、插入和删除元素相关操作

    - PiePlot.html
        功能描述：绘制一个饼状图，为不同的饼块添加不同的颜色和对应的数值。
- CircleAnimation.html
    - 功能描述：实现在1秒内将圆心坐标由100变化到300，半径缩小到25并采用bounce的过渡方式将颜色由绿色变更为红色
    - 重点功能接口：
        - **指定过渡方式，ease(),调用格式ease("bounce")**<br/>
        常用的过渡方式有：
            - linear：普通的线性变化
            - circle：慢慢地到达变换的最终状态
            - elastic：带有弹跳的到达最终状态
            - bounce：在最终状态处弹跳几次

