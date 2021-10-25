import WsConnect from "./WsConnect";
import {myConfig,Config} from "./config";

function main(config:Config):void{
    let myWsConnect=new WsConnect(config.port)
}

main(myConfig)
console.log("stated")