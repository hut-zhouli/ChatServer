# ChatServer
可以工作在nginx tcp负载均衡环境的集群聊天系统，基于muduo实现以及Redis中间件

#编译方式
cd ./build
rm -rf *
cmake ..
make


需要nginx的负载均衡以及启动redis服务，添加muduo库，启动mysql
客户端连接服务器地址为：127.0.0.1 8000
nginx两个服务器地址：127.0.0.1 8888以及127.0.0.1 8889
