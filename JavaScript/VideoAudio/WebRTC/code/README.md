声明：该模块中的代码主要是根据极客时间的李超的《从0到1打造音视频直播系统》的课程记录和进一步学习补充。<br/>

资源推荐
- [MDN WebRTC API](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API)


代码主要模块
- ch1
    - GetLocalVideoAudio.js<br/>
    功能描述：获取本地摄像头的音频和视频，并在html中进行播放
    - 02_TakePhoto.js</br>
    功能描述：实现拍照功能，并支持在网页端用css进行渲染实现滤镜效果。
    <br/>处理步骤：<br/>
        - 1、设置图片的滤镜处理方式。
        - 2、从采集到的视频中获取图片，查看滤镜处理效果。
        - 3、将处理的图片保存成文件
    <br/>待解决的问题：<br/>
        - 1、浏览器保存的图片，保存后效果丢失，那么如何实现对保存的图片进行滤镜处理？
    - 03_SaveAudio.js</br>
    功能描述：实现视频录制、回放和保存。
    <br/>待解决的问题：<br/>
        - 多路音频、视频互动情况下如何实现录制和回放？
        - 是否可以将多路音频录制到同一个多媒体文件中？
    - 04_CaptureDesktop.js<br/>
    功能描述：实现桌面的抓取、回放和下载
    <br/>待解决的问题:<br/>
        - 使用视频编码方式为什么容易模糊？怎么解决？

第三方库
- 音视频设备检测
    - [MediaDevices](https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices) 访问连接到计算机上的媒体设备和以及截取窃取屏幕的方法
        - [抓取桌面 getDisplayMedia()
](https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices/getDisplayMedia)
    - [MediaDeviceInfo](https://developer.mozilla.org/en-US/docs/Web/API/MediaDeviceInfo)输入/输出设备的信息，主要包含下面三个属性：
        - deviceID，设备的唯一标识。
        - label，设备名称，除非用户已经授予访问设备的权限，否则该字段一直为空。
        - kind，设备种类，可用于识别出是音频设备还是视频设备，是输出或输入设备。
        
- 音视频采集
    - navigator.mediaDevices.getUserMedia(constraints);
        - constraints：类型为 MediaStreamConstraints，指定包含哪些视媒体轨，并为这些媒体轨设置一些限制。
        - 返回：成功则返回MediaStream对象；失败则会返回PermissionDeniedError或NotFoundError等错误对象。

- [MediaStreamConstraints 媒体轨限制](https://w3c.github.io/mediacapture-main/getusermedia.html#mediastreamconstraints)
- 拍照(从视频流中抓取图片)
    - ctx.drawImage(image, dx, dy, width, height)
        - 输入参数
            - image:一幅图片
            - dx,dy:图片起点的x,y坐标
            - width, height: 图片的宽度和高度
   