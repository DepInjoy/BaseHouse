//顶点着色器
var VSHADER_SOURCE =
    'attribute vec4 a_Position;' +
    'attribute vec4 a_Color;' +             //表面基底色
    'attribute vec4 a_Normal;' +            //法向量
    'uniform mat4 u_NormalMatrix;' +        //用于计算法向量的矩阵
    'uniform mat4 u_MVPMatrix;' +
    'uniform vec3 u_LightColor;' +          //光线颜色
    'uniform vec3 u_LightDirection;' +      //归一化的世界坐标
    'uniform vec3 u_AmbientLightColor;' +        //环境光颜色
    'varying vec4 v_Color;' +
    'void main(){' +
    'gl_Position = u_MVPMatrix * a_Position;' +
    //对法向量归一化
    'vec3 normal = normalize(vec3(u_NormalMatrix * a_Normal));' +
    //计算光线方向和法向量的乘积，<0时，入射角大于90表明照射在背面，此时归0.
    'float nDotL = max(dot(u_LightDirection, normal), 0.0);' +
    //计算漫反射光的颜色
    'vec3 diffuse = u_LightColor * vec3(a_Color) * nDotL;' +
    //计算环境光产生的反射光颜色
    'vec3 ambient = u_AmbientLightColor * a_Color.rgb;' +
    //两者相加得到物体最终颜色并将数据传递给片元着色器
    'v_Color = vec4(diffuse + ambient, a_Color.a);' +
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

//模型透视矩阵参数
var MVPObj = {
    modelMatrix : new Matrix4().setIdentity(),
    viewMatrix : new Matrix4().setLookAt(20.0, 10.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0),
    prespectiveMatrix : new Matrix4().setPerspective(50.0, 1, 1.0, 100),
    PVMatrix : function () {
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

//光源参数
var lightObj = {
    lightColor : new Vector3([1.0, 1.0, 1.0]),          //白色光
    lightDirection : new Vector3([0.5, 3.0, 4.0]),
    ambientLight : new Vector3([0.2, 0.2, 0.2])         //环境光源
};

//层级参数
var layer = {
    baseLength : 2.0,
    arm1Angle : 0.0,                //arm1的当前角度
    arm1Length : 12.0,
    jointAngle : 0.0,               //joint1的当前角度(arm2的角度)
    arm2Length : 10.0,
    joint1Angle: 0.0,
    plamLength : 2.0,
    palmJointAngle: 0.0,
    finger1JointAngle:  0.0,
    finger2JointAngle:  0.0,
    fingerLength: 2.0,
    angleStep : 3.0                 //每次按键转动的角度
};

//存储矩阵的栈
var g_matrixStack = [];

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

    /**
     *  设置背景颜色并开启隐藏面消除
     */
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);

    //设置顶点位置和颜色
    var n = initVertexBuffers(gl);
    if (n < 0) {
        console.log("初始化顶点位置失败");
        return false;
    }

    //初始光源
    if(!initLight(gl)){
        console.log("初始化光线颜色和方向信息失败！");
        return false;
    }

    //初始化视图模型矩阵和法向量
    var u_MVPMatrix = gl.getUniformLocation(gl.program, 'u_MVPMatrix');
    if(u_MVPMatrix < 0){
        console.log("获取模型视图投影矩阵u_MVPMatrix失败！");
        return false;
    }
    var u_NormalMatrix = gl.getUniformLocation(gl.program, 'u_NormalMatrix');
    if(u_NormalMatrix < 0){
        console.log("获取u_NormalMatrix失败!");
        return  false;
    }
    setMVPMatrix(gl, u_MVPMatrix, u_NormalMatrix);

    /**
     *  绘图
     */
    document.onkeydown = function (ev) {
        keydown(ev, gl, n, MVPObj, u_MVPMatrix, u_NormalMatrix);
    };
    draw(gl, n, MVPObj, u_MVPMatrix, u_NormalMatrix);
}

