//顶点着色器
/**
 *  顶点着色器接收顶点的纹理坐标，光栅化后传递给片元着色器
 */
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute vec2 a_TexCoord;' +
    'varying vec2 v_TexCoord;' +
    'void main(){' +
    'gl_Position = a_Position;' +
    'v_TexCoord = a_TexCoord;' +
    '}';
/**
 *  片元着色器根据片元的纹理坐标，从纹理图像中抽取出纹素颜色，赋给当前片元
 * */
//片元着色器程序
var FSHADER_SOURCE =
    '#ifdef GL_ES\n'+
    'precision mediump float;\n' +
    '#endif\n' +
    'uniform sampler2D u_Sampler;'+
    'varying vec2 v_TexCoord;' +
    'void main(){' +
    'gl_FragColor = texture2D(u_Sampler, v_TexCoord);' +    //从片元着色器中获取纹理像素颜色
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
    var n = initVertexBuffers(gl);
    if(n < 0){
        console.log("初始化顶点位置失败");
        return false;
    }

    //清空canvas颜色
    gl.clearColor(0,0,0, 1.0)

    //设置顶点信息
    var n = initVertexBuffers(gl);
    if (n < 0) {
        console.error("设置顶点信息失败！");
        return false;
    }
    //配置纹理
    if(!initTextures(gl, n)){
        console.error("配置纹理失败！")
        return false;
    }
    return true;
}

/**
 *  设置顶点纹理坐标
 */
function initVertexBuffers(gl) {
/*
    var vertexTexCoords = new Float32Array([
        //顶点坐标  纹理坐标
        -0.5, 0.5, 0.0, 1.0,
        -0.5, -0.5, 0.0, 0.0,
        0.5, 0.5, 1.0, 1.0,
        0.5, -0.5, 1.0, 0.0
    ]);
 */
    var vertexTexCoords = new Float32Array([
        //顶点坐标  纹理坐标
        -0.5, 0.5, -0.3, 1.7,
        -0.5, -0.5, -0.3, -0.2,
        0.5, 0.5, 1.7, 1.7,
        0.5, -0.5, 1.7, -0.2
    ]);
    //设置顶点数目
    var n = 4;
    var FSIZE = vertexTexCoords.BYTES_PER_ELEMENT;

    //创建缓冲区对象,并将顶点坐标和纹理坐标写入缓冲区对象
    var vertexTexCoordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexTexCoordBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, vertexTexCoords, gl.STATIC_DRAW);

    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if(a_Position < 0){
        console.error("获取a_Position存储位置失败");
        return -1;
    }
    var a_TexCoord = gl.getAttribLocation(gl.program, 'a_TexCoord');
    if(a_TexCoord < 0){
        console.error("获取纹理坐标a_TexCoord存储位置失败")
        return -1;
    }

    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, FSIZE*4, 0);
    gl.vertexAttribPointer(a_TexCoord, 2, gl.FLOAT, false, FSIZE*4, FSIZE*2);
    gl.enableVertexAttribArray(a_Position);
    gl.enableVertexAttribArray(a_TexCoord);
    return n;
}

/**
 * 准备待加载的纹理图像，令浏览器读取它
 * @param gl        WebGL绘图上下文
 * @param n         顶点个数
 * @returns {boolean} true: 成功  false:失败
 */
function initTextures(gl, n) {
    // 1、创建纹理对象以存储纹理图像
    var texture = gl.createTexture();
    if(!texture){
        console.error("创建纹理对象失败");
        return false;
    }
    // 获取纹理的存储位置
    var u_Sampler = gl.getUniformLocation(gl.program, 'u_Sampler');
    if(u_Sampler < 0){
        console.error("获取纹理图像存储位置u_Sampler失败");
        return false;
    }
    var img = new Image();
    //注册图像加载事件的响应函数
    img.onload = function(){
        //图像加载完成，开始使用纹理
        //由于加载图像过程是异步的，需要监听加载完成的事件(onload)
        loadTextures(gl, n, texture, u_Sampler, img);
    };
    //浏览器开始加载图像
    img.src = "./sky.jpg";
    return true;
}

/**
 * 监听纹理图像的加载事件，一旦加载完成，在WebGL系统中使用纹理
 * @param gl            WebGL绘图上下文
 * @param n             顶点个数
 * @param texture       纹理对象
 * @param u_Sampler     着色器中纹理图像的取样，对应于着色器中的u_Sampler存储位置
 * @param image         图片
 */
function loadTextures (gl, n, texture, u_Sampler, image) {
    /*
        对纹理进行Y轴反转
        由于WebGL坐标系统中的t轴方向和PNG、BMP、JPG等格式图片坐标系统中的Y轴中Y轴是相反的
     */
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
    //开启0号纹理单元
    gl.activeTexture(gl.TEXTURE0);
    //向target绑定纹理对象,TEXTURE_CUBE_MAP代表立方体纹理
    gl.bindTexture(gl.TEXTURE_2D, texture);
    if(1){
        //配置纹理对象参数
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    }else {
        //辅助理解，测试使用
        //配置纹理对象参数
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
        //水平轴S轴上填充最边缘纹素的颜色
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE)
        //垂直轴t轴上重复填充纹理
        //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.MIRRORED_REPEAT);
    }
    //将纹理图像分配给纹理对象
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
    //将0号纹理传递给着色器中的取样器变量
    gl.uniform1i(u_Sampler, 0);
    //绘图
    gl.clear(gl.COLOR_BUFFER_BIT);          //清空canvas
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, n);
    //删除纹理对象，释放资源
    gl.deleteTexture(texture);
    delete image;
    image = null;
}