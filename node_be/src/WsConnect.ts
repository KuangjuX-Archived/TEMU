import { WebSocketServer, WebSocket} from 'ws';
import TemuConnect from "./TemuConnect";
type RawData=Buffer | ArrayBuffer | Buffer[]

enum wsStatus {UNREADY,READY}

class WsConnect {
    public constructor(){
        this.port = 0;
        this.ws=null;
        this.wsServer=null;
        this.status=wsStatus.UNREADY;
        this.temuC=null;
    }
    private temuC: TemuConnect|null;
    public port:number;
    public wsServer:WebSocketServer|null;
    public ws:WebSocket|null;
    public status:wsStatus;

    public setTemuC(temuC:TemuConnect){
        this.temuC=temuC;
    }

    private handleOnConnect(){
        console.log("connected")
        this.status=wsStatus.READY;
    }
    private static recvFromClient(message:RawData){
        console.log('received: %s', message);
    }
    public init(port:number){
        this.wsServer=new WebSocketServer({ port: port });
        this.wsServer.on('connection', (ws)=>{
            this.handleOnConnect()
            this.ws=ws;
            this.ws.on('message', WsConnect.recvFromClient)
        });
    }

    public send2Client(msg:string){
        this.ws?.send(msg)
    }
}

export default WsConnect;