function keydown(ev, gl, n, MVPObj, u_MVPMatrix, u_NormalMatrix) {
    switch (ev.keyCode) {
        case 38:    //向上,joint1绕Z轴正向旋转
            if(layer.jointAngle < 135.0)
                layer.jointAngle += layer.angleStep;
            break;
        case 40:    //向下,joint1绕Z轴负向旋转
            if(layer.jointAngle > -135.0)
                layer.jointAngle -= layer.angleStep;
            break;
        case 37:    //向左，arm1绕Y轴负向运动
            layer.arm1Angle = (layer.arm1Angle - layer.angleStep) % 360;
            break;
        case 39:    //向右，arm1绕Y轴正向运动
            layer.arm1Angle = (layer.arm1Angle + layer.angleStep) % 360;
            break;
        case 90:    //z,手掌正向转动
            layer.palmJointAngle = (layer.palmJointAngle + layer.angleStep) % 360;
            break;
        case 88:    //x,手掌反向转动
            layer.palmJointAngle = (layer.palmJointAngle + layer.angleStep) % 360;
            break;
        case 86:    //v,手指正向转动
            if(layer.finger1JointAngle < 60){
                layer.finger1JointAngle += layer.angleStep;
                layer.finger2JointAngle = -1 * layer.finger1JointAngle;
            }
            break;
        case 67://c，手指反向转动
            if(layer.finger1JointAngle > -60){
                layer.finger1JointAngle -= layer.angleStep;
                layer.finger2JointAngle = -1 * layer.finger1JointAngle;
            }
            break;
        default:
            console.log("未知的键盘输入，不处理！");
            return;
            break;
    }
    draw(gl, n, MVPObj, u_MVPMatrix, u_NormalMatrix);
}
/**
 * 功能说明：            初始化着色器中vec3的一些变量
 * @param gl            WebGL渲染上下文
 * @param name          着色器变量名
 * @param vec3Val       vec3参数值
 */
function initVec3(gl, name, vec3Val) {
    var vecLocation = gl.getUniformLocation(gl.program, name);
    if (vecLocation < 0) {
        console.log("获取着色器变量(" + name + ")失败！");
        return false;
    }
    gl.uniform3fv(vecLocation, vec3Val.elements);
    return true;
}

/**
 * 功能说明：            初始化光线的颜色和方向等
 * @param gl            WebGL上下文
 * @returns {boolean}   true 成功, false失败.
 */
function initLight(gl) {
    /**
     *  获取并设置光线颜色(平行光+漫反射光)
     */
    //设置光线颜色(白色)
    if(!initVec3(gl, 'u_LightColor', lightObj.lightColor)) {
        console.log("初始化光线颜色失败");
        return false;
    }

    if(!initVec3(gl, 'u_AmbientLightColor', lightObj.ambientLight))
        return false;
    /**
     *  设置光线方向
     */
    return initVec3(gl, 'u_LightDirection', lightObj.lightDirection.normalize());
}
/**
 * 功能说明：            初始化颜色、位置和法向量缓冲区
 * @param gl            WebGL上下文
 * @param data          欲写入的数据
 * @param name          WEBGL ES中缓冲区名称
 * @param num           点数
 * @param type          指定缓存区中每个顶点的分量个数
 * @param stride        相邻两个点间的字节数
 * @param offset        缓冲区对象中偏移量
 * @returns {boolean}   true：成功 false：失败
 */
function initArrayBuffer (gl, data, name, num, type, stride, offset) {
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
    gl.vertexAttribPointer(vertexLoction, num, type, false, stride, offset);
    gl.enableVertexAttribArray(vertexLoction);
    return true;
}

/**
 *  功能说明：           初始化顶点的位置和颜色
 * @param gl            WebGL绘图上下文
 * @returns {number}    顶点个数，-1表示初始化失败
 */
function initVertexBuffers(gl) {
    //顶点坐标和颜色
    var verticesColors = new Float32Array([
        0.5,    1.0,    0.5,    1.0,    0.4,    0.0,    //0
        -0.5,   1.0,    0.5,    1.0,    0.4,    0.0,    //1
        -0.5,   0.0,    0.5,    1.0,    0.4,    0.0,    //2
        0.5,    0.0,    0.5,    1.0,    0.4,    0.0,    //3
        0.5,    0.0,    -0.5,   1.0,    0.4,    0.0,    //4
        0.5,    1.0,    -0.5,   1.0,    0.4,    0.0,    //5
        -0.5,   1.0,    -0.5,   1.0,    0.4,    0.0,    //6
        -0.5,   0.0,    -0.5,   1.0,    0.4,    0.0     //7
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
        0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    //前
        1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    //右
        0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    0.0,    1.0,    0.0,    //上
        -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    //左
        0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    //下
        0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0,   0.0,    0.0,    -1.0    //后
    ]);
    var FSIZE = verticesColors.BYTES_PER_ELEMENT;
    /** 给法向量赋值 */
    if(!initArrayBuffer(gl, normalData, 'a_Normal',
        3, gl.FLOAT, 0, 0))
        return -1;

    /** 给位置赋值 */
    if(!initArrayBuffer(gl, verticesColors, "a_Position",
        3,  gl.FLOAT,FSIZE * 6, 0))
        return -1;

    /** 给颜色赋值 */
    if(!initArrayBuffer(gl, verticesColors, "a_Color",
        3,  gl.FLOAT, 6 * FSIZE, 3 * FSIZE))
        return -1;

    /**
     *      将顶点索引数据写入缓冲区对象
     */
    var indexBuffer = gl.createBuffer();
    if(!indexBuffer){
        console.log("创建索引缓冲区失败");
        return -1;
    }
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indeices, gl.STATIC_DRAW);
    return indeices.length;
}

