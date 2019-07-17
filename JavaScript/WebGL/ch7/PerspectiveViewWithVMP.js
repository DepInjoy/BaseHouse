//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute vec4 a_Color;' +
    'uniform mat4 u_ViewMatrix;' +
    'uniform mat4 u_ModelMatrix;' +
    'uniform mat4 u_ProjMatrix;' +                      //正射投影矩阵
    'varying vec4 v_Color;' +
    'void main(){' +
    'gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * a_Position;' +
    'v_Color = a_Color;' +              //将数据传递给片元着色器
    '}';
//片元着色器程序
var FSHADER_SOURCE =
    '#ifdef GL_ES\n'+
    'precision mediump float;\n' +
    '#endif\n'+
    'varying vec4 v_Color;' +           //将内插得到的颜色赋值给v_Color，
    'void main(){' +
    'gl_FragColor = v_Color;' +         //v_Color赋值给gl_FragColor
    '}';

function main() {
    var canvas = document.getElementById("webgl")
    if (!canvas || !canvas.getContext) {
        console.log("该浏览器不支持canvas");
        return false;
    }

    var gl = getWebGLContext(canvas);
    if (!gl) {
        console.log("无法获取WebGL渲染上下文")
        return false;
    }

    if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
        console.log("初始化着色器失败");
        return false;
    }

    //设置顶点位置
    var n = initVertexBuffers(gl);
    if (n < 0) {
        console.log("初始化顶点位置失败");
        return false;
    }

    /**
     * 给透视投影矩阵赋值
     */
    var u_ProjMatrix = gl.getUniformLocation(gl.program, 'u_ProjMatrix');
    if(u_ProjMatrix < 0){
        console.log("获取正射投影矩阵u_ProjMatrix失败！");
        return false;
    }
    //创建指定可视空间的矩阵并传递给u_ProjMatrix变量
    var projMatrix = new Matrix4();
    //移动X的位置，不会发生切断现象
    projMatrix.setPerspective(30, canvas.width / canvas.height, 1, 100)
    gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);

    /**
     *  设置模型矩阵
     */
    var u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix');
    if(u_ModelMatrix < 0){
        console.log("获取模型矩阵u_ModelMatrix失败");
        return  false;
    }
    //创建模型矩阵并赋值
    var modelMatrix = new Matrix4();
    /**
     *  设置视图矩阵
     */
    //获取u_ViewMatrix变量的储存位置
    var u_ViewMatrix = gl.getUniformLocation(gl.program, "u_ViewMatrix");
    if(u_ViewMatrix < 0){
        console.log("获取u_ViewMatrix失败")
        return false;
    }
    //设置视点、视线和上方向
    var  viewMatrix = new Matrix4();
    //右移0.75个单位
    modelMatrix.setTranslate(0.75, 0, 0);
    //绘制三角形
    draw(gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix);

    //在左侧复制一个三角形
    modelMatrix.setTranslate(-0.75, 0, 0);
    draw(gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix);
    /**
     *  注册鼠标响应事件
     */
    document.onkeydown = function (ev) {
        //绘制左侧三角形
        modelMatrix.setTranslate(-0.75, 0, 0);
        //处理键盘事件
        keydown(ev, gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix);
        //绘制右侧三角形
        modelMatrix.setTranslate(0.75, 0, 0);
        draw(gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix);
    };
}

function initVertexBuffers(gl) {
    var verticesColors = new Float32Array([
        0.0,    0.5,    -0.4,   0.4,    1.0,    0.4,        //最后一个绿色三角形
        -0.5,   -0.5,   -0.4,   0.4,    1.0,    0.4,
        0.5,    -0.5,   -0.4,   1.0,    0.4,    0.4,

        0.0,    0.5,    -0.2,   1.0,    0.4,    0.4,        //中间黄色三角形
        -0.5,   -0.5,   -0.2,   1.0,    1.0,    0.4,
        0.5,    -0.5,   -0.2,   1.0,    1.0,    0.4,

        0.0,    0.5,    0.0,   0.4,    0.4,    1.0,         //前面蓝色三角形
        -0.5,   -0.5,   0.0,   0.4,    0.4,    1.0,
        0.5,    -0.5,   0.0,   1.0,    0.4,    0.4
    ]);

    var n = 9;
    var FSIZE = verticesColors.BYTES_PER_ELEMENT;

    /**
     给位置赋值
     */
    var vertexBuffer = gl.createBuffer();
    if(!vertexBuffer){
        console.log("创建颜色缓冲区失败");
        return -1;
    }
    //将颜色缓冲区绑定到目标
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    //向颜色缓冲区写入数据
    gl.bufferData(gl.ARRAY_BUFFER, verticesColors, gl.STATIC_DRAW);
    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if(a_Position < 0){
        console.log("获取a_Position存储位置失败");
        return -1;
    }
    //将缓冲区对象分配给a_Position变量
    gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, FSIZE * 6, 0);
    //连接a_Position和分配给它的缓冲区对象
    gl.enableVertexAttribArray(a_Position)

    /**
     给颜色赋值
     */
    var colorBuffer = gl.createBuffer();
    if(!colorBuffer){
        console.log("创建颜色对象缓冲区失败");
        return  -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, verticesColors, gl.STATIC_DRAW);
    var a_Color = gl.getAttribLocation(gl.program, "a_Color");
    if(a_Color < 0){
        console.log("获取a_Color存储位置失败");
        return -1;
    }
    gl.vertexAttribPointer(a_Color, 3, gl.FLOAT, false, FSIZE * 6, FSIZE * 3);
    gl.enableVertexAttribArray(a_Color);
    return n;
}
//视点位置
var g_eyeX = 0, g_eyeY = 0, g_eyeZ = 5;

/**
 *  按键处理
 * @param ev                键盘按键
 * @param gl                绘图上下文
 * @param n                 点个数
 * @param u_ViewMatrix      视图模型
 * @param viewMatrix        视图矩阵
 */
function keydown(ev, gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix) {
    switch (ev.keyCode) {
        case 39:        //按下右键
            g_eyeX += 0.01;
            break;
        case 37:        //按下左键
            g_eyeX -= 0.01;
            break;
        case 38:        //按下向上键
            g_eyeY += 0.01;
            break;
        case 40:        //按下向下键
            g_eyeY -= 0.01;
            break;
        default:
            console.log("按下的按键不处理,键值: " + ev.keyCode);
            break;
    }
    draw(gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix);
}

/**
 *  绘制图形
 * @param gl                绘图上下文
 * @param n                 绘制点个数
 * @param u_ViewMatrix      视图模型
 * @param viewMatrix        视图矩阵
 */
function draw(gl, n, u_ViewMatrix, viewMatrix, u_ModelMatrix, modelMatrix) {
    gl.uniformMatrix4fv(u_ModelMatrix, false, modelMatrix.elements);
    //设置视图矩阵，视点(0, 0, 5),视线为Z轴负方向，正方向为Y轴正向
    viewMatrix.setLookAt(g_eyeX, g_eyeY, g_eyeZ, 0, 0, -100,0, 1,0);
    //将视图矩阵传递给u_ViewMatrix变量
    gl.uniformMatrix4fv(u_ViewMatrix, false, viewMatrix.elements);
    gl.drawArrays(gl.TRIANGLES, 0, n);
    //显示视点位置信息
    var eyeAt = document.getElementById("eyeAt");
    eyeAt.innerHTML = "eyeX: " + Math.round(g_eyeX * 100) / 100
        + ", eyeY: " + Math.round(g_eyeY * 100) / 100 ;
}