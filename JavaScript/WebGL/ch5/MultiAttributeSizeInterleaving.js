//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute float a_PositionSize;' +
    'attribute vec4 a_Color;' +
    'varying vec4 v_Color;' +           //声明attribute变量
    'void main(){' +
    'gl_Position = a_Position;' +       //attribute变量赋值给gl_Position
    'gl_PointSize = a_PositionSize;' +
    'v_Color = a_Color;' +              //将数据传递给片元着色器
    '}';
//着色器程序
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

    //设置顶点位置
    var n = initVertexBuffer(gl);
    if(n < 0){
        console.log("初始化顶点位置失败");
        return false;
    }

    //清空canvas颜色
    gl.clearColor(0,0,0, 1.0)
    //清空canvas
    gl.clear(gl.COLOR_BUFFER_BIT)

    if(0){
        //绘制三个不同颜色的点
        gl.drawArrays(gl.POINTS, 0, n);
    }else{
        //绘制一个彩色三角形
        gl.drawArrays(gl.TRIANGLES, 0, n);
    }
}

function initVertexBuffer(gl) {
    var n = 3;
    var verticesSize = new Float32Array([
        0.0,    0.5,    10.0,   1.0,     0.0,    0.0,                //第一个顶点
        -0.5,   -0.5,   20.0,   0.0,     1.0,    0.0,                //第二个顶点
        0.5,    -0.5,   30.0,   0.0,     0.0,    1.0,                //第三个顶点
    ]);

    //创建对象缓冲区
    var vertexBuffer = gl.createBuffer();
    if(!vertexBuffer){
        console.log("创建颜色缓冲区失败");
        return -1;
    }

    var FSIZE = verticesSize.BYTES_PER_ELEMENT;
    //将颜色缓冲区绑定到目标
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    //向颜色缓冲区写入数据
    gl.bufferData(gl.ARRAY_BUFFER, verticesSize, gl.STATIC_DRAW);

    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if(a_Position < 0){
        console.log("获取a_Position存储位置失败");
        return -1;
    }
    //将缓冲区对象分配给a_Position变量
    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, FSIZE * 6, 0);
    //连接a_Position和分配给它的缓冲区对象
    gl.enableVertexAttribArray(a_Position);

    //创建缓冲区对象
    var sizeBuffer = gl.createBuffer();
    if(!sizeBuffer){
        console.log("创建对象缓冲区失败");
        return -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, sizeBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, verticesSize, gl.STATIC_DRAW);
    var a_PositionSize = gl.getAttribLocation(gl.program, "a_PositionSize");
    if(a_PositionSize < 0){
        console.log("获取a_PositionSize的存储位置失败");
        return -1;
    }
    //将顶点尺寸写入缓存区对象并开启
    gl.vertexAttribPointer(a_PositionSize, 1, gl.FLOAT, false, FSIZE * 6, FSIZE * 2);
    gl.enableVertexAttribArray(a_PositionSize);

    //给颜色赋值
    var colorBuffer = gl.createBuffer();
    if(!colorBuffer){
        console.log("创建颜色对象缓冲区失败");
        return  -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, verticesSize, gl.STATIC_DRAW);
    var a_Color = gl.getAttribLocation(gl.program, "a_Color");
    if(a_Color < 0){
        console.log("获取a_Color存储位置失败");
        return -1;
    }
    gl.vertexAttribPointer(a_Color, 3, gl.FLOAT, false, FSIZE * 6, FSIZE * 3);
    gl.enableVertexAttribArray(a_Color);

    return n;
}