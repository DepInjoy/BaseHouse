WebGL是一种3D绘图协议。

代码主要模块：

- ch5\MultiAttributeSize.js<br/>
功能说明：将非坐标数据(点的大小)传递给顶点着色器

- ch5\MultiAttributeSizeInterleaving.js<br/>
功能说明：通过步进和偏移实现绘制不同位置、不同颜色的三个点或者彩色三角形

- ch7 进入三维世界
    - LookAtTriangles.js</br>
    功能说明：绘制一个前面是蓝色、中间黄色、后面红色的三角形。
    - LookAtRotatedTriangles.js</br>
    功能说明：用视图矩阵*模型矩阵实现将LookAtTriangles.js绘制的三角形逆时针旋转90度。
    - LookAtRotatedTriangleModelViewMatrix.html</br>
    功能说明：用模型视图矩阵实现将LookAtTriangles.js绘制的三角形逆时针旋转90度，效果和LookAtRotatedTriangles.js一致。
    - LookAtTriangles.js<br/>
    功能说明：绘制一个前面是蓝色、中间黄色、后面红色的三角形。
    - LookAtRotatedTriangles.js<br/>
    功能说明：用视图矩阵*模型矩阵实现将LookAtTriangles.js绘制的三角形逆时针旋转90度。
    - LookAtRotatedTriangleModelViewMatrix.html<br/>
    功能说明：用模型视图矩阵实现将LookAtTriangles.js绘制的三角形逆时针旋转90度，效果和LookAtRotatedTriangles.js一致。
    - LookAtTrianglesWithKey.js<br/>
    功能说明：实现在LookAtTriangles.js绘制的三角形，可以通过鼠标的上下、左右按键控制其X、Y的位置。
    - OrthoView.js<br/>
    功能说明：辅助理解盒型视图空间，可以通过上下、左右按键控制近边界和远边界。
    - LookAtTriangleWithKeysWithViewVolume.js<br/>
    功能说明：在LookAtTrianglesWithKey.js基础之上引入正射投影矩阵
    - PerspectiveView.js<br/>
    功能说明：透视投影矩阵调用显示左右各三个三角形示例，同时支持上下、左右按键控制视图。
    - PerspectiveViewWithVMP.js<br/>
    功能说明：通过透视矩阵、视图矩阵和模型矩阵实现通过复制显示在左右两侧各三个三角形，效果和PerspectiveView.js的效果一致。
    - 08_DepBuffer.js<br/>
    功能说明：开启隐藏面消除，看到的效果和PerspectiveViewWithVMP.js一样。
    - 09_DepFlight.js<br/>
    功能说明：避免深度冲突示例，两个Z一致的三角形制造深度冲突，然后消除。重点在于开启多边形偏移并设置多边形偏移。
    - 10_HelloCube.js<br/>
    功能说明：绘制一个立方体。
- ch8
    - 01_LightedCube.js<br/>
    功能说明：绘制一个白色平行光照射下的红色立方体
    - 02_LightedCubeAmbient.js<br/>
    功能说明：在01_LightedCube.js的基础上添加环境漫反射。
    - 03_LightedTranslatedRotatedCube.js<br/>
    功能说明：立方体沿着Z轴旋转90度，然后沿着y轴平移1个单位。
    - 04_PointLightedCube.js<br/>
    功能说明：绘制一个点光源照射下的红色立方体，并以固定速率旋转。
    - 05_PointLightedCubePreFragment.js<br/>
    功能说明：效果同04_PointLightedCube.js，通过逐片元实现的，效果更接近真实情况。
- ch9
    - 01_JointModel.js<br/>
    功能说明：绘制两个链接在一起的机械臂，同时支持左右上下按键进行控制。
    - 02_MultiJointModel.js<br/>
    功能说明：绘制一个多个关节的机械臂，支持z、x、c、v按键和上下左右按键进行控制。
    - 03_MultiJointModelSegment.js<br/>
    功能说明：效果同02_MultiJointModel.js，只是每个结点是通过一组数据给入的。
