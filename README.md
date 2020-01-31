# java Web 项目 
项目名称 mynews_client 
>考虑到这个项目是一个小型的网站开发项目。之前有开发过购物网站的经验，在DAO层需要连接数据库。而作为项目负责任的我学过 hibernate 跟 Mybatis 考虑到该课程设计的需求不大。我最终选择Apache 组织提供的一个开源 JDBC工具类库，commons-dbutils 来连接数据库，以及c3p0 数据库连接池。一个简单的小项目 。项目包裹前端新闻界面 以及后端管理员界面 前端界面可以查看新闻 后端界面 提供管理员 管理新闻`
# Android Demo
>安卓socket 的一个小案例，通过socket连接树莓派网管 发送数据，树莓派接收到数据操纵GPIO输出高低电平控制继电器开关
# Shell Code
> 整理了一些非常基础的Shell编程代码 

# python Test
> python 学习中的小测试代码 方便学习python

# esp
> WIFIManualWebServer 是 通过 http请求 控制led的亮灭 
> blinker_app_xiaoai 是通过 Blinker平台 实现 远端控制led的开关（MQTT协议以及wifi内网）并且 连接小爱同学语音控制
# mqtt 
> 基于mqtt协议 开发的远程遥控 esp-01s芯片 配合 继电器 实现 远程开灯 

利用 PubSubClient 实现esp 开发板的mqtt协议开发
利用mqtt client jar包开发安卓端 
服务器 采用emqx 开发 
# zigbee
>两个zigbee路由节点采集数据 发送到协调节点 协调节点通过串口发给树莓派 树莓派与Android建立TCP连接 传输数据
