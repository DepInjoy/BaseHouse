//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute vec4 a_Color;' +             //表面基地色
    'uniform mat4 u_ModelMatrix;' +         //模型矩阵
    'uniform mat4 u_NormalMatrix;' +        //用于变换法向量的矩阵
    'attribute vec4 a_Normal;' +            //法向量
    'uniform mat4 u_VPMatrix;' +
    'varying vec4 v_Color;' +
    'varying vec3 v_Normal;' +
    'varying vec3 v_Position;' +
    //'attribute vec2 a_TexCoord;' +
    //'varying vec2 v_TexCoord;' +
    'void main(){' +
    'gl_Position = u_VPMatrix * u_ModelMatrix * a_Position;' +
    //两者相加得到物体最终颜色并将数据传递给片元着色器
    'v_Color = a_Color;' +
    //计算顶点的世界坐标
    'v_Position = vec3(u_ModelMatrix * a_Position);' +
    'v_Normal = normalize(vec3(u_NormalMatrix * a_Normal));' +
//    'v_TexCoord = a_TexCoord;' +
    '}';
//片元着色器程序
var FSHADER_SOURCE =
    '#ifdef GL_ES\n'+
    'precision mediump float;\n' +
    '#endif\n'+
    'uniform vec3 u_LightColor;' +
    'uniform vec3 u_LightPosition;' +           //光源位置(世界坐标系)
    'uniform vec3 u_AmbientLightColor;' +
    'varying vec4 v_Color;' +
    'varying vec3 v_Normal;' +
    'varying vec3 v_Position;' +
    //'uniform sampler2D u_Sampler;'+
   // 'varying vec2 v_TexCoord;' +
    'void main(){' +
    //对光线进行归一化，因为内插之后长度未必为1.0
    'vec3 normal = normalize(v_Normal);' +
    //计算光线方向并归一化
    'vec3 lightDirection = normalize(u_LightPosition - v_Position);' +
    //计算光线方向和法向量的乘积，<0时，入射角大于90表明照射在背面，此时归0.
    'float nDotL = max(dot(lightDirection, normal), 0.0);' +
    //计算漫反射光的颜色
    'vec3 diffuse = u_LightColor * vec3(v_Color) * nDotL;' +
    //计算环境光产生的反射光颜色
    'vec3 ambient = u_AmbientLightColor * v_Color.rgb;' +
    'gl_FragColor = vec4(diffuse + ambient, v_Color.a);' +      //v_Color赋值给gl_FragColor
    //'vec4 textureColor = textureCube(u_Sampler, vec2(v_TexCoord.s, v_TexCoord.t));' +
    //'gl_FragColor = vec4(textureColor.rgb * lightWeight, v_TexCoord.a);' +
    '}';

//模型透视矩阵参数
var MVPObj = {
    modelMatrix : new Matrix4().setIdentity(),
    viewMatrix : new Matrix4().setLookAt(6.0, 3.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0),
    prespectiveMatrix : new Matrix4().setPerspective(30.0, 1, 1.0, 100),
    VPMatrix : function () {
        return new Matrix4().setIdentity()
            .multiply(this.prespectiveMatrix)
            .multiply(this.viewMatrix);
    },
    MVPMatrix : function () {
        return new Matrix4().setIdentity()
            .multiply(this.prespectiveMatrix)
            .multiply(this.viewMatrix)
            .multiply(this.modelMatrix);
    }
};

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

    if(!initTextures(gl, n)){
        console.log("初始化取样器失败！");
        return false;
    }

    /**
     *  设置背景颜色并开启隐藏面消除
     */
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    /**
     * u_ModelMatrix
     */
    var u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix');
    if(u_ModelMatrix < 0){
        console.log("获取u_ModelMatrix失败！");
        return false;
    }

    //model逆转置,给用于变换法向量的矩阵赋值
    var u_NormalMatrix = gl.getUniformLocation(gl.program, 'u_NormalMatrix');
    if(u_NormalMatrix < 0){
        console.log("获取u_NormalMatrix失败！");
        return false;
    }

    /**
     *  获取并设置光线颜色(平行光+漫反射光)
     */
    var u_LightColor = gl.getUniformLocation(gl.program, 'u_LightColor');
    if(u_LightColor < 0){
        console.log("获取光线颜色u_LightColor失败！");
        return false;
    }
    //设置光线颜色(白色)
    gl.uniform3f(u_LightColor, 1.0,1.0,1.0);

    var u_LightPosition = gl.getUniformLocation(gl.program, 'u_LightPosition');
    if(u_LightPosition < 0){
        console.log("获取u_LightPosition失败！")
        return false;
    }
    gl.uniform3f(u_LightPosition, 0.5, 3.0, 4.0);

    //设置环境光
    var u_AmbientLightColor = gl.getUniformLocation(gl.program, 'u_AmbientLightColor');
    if(u_AmbientLightColor < 0){
        console.log("获取光线颜色u_LightColor失败！");
        return false;
    }
    //设置光线颜色(白色)
    gl.uniform3f(u_AmbientLightColor, 0.2,0.2, 0.2);

    /**
     * 给模型视图投影矩阵赋值
     */
    var u_VPMatrix = gl.getUniformLocation(gl.program, 'u_VPMatrix');
    if(u_VPMatrix < 0){
        console.log("获取模型视图投影矩阵u_MVPMatrix失败！");
        return false;
    }
    gl.uniformMatrix4fv(u_VPMatrix, false, MVPObj.VPMatrix().elements);

    /**
     *  旋转处理
     */
    //绕X、Y轴旋转角度
    var currentAngle = [0.0, 0.0];
    initEventHandlers(canvas, currentAngle);
    var tick = function(){
        draw(gl, n, u_VPMatrix, u_ModelMatrix,u_NormalMatrix, currentAngle);
        requestAnimationFrame(tick);
    };
    tick();
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
 * 功能：      初始化缓存区
 * @param gl            WebGL上下文
 * @param data          欲写入的数据
 * @param name          WEBGL ES中缓冲区名称
 * @param num           点数
 * @param type          指定缓存区中每个顶点的分量个数
 * @returns {boolean}   true：成功 false：失败
 */
