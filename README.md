# SOCKET-TEST
1.项目分为两个部分，一个是server端，一个是client端，server端运行后client端才能连接上，连接成功后可实现网络通信。
2.由于收发是两个不相关的部分，如果放在主线程里，就会造成只有收到一个消息之后才能发送一条消息，所以里面加入了分离线程，来实现被动的收消息，发消息还是在主线程。
3.线程部分尚不完善。
