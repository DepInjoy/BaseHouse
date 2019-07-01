代码主要模块：
- ch5\MultiAttributeSize.js</br>
功能说明：将非坐标数据(点的大小)传递给顶点着色器

- ch5\MultiAttributeSizeInterleaving.js</br>
功能说明：通过步进和偏移实现绘制不同位置、不同颜色的三个点或者彩色三角形


接口说明
- gl.vertexAttribPointer(location, size, type, normalized, stride, offset);</br>
    将绑定至gl.ARRAY_BUFFER的缓冲区对象分配给location指定的attribute变量。</br>
    
    - location 指定待分配的attribute变量的存储位置
    - size         指定缓存区中每个顶点的分量个数
    - type     指定数据格式
    - normalise    true或false，表明是否将浮点型数据归一化到[0,1]或[-1, 1]区间
    - stride       相邻两个点间的字节数，默认为0
    - offset       缓冲区对象中偏移量(单位为字节)，如果从其实位置开始，该参数设为0.

</br>
问题附录</br>

- failed to compile shader: ERROR: 0:1: '' : No precision specified for (float)</br>

在着色器程序中添加：
```$JavaScript
#ifdef GL_ES
    precision mediump float;
#endif
```

</br>
学习资源

- [MDN API接口](https://developer.mozilla.org/zh-CN/docs/Web/API/WebGLRenderingContext/vertexAttribPointer)
- []()