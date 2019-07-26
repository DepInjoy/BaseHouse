//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute float a_PositionSize;' +      //声明attribute变量
    'void main(){' +
    'gl_Position = a_Position;' +       //attribute变量赋值给gl_Position
    'gl_PointSize = a_PositionSize;' +
    '}';
//着色器程序
var FSHADER_SOURCE =
    'void main(){' +
    'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);' +    //设置颜色
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

    gl.drawArrays(gl.POINTS, 0, n);
}

function initVertexBuffer(gl) {
    var n;
    var vertices;

    n = 3;
    vertices = new Float32Array([
        0.0, 0.5, -0.5, -0.5, 0.5, -0.5
    ]);

    var sizes = new Float32Array([
        10.0, 20.0, 30.0
    ]);
    //创建对象缓冲区
    var vertexBuffer = gl.createBuffer();
    if(!vertexBuffer){
        console.log("创建颜色缓冲区失败");
        return -1;
    }

    //将颜色缓冲区绑定到目标
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    //向颜色缓冲区写入数据
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if(a_Position < 0){
        console.log("获取a_Position存储位置失败");
        return -1;
    }
    //将缓冲区对象分配给a_Position变量
    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
    //连接a_Position和分配给它的缓冲区对象
    gl.enableVertexAttribArray(a_Position)

    //创建缓冲区对象
    var sizeBuffer = gl.createBuffer();
    if(!sizeBuffer){
        console.log("创建对象缓冲区失败");
        return -1;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, sizeBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, sizes, gl.STATIC_DRAW);
    var a_PositionSize = gl.getAttribLocation(gl.program, "a_PositionSize");
    if(a_PositionSize < 0){
        console.log("获取a_PositionSize的存储位置失败");
        return -1;
    }
    //将顶点尺寸写入缓存区对象并开启
    gl.vertexAttribPointer(a_PositionSize, 1, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_PositionSize);
    return n;
}