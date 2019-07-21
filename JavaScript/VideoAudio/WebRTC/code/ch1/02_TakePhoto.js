'use strict';
var picture = null;

//将Date转化为指定格式的string
Date.prototype.Format = function (fmt) {
    var o = {
        "M+": this.getMonth() + 1, //月份
        "d+": this.getDate(), //日
        "H+": this.getHours(), //小时
        "m+": this.getMinutes(), //分
        "s+": this.getSeconds(), //秒
        "q+": Math.floor((this.getMonth() + 3) / 3), //季度
        "S": this.getMilliseconds() //毫秒
    };
    if (/(y+)/.test(fmt)) fmt =
        fmt.replace(RegExp.$1, (this.getFullYear() + "")
            .substr(4 - RegExp.$1.length));
    for (var k in o)
        if (new RegExp("(" + k + ")").test(fmt))
            fmt = fmt.replace(RegExp.$1,
                (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
    return fmt;
};

function main() {
    //获取HTML页面中id为picture的canvas标签
    picture = document.querySelector('canvas#picture');
}


function takePhoto() {
    //获取HTML页面video标签
    var videoPlayer = document.querySelector('video#player');
    if(!videoPlayer){
        console.log("获取video标签失败！");
        return;
    }
    //媒体轨限制
    const constraints = {
        video : {
            width: 1280,
            height: 720,
            frameRate:15,
        },
        audio : false
    };
    //采集音视频数据流
    navigator.mediaDevices.getUserMedia(constraints)
        .then(function (mediaStream) {
            videoPlayer.srcObject = mediaStream;
        })
        .catch(function (error) {
            console.log("获取音视频失败(" + error.name + "  : " + error.message + ")");
        });

    /**
     *  滤镜处理，通过css修改图片的渲染形式
     */
    const filtersSelect = document.querySelector("select#filter");
    picture.className = filtersSelect.value;

    /**
     *  从视频数据流中抓取图片
     */
    picture.getContext('2d')
        .drawImage(videoPlayer, 0, 0, picture.width, picture.height);
}

function downLoad(url) {
    const oA = document.createElement("a");
    //获取当前系统时间
    var now = new Date();
    //设置下载的文件名，默认是'下载'
    oA.download = now.Format("yyyy-MM-dd-HH:mm:ss")
    oA.href = url;
    document.body.appendChild(oA);
    oA.click();
    oA.remove();
}

function savePhoto() {
    document.querySelector("button#savePhoto").onclick = function (){
        downLoad(picture.toDataURL("image/jpeg"))
    }
}