声明：该模块中的代码主要是根据极客时间的李超的《从0到1打造音视频直播系统》的课程记录和进一步学习补充。<br/>

资源推荐
- [MDN WebRTC API](https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API)


代码主要模块
- ch1
    - GetLocalVideoAudio.js<br/>
    功能描述：获取本地摄像头的音频和视频，并在html中进行播放

第三方库
- 音视频设备检测
    - [MediaDevices](https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices) 访问连接到计算机上的媒体设备和以及截取窃取屏幕的方法
    
    - [MediaDeviceInfo](https://developer.mozilla.org/en-US/docs/Web/API/MediaDeviceInfo)输入/输出设备的信息，主要包含下面三个属性：
        - deviceID，设备的唯一标识。
        - label，设备名称，除非用户已经授予访问设备的权限，否则该字段一直为空。
        - kind，设备种类，可用于识别出是音频设备还是视频设备，是输出或输入设备。
        
- 音视频采集
    - navigator.mediaDevices.getUserMedia(constraints);
        - constraints：类型为 MediaStreamConstraints，指定包含哪些视媒体轨，并为这些媒体轨设置一些限制。
        - 返回：成功则返回MediaStream对象；失败则会返回PermissionDeniedError或NotFoundError等错误对象。

- [MediaStreamConstraints 媒体轨限制](https://w3c.github.io/mediacapture-main/getusermedia.html#mediastreamconstraints)
    