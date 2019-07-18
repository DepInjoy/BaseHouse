代码主要模块
- ch1
    - GetLocalVideoAudio.js<br/>
    功能描述：获取本地摄像头的音频和视频，并在html中进行播放

第三方库
- 音视频采集
    - navigator.mediaDevices.getUserMedia(constraints);
        - constraints：类型为 MediaStreamConstraints，指定包含哪些视媒体轨，并为这些媒体轨设置一些限制。
        - 返回：成功则返回MediaStream对象；失败则会返回PermissionDeniedError或NotFoundError等错误对象。

- [MediaStreamConstraints 媒体轨限制](https://w3c.github.io/mediacapture-main/getusermedia.html#mediastreamconstraints)
    