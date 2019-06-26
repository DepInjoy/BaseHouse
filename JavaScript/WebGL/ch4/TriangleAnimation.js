//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +      //声明attribute变量
    'uniform mat4 u_rotatedMatrix;' +   //旋转矩阵
    'void main(){' +
    '   gl_Position = u_rotatedMatrix * a_Position;' +  //attribute变量赋值给gl_Position
    '}';

var FSHADER_SOURCE =
    'void main(){' +
    'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);' +    //设置颜色
    '}'
//旋转角速度
var rotatedAngleStep = 60.0;
function main() {
    var canvas = document.getElementById("webgl")
    if(!canvas || !canvas.getContext){
        console.log("该浏览器不支持canvas");
        return false;
    }

    var gl = getWebGLContext(canvas);
    if(!gl){
        console.log("无法获取WebGL渲染上下文")
        return false;
    }

    if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
        console.log("初始化着色器失败");
        return false;
    }

    /**
     * 设置绘制图形的形状
     * 0：                   被填充的三角形
     * 1：                   只包含外框的三角形
     * 2：                   四边形
     * 3：                   飘带
     */
    var selectedShape = 3;

    //设置顶点位置
    var n = initVertexBuffer(gl, selectedShape);
    if(n < 0){
        console.log("初始化顶点位置失败");
        return false;
    }

    //清空canvas颜色
    gl.clearColor(0,0,0, 1.0)
    //清空canvas
    gl.clear(gl.COLOR_BUFFER_BIT)

    var curAngle = 0.0;
    //为旋转矩阵创建Matrix4对象
    var rotatedMatrix = new Matrix4();

    //获取旋转矩阵u_rotatedMatrix的存储位置并赋值
    var u_rotatedMatrix = gl.getUniformLocation(gl.program, 'u_rotatedMatrix');
    if(!u_rotatedMatrix){
        console.log("获取u_rotatedMatrix存储位置失败")
        return -1;
    }

    //开始绘制三角形
    var tick = function () {
        //更新旋转角
        curAngle = animate(curAngle);
        draw(gl, n, curAngle, rotatedMatrix, u_rotatedMatrix, selectedShape);
        /*
            请求浏览器调用tick
            requestAnimationFrame与setInterval类似，只是在标签页激活状态下才生效
            cancelAnimationFrame取消请求
         */
        requestAnimationFrame(tick);
    };
    tick();
}

function initVertexBuffer(gl, selectedShape) {
    var n;
    var vertices;

    switch (selectedShape) {
        case 0:
        case 1:
            n = 3;
            vertices = new Float32Array([
                0.0, 0.5, -0.5, -0.5, 0.5, -0.5
            ]);
            break;
        case 2:
        case 3:
            n = 4;
            vertices = new Float32Array([
                -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, -0.5
            ]);
            break;
    }
    //创建对象缓冲区
    var vertexBuffer = gl.createBuffer();
    if (!vertexBuffer) {
        console.log("创建颜色缓冲区失败");
        return -1;
    }

    //将颜色缓冲区绑定到目标
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    //向颜色缓冲区写入数据
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if (a_Position < 0) {
        console.log("获取a_Position存储位置失败")
        return -1;
    }


    //将缓冲区对象分配给a_Position变量
    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
    //连接a_Position和分配给它的缓冲区对象
    gl.enableVertexAttribArray(a_Position)
    return n;
}
/*
    功能描述：               绘制图形
    @param gl               绘图上下文
    @param n                顶点个数
    @param curAngle         当前旋转角度
    @param rotatedMatrix    旋转矩阵
    @param u_rotatedMatrix  顶点着色器中的旋转矩阵
    @param selectedShape    绘图的形状
* */
function draw(gl, n, curAngle, rotatedMatrix, u_rotatedMatrix, selectedShape) {
    //设置旋转矩阵
    rotatedMatrix.setRotate(curAngle, 0, 0, 1);
    //平移至0.35单位处
    rotatedMatrix.translate(0.35, 0 , 0)
    //将旋转矩阵传递给顶点着色器
    gl.uniformMatrix4fv(u_rotatedMatrix, false, rotatedMatrix.elements);
    //清楚canvas
    gl.clear(gl.COLOR_BUFFER_BIT);
    //绘制图形
    switch (selectedShape) {
        case 0:
            //绘制三角形
            gl.drawArrays(gl.TRIANGLES, 0, n);
            break;
        case 1:
            //绘制三角形
            gl.drawArrays(gl.LINES, 0, n);
            gl.drawArrays(gl.LINE_STRIP, 0, n);
            gl.drawArrays(gl.LINE_LOOP, 0, n);
            break;
        case 2:
            gl.drawArrays(gl.TRIANGLE_STRIP, 0, n);
            break;
        case 3:
            gl.drawArrays(gl.TRIANGLE_FAN, 0, n);
            break;
        default:
            console.log("未知的形状选项")
            break;
    }
}

//记录上一次调用函数的时刻
var g_last = Date.now();
function animate(angle) {
    //计算距离上次调用经过了多久
    var now = Date.now();
    //单位:毫秒
    var elapsed = now - g_last;
    g_last = now;
    //根据距离上次调用的时间，更新当前旋转角度
    var newAngle = angle + (rotatedAngleStep * elapsed) / 1000.0;
    return newAngle % 360;
}