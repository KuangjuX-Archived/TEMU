import WsConnect from "./WsConnect";
import {myConfig,Config} from "./config";
import TemuConnect from "./TemuConnect";

function main(config:Config):void{
    let myWsConnect=new WsConnect()
    myWsConnect.init(config.port)
    let myTemuConnect=new TemuConnect()
    myTemuConnect.setWsC(myWsConnect)
    myWsConnect.setTemuC(myTemuConnect)
    setTimeout(()=>{myTemuConnect.sendMsg2Temu("si 1")},15000)
}

main(myConfig)
console.log("stated")