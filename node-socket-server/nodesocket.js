const net = require('net');
const http = require('http');
const port = 8080;
const hostname = '127.0.0.1'
const httpPort = 8081;

const stdin = process.stdin
const stdout = process.stdout

// 定义两个变量， 一个用来计数，一个用来保存客户端
let clients = {};
let clientName = 0;

// 创建服务器
const server = new net.createServer();


server.on('connection', (client) => {
  client.name = ++clientName; // 给每一个client起个名
  clients[client.name] = client; // 将client保存在clients

  client.on('data', function (msg) { //接收client发来的信息
		const head = Buffer.from(msg,0, 20);
		const body = msg.slice(20,msg.length);
    console.log(`客户端${client.name}发来一个信息：${body}`);
		var result = `服务端返回消息：${body.toString()}`;
		console.log(result);
		client.write(result);
  });

  client.on('error', function (e) { //监听客户端异常
    console.log('client error' + e);
    client.end();
  });

  client.on( 'close', function () {
    delete clients[client.name];
    console.log(`客户端${ client.name }下线了`);
  });

});
server.listen( port,hostname,function () {
  console.log(`服务器运行在：http://${hostname}:${port}`);
});


var httpServer = new http.Server();
httpServer.on("request",function(request, response){
//	var params = url.parse(request,url,true).query;
	console.log(request.url);

	response.writeHeader(200, {
    "Content-Type" : "text/plain"
  	});
	if(clients[1]){
		clients[1].write(request.url);
		response.write("发送到聊天室成功");
	}else{
		response.write("客户端未连接");
	}

	response.end();
});

httpServer.listen(httpPort);

stdin.on('data',function(data){
	if(data == ''||data ==undefined){
			return ;
	}
	console.log('输入了：'+ data);	
	for(var item in clients){
		if(item == undefined){
			return ;
		}
		clients[item].write(data);
	}
});

stdin.resume();