function initArrayBuffer (gl, data, name, num, type) {
    var vertexBuffer = gl.createBuffer();
    if(!vertexBuffer){
        console.log("创建缓冲区失败");
        return false;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
    var vertexLoction = gl.getAttribLocation(gl.program, name);
    if(vertexLoction < 0){
        console.log("获取" + name + "缓冲区的位置失败！");
        return false;
    }
    gl.vertexAttribPointer(vertexLoction, num, type, false, 0, 0);
    gl.enableVertexAttribArray(vertexLoction);
    return true;
}

function initVertexBuffers(gl) {
    //顶点坐标和颜色
    var verticesColors = new Float32Array([
        1.0,    1.0,    1.0,    1.0,    0.0,    0.0,
        -1.0,   1.0,    1.0,    1.0,    0.0,    0.0,
        -1.0,   -1.0,   1.0,    1.0,    0.0,    0.0,
        1.0,    -1.0,   1.0,    1.0,    0.0,    0.0,
        1.0,    -1.0,   -1.0,   1.0,    0.0,    0.0,
        1.0,    1.0,    -1.0,   1.0,    0.0,    0.0,
        -1.0,   1.0,    -1.0,   1.0,    0.0,    0.0,
        -1.0,   -1.0,   -1.0,   1.0,    0.0,    0.0,
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

    //通过设置顶点的法向量 确定面的法向量
    var normalData = new Float32Array([
        0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,
        1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,
        0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,
        -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,
        0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,
        0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0
    ]);
    var FSIZE = verticesColors.BYTES_PER_ELEMENT;
    /**
     *      给法向量赋值
     */
    initArrayBuffer(gl, normalData, 'a_Normal', 3, gl.FLOAT);

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
/*
    var a_TexCoord = gl.getAttribLocation(gl.program, 'a_TexCoord');
    if(a_TexCoord < 0){
        console.error("获取纹理坐标a_TexCoord存储位置失败")
        return -1;
    }
    gl.vertexAttribPointer(a_TexCoord, 2, gl.FLOAT, false, FSIZE*4, FSIZE*2);
    gl.enableVertexAttribArray(a_TexCoord);
 */
    return indeices.length;
}
/**
 *  绘制图形
 * @param gl                绘图上下文
 * @param n                 绘制点个数
 * @param u_ViewMatrix      视图模型
 * @param viewMatrix        视图矩阵
 */
function draw(gl, n, u_VPMatrix, u_ModelMatrix, u_NormalMatrix, currentAngle) {
    MVPObj.modelMatrix.rotate(currentAngle[0], 1.0, 0.0, 0.0);
    MVPObj.modelMatrix.rotate(currentAngle[1], 0.0, 1.0, 0.0);
    gl.uniformMatrix4fv(u_ModelMatrix, false, MVPObj.modelMatrix.elements);
    //model逆转置,给用于变换法向量的矩阵赋值
    var reverseModelMat = new Matrix4().setInverseOf(MVPObj.modelMatrix).transpose();      //求逆和转置
    gl.uniformMatrix4fv(u_NormalMatrix, false, reverseModelMat.elements);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.drawElements(gl.TRIANGLES, n, gl.UNSIGNED_BYTE, 0);
    delete  reverseModelMat;
    reverseModelMat = null;
}

function initEventHandlers(canvas, currentAngle) {
   var dragging = false;
   var lastX = -1, lastY = -1;
   //按下鼠标
   canvas.onmousedown = function (ev) {
       var x = ev.clientX, y = ev.clientY;
       //如果鼠标在canvas内开始拖动
       var rect = ev.target.getBoundingClientRect();
       if(rect.left <= x && x < rect.right
            && rect.top <= y && y < rect.bottom){
           lastX = x;
           lastY = y;
           dragging = true;
       }
   };

   //松开鼠标
    canvas.onmouseup = function (ev) {
        dragging = false;
        currentAngle[0] = 0.0;
        currentAngle[1] = 0.0;
    };

    //移动鼠标
    canvas.onmousemove = function (ev) {
        var x = ev.clientX, y = ev.clientY;
        if(dragging){
            //旋转因子
            var factor = 100 / canvas.height;
            var dx = factor * (x - lastX);
            var dy = factor * (y - lastY);
            //将Y轴控制在-90到90度以内
            currentAngle[0] = Math.max(Math.min(currentAngle[0] + dy, 90.0), -90.0);
            currentAngle[1] = currentAngle[1] + dx;
        }
        lastX = x;
        lastY = y;
    }
}