const stdin = process.stdin;
const stdout = process.stdout;


console.log('hello world!');

stdin.on('data',function(data){

	console.log(`输入了:${data}`);
});

stdin.resume();


