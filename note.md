# 基于sylar的高性能服务器

* <https://github.com/sylar-yin/sylar>

## 基本框架

* 日志系统
* 封装协程库
* socket函数库
* http协议开发
* 分布协议
* 推荐系统

### 日志系统

* 类似于log4j的设计

* Logger -- formatter -- Appender 对日志划分五个级别
* Logger：定义日志种类
* formatter：定义日志格式
* Appender：定义日志输出位置
