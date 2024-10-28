const http = require('http');
const fs = require('fs');
const url = require('url');

// 创建服务器
http.createServer(function (req, res) {
  // 解析请求的 URL
  const parsedUrl = url.parse(req.url, true);
  const pathName = parsedUrl.pathname;

  // 根据请求的路径处理不同的请求
  if (pathName === '/' || pathName === '/index.html') {
    // 读取前端页面文件 index.html 并返回
    fs.readFile('index.html', function(err, data) {
      if (err) {
        res.writeHead(404, {'Content-Type': 'text/html'});
        return res.end('404 Not Found');
      }
      res.writeHead(200, {'Content-Type': 'text/html'});
      res.write(data);
      return res.end();
    });
  } else {
    // 其他路径返回 404 Not Found
    res.writeHead(404, {'Content-Type': 'text/html'});
    return res.end('404 Not Found');
  }
}).listen(8000);

console.log('Server running at http://127.0.0.1:8000/');
