interface Config {
    port:number; // for websocket binding port default
}


const myConfig:Config={
    port: 8848,
}

export {myConfig, Config};