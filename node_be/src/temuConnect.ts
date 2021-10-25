
import {streamWrite,chunksToLinesAsync,chomp} from '@rauschma/stringio'
// const {spawn} = require('child_process');
import {spawn} from 'child_process'

function main() {
    const sink = spawn('make', ["run"],
        {stdio: ['pipe','pipe',process.stderr]}); // (A)

    writeToWritable(sink.stdin); // (B)
    echoReadable(sink.stdout)
    writeToWritable(sink.stdin); // (B)
    writeToWritable(sink.stdin);
    // await echoReadable(sink.stdout)
    // await onExit(sink);

    console.log('### DONE');
}
main();

async function writeToWritable(writable:any) {
    await streamWrite(writable, 'si 1\n');
    // await streamWrite(writable, 'q\n');
    // await streamEnd(writable);
}

async function echoReadable(readable:any) {
    for await (const line of chunksToLinesAsync(readable)) { // (C)
        console.log('LINE: '+chomp(line))
    }
}