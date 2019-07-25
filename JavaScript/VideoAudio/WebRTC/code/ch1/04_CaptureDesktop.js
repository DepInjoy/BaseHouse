var buffer;
shareDesktop();
/**
 * 功能说明：        判断浏览器是否是PC端
 * @returns {boolean} true：是 false：否
 */
function isPC(){
    var userAgentInfo = navigator.userAgent;
    var agents = new Array("Android", "iPhone", "SymbianOS", "Windows Phone", "iPad", "iPod");
    var flag = true;
    for (var i = 0; i < agents.length; i++) {
        if (userAgentInfo.indexOf(agents[i]) > 0) {
            flag = false;
            break;
        }
    }
    delete agents;
    agents = null;
    return flag;
}

/**
 * 功能说明：             桌面数据流处理，将获取到的桌面stream和页面元素绑定进行展示
 * @param stream        抓取到的桌面音视频流
 */
function getDeskStream(stream){
    var deskVideo = document.querySelect("video/deskVideo");
    deskVideo.srcObject = stream;
    window.localStream = stream;
}

/**
 * 功能说明:            抓取桌面
 * @returns {boolean}  true:成功 false:失败
 */
function shareDesktop(){
    if(!isPC())
        return false;

    const mediaConstraints = {
        video:      true,
        audio:      true
    };

    if('mediaDevices' in window.navigator){
        if('getDisplayMedia' in window.navigator.mediaDevices){
            //只有在PC下才能抓取桌面
            navigator.mediaDevices.getDisplayMedia(mediaConstraints)
                .then(getDeskStream)
                .catch(function (error) {
                    console.error("捕获桌面失败(" + error.name + ":" + error.message + ")");
                });
            return true;
        }else{
            console.error("不支持的API: ", "navigator.mediaDevices.getDisplayMedia");
        }
    }else{
        console.error("不支持的API: ", "navigator.mediaDevices");
    }
    return false;
}

function handleDataAvailable(e){
    if(e && e.data && e.data.size > 0){
        buffer.push(e.data);
    }
}

function startRecord(){
    // 定义一个数组，用于缓存桌面数据，最终将数据存储到文件中
    buffer = [];

    var options = {
        mimeType: 'video/webm;codecs=vp8'
    };

    if(!MediaRecorder.isTypeSupported(options.mimeType)){
        console.error('格式不支持 ',"不支持 " + options.mimeType + '格式');
        return;
    }

    try{
        //创建录制对象，用于将桌面数据录制下来
        mediaRecorder = new MediaRecorder(window.localStream, options);
    }catch(e){
        console.error('创建对象失败 ' , '创建MediaRecorder失败(' + e.name + ':'  + e.message + ')');
        return;
    }

    // 当捕获到桌面数据后，该事件触发
    mediaRecorder.ondataavailable = handleDataAvailable;
    mediaRecorder.start(10);
}
