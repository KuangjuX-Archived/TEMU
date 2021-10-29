
import {streamWrite,chunksToLinesAsync,chomp} from '@rauschma/stringio'
import WsConnect from "./WsConnect";
import {spawn} from 'child_process'

class TemuConnect{
    public constructor() {
        this.temuProcess=spawn('make', ["run"], {stdio: ['pipe','pipe',process.stderr]});
        this.echoReadable()
        this.wsC=null;
    }
    private temuProcess;
    private wsC:WsConnect|null;

    public setWsC(wsC:WsConnect){
        this.wsC=wsC;
    }

    public sendMsg2Temu(msg:string){
        this.writeToWritable(msg)
    }

    private async echoReadable() {
        for await (const line of chunksToLinesAsync(this.temuProcess.stdout)) {
            let line_s=chomp(line)
            console.log('LINE: '+line_s)
            this.wsC?.send2Client(line_s)
        }
    }
    private async writeToWritable(msg:string) {
        await streamWrite(this.temuProcess.stdin, msg+'\n');
    }
}

export default TemuConnect;