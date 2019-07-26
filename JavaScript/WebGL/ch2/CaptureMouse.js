var isAllowedColorChanged = false
//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +      //声明attribute变量
    'void main(){' +
    'gl_Position = a_Position;' +       //attribute变量赋值给gl_Position
    'gl_PointSize = 10.0;' +
    '}';
//着色器程序
if(!isAllowedColorChanged){
    //绘制点的颜色不变
    var FSHADER_SOURCE =
        'void main(){' +
        'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);' +    //设置颜色
        '}'
}else{
    //改变颜色
    var FSHADER_SOURCE =
        'precision mediump float;' +        //经度限定词，限定指定变量的精度和范围
        'uniform vec4 u_FragColor;' +
        'void main(){' +
        'gl_FragColor = u_FragColor;' +    //设置颜色
        '}'
}
function main() {
    var canvas = document.getElementById("webgl")
    if (!canvas || !canvas.getContext) {
        console.log("不支持canvas");
        return false
    }

    //获取WebGL渲染上下文
    var gl = getWebGLContext(canvas)
    if (!gl) {
        console.log("无法获取WebGL渲染上下文")
        return false
    }

    /*
        初始化着色器，定义在cuon-utils.js中
        将以字符串的形式的着色器代码从JavaScript传给WebGL系统，并建立着色器
    */
    if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
        console.log("初始化着色器失败")
        return false
    }

    /*
        获取attribute变量的存储位置
        @param1     gl.program是一个程序对象
    */
    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if (a_Position < 0) {
        console.log("获取a_Position的存储位置失败")
        return false
    }

    if (isAllowedColorChanged){
        //获取uniform变量的位置
        var u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
        if (!u_FragColor) {
            console.log("获取u_FragColor的存储位置失败")
            return false;
        }
    }
    if(!isAllowedColorChanged){
        //注册鼠标点击事件响应函数
        canvas.onmousedown = function (ev) {
            handleClicked(ev, gl, canvas, a_Position)
        }
    }else{
        canvas.onmousedown = function (ev) {
            handleClicked0(ev, gl, canvas, a_Position, u_FragColor)
        }
    }
    //清空canvas颜色
    gl.clearColor(0,0,0, 1.0)
    //清空canvas
    gl.clear(gl.COLOR_BUFFER_BIT)
}

//全局变量，存储鼠标点击选中的WebGL的坐标点
var g_Points = [];
function handleClicked(ev, gl, canvas, a_Position) {
    //鼠标点击客户浏览区坐标
    var x = ev.clientX;
    var y = ev.clientY;
    //获取canvas在客户浏览区的坐标
    var rect = ev.target.getBoundingClientRect();
    //转换到canvas坐标系再转换到WebGL坐标系
    x = ((x - rect.left) - (canvas.width / 2)) / (canvas.width / 2);
    y = ((canvas.height / 2) - (y - rect.top)) / (canvas.height / 2);
    g_Points.push([x, y]);

    //清空canvas
    gl.clear(gl.COLOR_BUFFER_BIT)
    for(var i = 0; i < g_Points.length;i+=1){
        //将顶点位置传输给attribute变量
        gl.vertexAttrib3f(a_Position, g_Points[i][0], g_Points[i][1], 0.0);
        //绘制一个点
        gl.drawArrays(gl.POINTS, 0, 1)
    }
}
//全局变量，存储颜色
var g_Colors = [];
function handleClicked0(ev, gl, canvas, a_Position, u_FragColor) {
    //鼠标点击客户浏览区坐标
    var x = ev.clientX;
    var y = ev.clientY;
    //获取canvas在客户浏览区的坐标
    var rect = ev.target.getBoundingClientRect();
    //转换到canvas坐标系再转换到WebGL坐标系
    x = ((x - rect.left) - (canvas.width / 2)) / (canvas.width / 2);
    y = ((canvas.height / 2) - (y - rect.top)) / (canvas.height / 2);
    g_Points.push([x, y]);

    //根据不同象限设置颜色
    if(x >= 0 && y >= 0)
        g_Colors.push([1.0, 0.0, 0.0, 1.0]);
    else if(x > 0 && y < 0)
        g_Colors.push([0.0, 1.0, 0.0, 1.0]);
    else if(x < 0 && y < 0)
        g_Colors.push([0.0, 0.0, 1.0, 1.0])
    else
        g_Colors.push([1.0, 1.0, 1.0, 1.0])

    //清空canvas
    gl.clear(gl.COLOR_BUFFER_BIT)
    for(var i = 0; i < g_Points.length;i+=1){
        //将顶点位置传输给attribute变量
        gl.vertexAttrib3f(a_Position, g_Points[i][0], g_Points[i][1], 0.0);
        //将顶点颜色传递给u_FragColor
        gl.uniform4f(u_FragColor, g_Colors[i][0],g_Colors[i][1],g_Colors[i][2],g_Colors[i][3])
        //绘制一个点
        gl.drawArrays(gl.POINTS, 0, 1)
    }
}