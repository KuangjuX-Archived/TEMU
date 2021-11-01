import WsConnect from "./WsConnect";
import {myConfig,Config} from "./config";
import TemuConnect from "./TemuConnect";

function main(config:Config):void{
    let myWsConnect=new WsConnect()
    myWsConnect.init(config.port)
}

main(myConfig)

const fs = require('fs'); //文件模块
const path = require('path'); //路径模块
const express = require('express'); //express框架模块
const app = express();
const port = 8888; //端口

app.use(express.static(path.resolve(__dirname, './dist'))); // 设置静态项目访问路径(此处的dist为webpack打包生成的项目文件夹名称)
console.log(path.resolve(__dirname, './dist'))
app.get('*', function(req:any, res:any) {
    const html = fs.readFileSync(path.resolve(__dirname, './dist/index.html'), 'utf-8'); // 设置所有访问服务请求默认返回index.html文件
    res.send(html);
});

app.listen(port, function() {
    console.log(`服务器运行在:${port}`);
});