function main() {
    //获取canvas元素
    var theCanvas = document.getElementById("example")
    //判断该浏览器是否支持canvas
    if(!theCanvas || !theCanvas.getContext){
        alert("Can not retrieve the canvas!")
        return false
    }

    //向该元素请求二维图形的绘图上下文
    var rect = theCanvas.getContext('2d')
    /*
        在绘图上下文中调用绘图函数，绘制一个绿色的矩形
        一单指定背景色之后，背景色便会入驻WebGL系统，在调用clearColor之前不会改变
     */
    rect.fillStyle = 'rgba(0, 255, 0, 0.8)'              //设置刷子的颜色
    rect.fillRect(120, 10, 150, 150)        //填充矩形
}