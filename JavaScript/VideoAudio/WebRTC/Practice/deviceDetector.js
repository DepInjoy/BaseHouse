//媒体轨限制
const mediaStreamConstrains = {
    video: {
        frameRate: {
            min:                20,         //帧率最小值
        },
        width: {
            min:                640,        //宽度最小值
            ideal:              1280        //理想宽度
        },
        height: {
            min:                360,        //高度最小值
            ideal:              720         //理想高度
        },
        aspectRatio:            16/9        //宽高比
    }, audio: {
        echoCancellation:       true,       //是否开启回音消除
        noiseSuppression:       true,       //是否开启降噪
        autoGainControl:        true,       //是否开启自动增益
        muted:                  true,
    }
};

const videoStreamConstrains = {
    video:{

    }
};

/**
 * 功能描述：                请求camera,并请求访问摄像头
 * @param mediaStream       getUserMedia方法采集到的音视频轨
 */
function getLocalMediaStream(mediaStream){
    //获取video选择器
    const localVideo = document.querySelector('video');
    if(!localVideo){
        console.log("获取Video选择器失败!")
        return;
    }

    //将视频源传递给HTML的video标签的srcObject属性
    localVideo.srcObject = mediaStream;
}

/**
 * 功能描述：                设备检测
 * @returns {boolean}       true：成功 false：失败
 */
function getLocalMediaDevicesInfo() {
    //设备检测
    if (!navigator.mediaDevices || !navigator.mediaDevices.enumerateDevices) {
        console.log("不支持enumerateDevices接口！");
        return false;
    }
    //列出视频和音频设备
    navigator.mediaDevices.enumerateDevices()
        .then(function (mediaDevicesInfo) {
            const audioInputDevicesInfo = document.getElementById("audioInputDevicesInfo");
            const audioOutputDevicesInfo = document.getElementById("audioOutputDevicesInfo");
            const videoInputDevicesInfo = document.getElementById("videoInputDevicesInfo");
            mediaDevicesInfo.forEach(function (deviceInfo) {
                var pItem = document.createElement("p");
                pItem.append("Label " + deviceInfo.label
                    + " DeviceId " + deviceInfo.deviceId
                    + " GroupId " + deviceInfo.groupId);
                //将设备信息在页面中分类显示
                if (deviceInfo.kind == "audioinput") {
                    audioInputDevicesInfo.appendChild(pItem);
                }else if(deviceInfo.kind == "videoinput"){
                    videoInputDevicesInfo.appendChild(pItem);
                }else if(deviceInfo.kind == "audiooutput"){
                    audioOutputDevicesInfo.appendChild(pItem);
                }
                //以日志形式显示设备信息
                console.log(deviceInfo.kind + " " + deviceInfo.label + " " + deviceInfo.deviceId + deviceInfo.groupId);
            })
        })
        .catch(function (error) {
            console.log("捕获设备信息出错，错误信息(" + error.name + ": " + error.message + ")");
        });
    return true;
}

function detector() {
    if(!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia){
        alert("该浏览器不支持WebRTC，请检查");
        return false;
    }

    navigator.mediaDevices.getUserMedia(mediaStreamConstrains).then(function (mediaStream) {
        if(!getLocalMediaDevicesInfo()){
            console.log("获取本地音视频设备信息失败！")
            return;
        }
        //采集视频信息
        getLocalMediaStream(mediaStream)
    }).catch(function (error) {
        console.log('navigator.getUserMedia error: ', error);
    });
}

