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
var buffer;                         //存储视频数据
var mediaRecorder = null;           //

// 当该函数被触发后，将数据压入到 blob 中
function handleDataAvailable(e){
    if(e && e.data && e.data.size > 0){
        buffer.push(e.data);
    }
}

function stop(){
    if(mediaRecorder &&
        (mediaRecorder.state === "recording"
            || mediaRecorder.state === "paused")){
        mediaRecorder.stop();
    }
}
/**
 * 功能说明：            开始录制音视频
 */
function startRecord(){
    if(mediaRecorder && mediaRecorder.state == "recording")
        return;
    buffer = [];
    //设置录制的多媒体格式
    var options = {
        mimeType: 'video/webm;codecs=vp8'
    };

    //判断浏览器是否支持录制
    if(!MediaRecorder.isTypeSupported(options.mimeType)){
        console.error('不支持' + options.mimeType + '多媒体格式');
        return;
    }

    try{
        //创建录制对象
        mediaRecorder = new MediaRecorder(window.mediaStream, options);
    }catch(e){
        console.error('Failed to create MediaRecorder:', e);
        return;
    }

    //当有音视频数据来了之后触发该事件
    mediaRecorder.ondataavailable = handleDataAvailable;
    //开始录制
    mediaRecorder.start(10);
}

/**
 *  功能说明:                   回放录制视频
 */
function replay() {
    var recvideo = document.getElementById("player");
    var blob = new Blob(buffer, {type: 'video/webm'});
    recvideo.src = window.URL.createObjectURL(blob);
    recvideo.srcObject = null;
    recvideo.controls = true;
    recvideo.play();
}

function download() {
    var blob = new Blob(buffer, {type: 'video/webm'});
    var url = window.URL.createObjectURL(blob);
    var a = document.createElement('a');

    a.href = url;
    a.style.display = 'none';
    a.download = 'aaa.webm';
    a.click();
}

/**
 * 功能描述：                      视音频采集
 * mediaStreamConstrains：       媒体轨限制
 */
navigator.mediaDevices.getUserMedia(mediaStreamConstrains).then(function (mediaStream) {
    //成功获取视频处理
    window.mediaStream = mediaStream;
}).catch(function () {
    //错误处理
    console.log('navigator.getUserMedia error: ', error);
});


