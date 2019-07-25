'use strict';

/**
 * 音视频检测
 */
function deviceDetector() {
    if (!navigator.mediaDevices || !navigator.mediaDevices.enumerateDevices) {
        console.log("enumerateDevices() not supported.");
        return false;
    }

    // List cameras and microphones.
    navigator.mediaDevices.enumerateDevices()
        .then(function(devices) {
            devices.forEach(function(device) {
                console.log(device.kind + ": " + device.label +
                    " id = " + device.deviceId);
            });
        })
        .catch(function(err) {
            console.log(err.name + ": " + err.message);
            return false;
        });
    return true;
}

//媒体轨限制
const mediaStreamConstrains = {
    video: {
        frameRate: {
            min:                20,         //帧率最小值
        },
        width: {
            min:                640,        //宽度最小值
            ideal:              1280,       //理想宽度
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


const localVideo = document.querySelector('video');
if(!localVideo){
    console.log("获取video选择器失败！");
}

/**
 * 功能描述：                请求camera,并请求访问摄像头
 * @param mediaStream       getUserMedia方法采集到的音视频轨
 */
function gotLocalMediaStream(mediaStream){
    //设备检测
    if(!deviceDetector()){
        console.log("设备检测失败！");
        return;
    }
    //将视频源传递给HTML的video标签的srcObject属性
    localVideo.srcObject = mediaStream;
}

function handleLocalMediaStreamError(error){
    console.log('navigator.getUserMedia error: ', error);
}

/**
 * 功能描述：                      视音频采集
 * mediaStreamConstrains：       媒体轨限制
 */
navigator.mediaDevices.getUserMedia(mediaStreamConstrains).then(
    //成功获取视频处理
    gotLocalMediaStream
).catch(
    //错误处理
    handleLocalMediaStreamError
);