/**
 * 功能说明：                给视图矩阵和法向量赋值
 * @param gl                WebGL渲染上下文
 */
function setMVPMatrix(gl, u_MVPMatrix, u_NormalMatrix) {
    /** 给模型视图投影矩阵赋值 */
    //将视图矩阵传递给u_ViewMatrix变量
    gl.uniformMatrix4fv(u_MVPMatrix, false, MVPObj.MVPMatrix().elements);

    /** 给法向量矩阵赋值 */
    //model逆转置,给用于变换法向量的矩阵赋值
    var reverseModelMat = new Matrix4().setInverseOf(MVPObj.modelMatrix).transpose();
    gl.uniformMatrix4fv(u_NormalMatrix, false, reverseModelMat.elements);
}

/**
 * 功能说明：                将矩阵压栈
 * @param matrix            矩阵
 */
function pushMatrix(matrix) {
    var tmp = new Matrix4(matrix);
    g_matrixStack.push(tmp);
}

/**
 * 功能说明：                将矩阵从栈中弹出
 */
function popMatrix() {
   return g_matrixStack.pop();
}

function drawBox(gl, n, width, height, depth, u_MVPMatrix, u_NormalMatrix) {
    pushMatrix(MVPObj.modelMatrix);
    MVPObj.modelMatrix.scale(width, height, depth);
    setMVPMatrix(gl, u_MVPMatrix, u_NormalMatrix);
    MVPObj.modelMatrix.set(popMatrix());
    gl.drawElements(gl.TRIANGLES, n, gl.UNSIGNED_BYTE, 0);
}
/**
 *  绘制图形
 * @param gl                绘图上下文
 * @param n                 绘制点个数
 * @param u_ViewMatrix      视图模型
 * @param viewMatrix        视图矩阵
 */
function draw(gl, n, MVPObj, u_MVPMatrix, u_NormalMatrix) {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    //Base
    MVPObj.modelMatrix.setTranslate(0.0, -12.0, 0.0);
    drawBox(gl, n ,10.0, layer.baseLength, 10.0, u_MVPMatrix, u_NormalMatrix);

    //Arm1
    MVPObj.modelMatrix.translate(0.0, layer.baseLength, 0.0)
        .rotate(layer.arm1Angle, 0.0, 1.0, 0.0);
    drawBox(gl, n, 3.0, layer.arm1Length, 3.0, u_MVPMatrix, u_NormalMatrix);

    //Arm2
    MVPObj.modelMatrix.translate(0.0, layer.arm1Length, 0.0)
        .rotate(layer.jointAngle, 0.0, 0.0, 1.0);                //绕着Z轴旋转
    drawBox(gl, n, 4.0, layer.arm2Length, 4.0, u_MVPMatrix, u_NormalMatrix);

    //手掌
    MVPObj.modelMatrix.translate(0.0, layer.arm2Length, 0.0)
        .rotate(layer.palmJointAngle, 0.0, 1.0 ,0.0);
    drawBox(gl, n, 6.0, layer.plamLength, 2.0, u_MVPMatrix, u_NormalMatrix);

    //手指
    MVPObj.modelMatrix.translate(0.0, layer.plamLength, 0.0)

    //finger 1
    pushMatrix(MVPObj.modelMatrix);
    MVPObj.modelMatrix.translate(2.0, 0.0, 0.0)
        .rotate(layer.finger1JointAngle, 0.0, 0.0, 1.0);
    drawBox(gl, n, 1.0, layer.fingerLength, 1.0, u_MVPMatrix, u_NormalMatrix);
    MVPObj.modelMatrix.set(popMatrix());

    //finger 2
    MVPObj.modelMatrix.translate(-2.0, 0.0, 0.0)
        .rotate(layer.finger2JointAngle, 0.0, 0.0, 1.0);
    drawBox(gl, n, 1.0, layer.fingerLength, 1.0, u_MVPMatrix, u_NormalMatrix);
}