import { WebSocketServer, WebSocket} from 'ws';

type RawData=Buffer | ArrayBuffer | Buffer[]

class WsConnect {
    public constructor(port:number){
        this.port = port;
        this.ws=null
        this.wsServer=new WebSocketServer({ port: port });
        this.wsServer.on('connection', (ws)=>{
            WsConnect.handleOnConnect()
            this.ws=ws;
            this.ws.on('message', WsConnect.handleOnMessage)
        });
    }
    public port:number;
    public readonly wsServer:WebSocketServer;
    public ws:WebSocket|null;
    private static handleOnConnect(){
        console.log("connected")
    }
    private static handleOnMessage(message:RawData){
        console.log('received: %s', message);
    }
}

export default WsConnect;