第三方库文件
- cuon-matrix.js
    - Matrix4.setLookAt(eyeX,eyeY,eyeZ,atX,atY,atZ,upX,,upY,upZ):根据视点、观察点、上方向来创建视图矩阵
        - eyeX,eyeY,eyeZ:指定视点
        - atX,atY,atZ:指定观察点
        - upX,,upY,upZ:指定上方向，如果上方向是Y轴正向，则(upX,,upY,upZ)是(0,1,0)
    
    - Matrix4.setOrtho(left, right, bottom, top, near, far)通过各参数计算正投影矩阵
        - left, right:  指定可视空间的近裁面的左边界和右边界
        - bottom, top:  指定可视空间的近裁面的上下边界
        - near, far:    指定可视空间的近边界和远边界
    
    - Matrix4.setPerspective(fov, aspect, near, far)通过各参数计算透视投影矩阵，将其存储在Matrix4中。<br/>
        - fov:          指定垂直视角
        - aspect:       指定近裁面的宽高比
        - near, far:    指定近裁面和元裁面的位置

接口说明
- gl.drawArrays(mode, type, offset)
- gl.drawElements()高效绘制三维图形，按照mode指定的方式根据绑定到gl.ELEMENT_ARRAY_BUFFER缓冲区中的顶点索引绘制图形。
    - mode       指定绘制方式
    - type：     指定索引数据的类型
    - offset     指定索引数组中开始绘制的位置，单位：字节

- gl.vertexAttribPointer(location, size, type, normalized, stride, offset);<br/>
    将绑定至gl.ARRAY_BUFFER的缓冲区对象分配给location指定的attribute变量。
    - location 指定待分配的attribute变量的存储位置
    - size         指定缓存区中每个顶点的分量个数
    - type         指定数据格式
    - normalise    true或false，表明是否将浮点型数据归一化到[0,1]或[-1, 1]区间
    - stride       相邻两个点间的字节数，默认为0
    - offset       缓冲区对象中偏移量(单位为字节)，如果从其实位置开始，该参数设为0.

- gl.bindTexture(target, texture)
    开启texture指定的纹理图像，并将其绑定至target上。
    - target
        - gl.TEXTURE_2D:        二维纹理
        - gl.TEXTURE_CUBE_MAP      立方体纹理

- gl.texParameteri(tartget, pname, param)
   配置纹理对象参数
   - target         gl.TEXTURE_2D或gl.TEXTURE_CUBE_MAP
   - pname          纹理参数
    - gl.TEXTURE_MIN_FILTER:    缩小法,默认值gl.LINEAR
    - gl.TEXTURE_MAG_FILTER:    放大方法，默认值gl.NEAREST_MIPMAP_LINEAR
    - gl.TEXTURE_WRAP_S:        水平填充法,默认值gl.REPEAT
    - gl.TEXTURE_WRAP_T:        垂直填充法,默认值gl.REPEAT
   - param          纹理参数的值

- gl.enable(cap) 开启cap表示的功能
    - cap           开启需要制定的功能
        - gl.DEPTH_TEST             隐藏面消除
        - gl.BLEND                  混合
        - gl.POLYGON_OFFSET_FILL    多边形位移等等
- gl.disable(cap) 关闭cap表示的功能
    - cap           关闭需要制定的功能
        - gl.DEPTH_TEST             隐藏面消除
        - gl.BLEND                  混合
        - gl.POLYGON_OFFSET_FILL    多边形位移等等
<br/>

注意事项<br/>
- 出于安全性考虑，WebGL允许使用跨域纹理图像。
- GLSL ES中的变量不能以gl_、wbgl_、_webgl_开头，这些开头已经被OPenGL ES保留位关键字。

问题附录<br/>

- failed to compile shader: ERROR: 0:1: '' : No precision specified for (float)<br/>

在着色器程序中添加：
```$JavaScript
#ifdef GL_ES
    precision mediump float;
#endif
```

<br/>
学习资源

- [MDN API接口](https://developer.mozilla.org/zh-CN/docs/Web/API/WebGLRenderingContext/vertexAttribPointer)
- []()