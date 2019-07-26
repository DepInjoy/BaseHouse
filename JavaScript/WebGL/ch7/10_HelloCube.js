//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute vec4 a_Color;' +
    'uniform mat4 u_MVPMatrix;' +
    'varying vec4 v_Color;' +
    'void main(){' +
    'gl_Position = u_MVPMatrix * a_Position;' +
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
//视点位置
var g_eyeX = 3, g_eyeY = 3, g_eyeZ = 7.0;

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

    //设置顶点位置和颜色
    var n = initVertexBuffers(gl);
    if (n < 0) {
        console.log("初始化顶点位置失败");
        return false;
    }

    /**
     *  设置背景颜色并开启隐藏面消除
     */
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);

    /**
     * 给模型视图投影矩阵赋值
     */
    var u_MVPMatrix = gl.getUniformLocation(gl.program, 'u_MVPMatrix');
    if(u_MVPMatrix < 0){
        console.log("获取模型视图投影矩阵u_MVPMatrix失败！");
        return false;
    }
    //创建指定可视空间的矩阵并传递给u_MVPMatrix变量
    var MVPMatrix = new Matrix4();
    //设置透视矩阵
    MVPMatrix.setPerspective(30, canvas.width / canvas.height, 1, 100)
    draw(gl, n, u_MVPMatrix, MVPMatrix);
}

function initVertexBuffers(gl) {
    //顶点坐标和颜色
    var verticesColors = new Float32Array([
        1.0,    1.0,    1.0,    1.0,    1.0,    1.0,
        -1.0,   1.0,    1.0,    1.0,    0.0,    1.0,
        -1.0,   -1.0,   1.0,    1.0,    0.0,    0.0,
        1.0,    -1.0,   1.0,    1.0,    1.0,    0.0,
        1.0,    -1.0,   -1.0,   0.0,    1.0,    0.0,
        1.0,    1.0,    -1.0,   0.0,    1.0,    1.0,
        -1.0,   1.0,    -1.0,   0.0,    0.0,    1.0,
        -1.0,   -1.0,   -1.0,   0.0,    0.0,    0.0,
    ]);

    //顶点索引
    var indeices = new Uint8Array([
        0,  1,  2,  0,  2,  3,      //前
        0,  3,  4,  0,  4,  5,      //右
        0,  5,  6,  0,  6,  1,      //上
        1,  6,  7,  1,  7,  2,      //左
        7,  4,  3,  7,  3,  2,      //下
        4,  7,  6,  4,  6,  5       //后
    ]);
    var FSIZE = verticesColors.BYTES_PER_ELEMENT;

    /**
     *      给位置赋值
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
    gl.enableVertexAttribArray(a_Position);

    /**
     *      给颜色赋值
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

    /**
     *      将顶点索引数据写入缓冲区对象
     */
    var indexBuffer = gl.createBuffer();
    if(!indexBuffer){
        console.log("创建索引缓冲区失败")
    }
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indeices, gl.STATIC_DRAW);
    return indeices.length;
}
/**
 *  绘制图形
 * @param gl                绘图上下文
 * @param n                 绘制点个数
 * @param u_ViewMatrix      视图模型
 * @param viewMatrix        视图矩阵
 */
function draw(gl, n, u_MVPMatrix, MVPMatrix) {
    MVPMatrix.lookAt(g_eyeX, g_eyeY, g_eyeZ, 0, 0, 0,0, 1,0);
    //将视图矩阵传递给u_ViewMatrix变量
    gl.uniformMatrix4fv(u_MVPMatrix, false, MVPMatrix.elements);
    gl.drawElements(gl.TRIANGLES, n, gl.UNSIGNED_BYTE, 0);
    //显示视点位置信息
    var eyeAt = document.getElementById("eyeAt");
    eyeAt.innerHTML = "eyeX: " + Math.round(g_eyeX * 100) / 100
        + ", eyeY: " + Math.round(g_eyeY * 100) / 100 ;
}