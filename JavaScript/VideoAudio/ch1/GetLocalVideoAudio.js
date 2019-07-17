'use strict';

//媒体轨限制
const mediaStreamContrains = {
    video: {
        frameRate: {min: 20},
        width: {min: 640, ideal: 1280},
        height: {min: 360, ideal: 720},
        aspectRatio: 16/9
    },
    audio: {
        echoCancellation: true,
        noiseSuppression: true,
        autoGainControl: true,
        muted:           true
    }
};


const localVideo = document.querySelector('video');
if(!localVideo){
    console.log("获取video选择器失败！");
}

/**
 * 功能描述：                请求camera
 * @param mediaStream       getUserMedia方法采集到的音视频轨
 */
function gotLocalMediaStream(mediaStream){
    //将视频源传递给HTML的video标签的srcObject属性
    localVideo.srcObject = mediaStream;
}

function handleLocalMediaStreamError(error){
    console.log('navigator.getUserMedia error: ', error);
}

navigator.mediaDevices.getUserMedia(mediaStreamContrains).then(
    gotLocalMediaStream
).catch(
    handleLocalMediaStreamError
);
