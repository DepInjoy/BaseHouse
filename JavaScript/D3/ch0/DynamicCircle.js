function draw() {
    var width = 300, height = 300;
    var svg = d3.select("body")
        .append("svg")
        .attr("width", width)
        .attr("height", height);

    var circle1 = svg.append("circle")
        .attr("cx", 45)
        .attr("cy", 45)
        .attr("r", 30)
        .style("fill", "green")
        //通过on添加监听事件器
        .on("click", function () {                  //鼠标点击，颜色由绿色切换为红色
            d3.select(this)
                .style("fill", "red");
        })
        .on("mouseover", function () {              //鼠标悬浮其上，颜色切换为黄色
            d3.select(this)
                .style("fill", "yellow");
        })
        .on("dblclick", function () {               //双击，圆形半径扩大至45
            d3.select(this)
                .transition()                       //启动过渡效果
                .duration(1000)                     //指定过渡持续时间，单位毫秒
                .ease("bounce")                     //指定过渡方式
                .attr("r", 45)
        })
        .on("mouseout", function () {               //鼠标退出，颜色切换为绿色，圆大小变为30
            d3.select(this)
                .style("fill", "green")
            d3.select(this)
                .transition()                       //启动过渡效果
                .attr("r", 30)
        })
}