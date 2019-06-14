//顶点着色器
var VSHADER_SOURCE =
        'attribute vec4 a_Position;' +      //声明attribute变量
        'void main(){' +
        'gl_Position = a_Position;' +       //attribute变量赋值给gl_Position
        'gl_PointSize = 10.0;' +
        '}';
//着色器程序
var FSHADER_SOURCE =
        'void main(){' +
        'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);' +    //设置颜色
        '}'

function main() {
        var canvas = document.getElementById("webgl")
        if(!canvas || !canvas.getContext){
            console.log("不支持canvas");
            return false
        }

        //获取WebGL渲染上下文
        var gl = getWebGLContext(canvas)
        if(!gl){
            console.log("无法获取WebGL渲染上下文")
            return false
        }

        /*
            初始化着色器，定义在cuon-utils.js中
            将以字符串的形式的着色器代码从JavaScript传给WebGL系统，并建立着色器
        */
        if(!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)){
            console.log("初始化着色器失败")
            return  false
        }

        //获取attribute变量的存储位置
        var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
        if(a_Position < 0){
            console.log("获取a_Position的存储位置失败")
            return false
        }

        //将顶点位置传输给attribute变量
        gl.vertexAttrib3f(a_Position, 0.0,0.5,0.0);

        //清空canvas颜色
        gl.clearColor(0,0,0, 1.0)

        //清空canvas
        gl.clear(gl.COLOR_BUFFER_BIT)

        //绘制一个点
        gl.drawArrays(gl.POINTS, 0, 1)
    }