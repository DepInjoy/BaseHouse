function main() {
    new Promise(function (resolve, reject) {
        console.log("start a new Promise");
        //生成一个0到2之间的随机数
        var timeoutVal = Math.random() * 2;
        setTimeout(function () {
            if(timeoutVal < 1){
                resolve("Resolve: Timeout " + timeoutVal + " second");
            }else {
                reject("Reject: timeout " + timeoutVal + " Second");
            }
        }, timeoutVal * 1000);
    }).then(function (stat) {
        //完成处理
        console.log("完成: " + stat);
    }).catch(function (error) {
        //失败处理
        console.log("失败: " + error);
    });
}