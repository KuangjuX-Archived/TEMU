import WsConnect from "./WsConnect";
import {myConfig,Config} from "./config";
import TemuConnect from "./TemuConnect";

function main(config:Config):void{
    let myWsConnect=new WsConnect()
    myWsConnect.init(config.port)
}

main(myConfig)