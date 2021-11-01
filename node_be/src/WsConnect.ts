import { WebSocketServer, WebSocket} from 'ws';
import TemuConnect from "./TemuConnect";
type RawData=Buffer | ArrayBuffer | Buffer[]

enum wsStatus {UNREADY,READY,CLOSE}

class WsConnect {
    public constructor(){
        this.port = 0;
        this.ws=null;
        this.wsServer=null;
        this.status=wsStatus.UNREADY;
        this.temuC=null;
        this.x=null
    }
    public x:number|null;
    public temuC: TemuConnect|null;
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
        this.temuC=new TemuConnect()
        this.temuC.setWsC(this)
    }
    // private recvFromClient(message:RawData){
    //     console.log('received: %s', message);
    //     console.log(this)
    //     this.temuC?.sendMsg2Temu(message.toString())
    // }
    public init(port:number){
        this.wsServer=new WebSocketServer({ port: port });
        this.wsServer.on('connection', (ws)=>{
            this.handleOnConnect()
            this.ws=ws;
            this.ws.on('message', (message)=>{
                console.log('received: %s', message);
                // console.log(message.toString().slice(0,message.toString().length-1))
                this.temuC?.sendMsg2Temu(message.toString())
                // this.temuC?.sendMsg2Temu(message.toString())
            })
            this.ws.on('close',()=>{
                this.status=wsStatus.CLOSE
                this.temuC?.sendMsg2Temu("q")
                this.temuC=null
            })
        });
        this.x=123
        console.log("[WS] init successfully.")
    }

    public send2Client(msg:string){
        this.ws?.send(msg)
    }
}

export default WsConnect;