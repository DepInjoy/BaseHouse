//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +      //声明attribute变量
    'void main(){' +
    'gl_Position = a_Position;' +       //attribute变量赋值给gl_Position
    '}';

var FSHADER_SOURCE =
    'void main(){' +
    'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);' +    //设置颜色
    '}'

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
    var selectedShape = 0;

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

function initVertexBuffer(gl, selectedShape) {
    var n;
    var vertices;

    switch(selectedShape){
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
        console.log("获取a_Position存储位置失败")
        return -1;
    }

    //将缓冲区对象分配给a_Position变量
    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
    //连接a_Position和分配给它的缓冲区对象
    gl.enableVertexAttribArray(a_Position)
    return n;
}