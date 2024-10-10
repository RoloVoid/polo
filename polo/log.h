// 日志库封装

#pragma once

#include <string>
#include <sstream>
#include <memory>

// 是哪个位置需要使用单例模式
#include "singleton.h"

// 封装给外部调用的宏

namespace polo
{
    class Logger;
    class LoggerManager;

    // 日志级别
    class LogLevel
    {
    public:
        // 常见的五级log结构
        enum Level
        {
            UNKNOWN = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
        using L = LogLevel::Level;
        static const char *ToString(L level);
        static L FromString(const std::string &str);
    };

    // 日志事件
    // 日志记录也是依赖于协程库的
    class LogEvent
    {
    public:
        using LL = LogLevel::Level;
        // 这里应该定义在这里方便使用
        using ptr = std::shared_ptr<LogEvent>;
        /// fiber_id 协程id
        /// elapse 程序启动依赖的耗时？
        /// time 日志时间(秒)？
        /// 虽然不太确定，此处的一个事件似乎对应这个类的实例化
        LogEvent(std::shared_ptr<Logger> logger, LL level, const char *file, int32_t line, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, uint64_t time, const std::string &thread_name);

        // 基本get函数
        const char *getFile() const { return m_file; }
        int32_t getLine() const { return m_line; }
        uint32_t getElapse() const { return m_elapse; }
        uint32_t getThreadId() const { return m_threadId; }
        uint32_t getFiberId() const { return m_fiberId; }
        uint64_t getTime() const { return m_time; }
        const std::string &getThreadName() const { return m_threadName; }
        std::shared_ptr<Logger> getLogger() const { return m_logger; }
        LogLevel::Level getLevel() const { return m_level; }
        std::stringstream &getSS() { return m_ss; }

        // 格式化方法
        void format(const char *fmt, ...);

        // 使用va_list
        void format(const char *fmt, va_list al);

    private:
        const char *m_file = nullptr;
        int32_t m_line = 0;    // 文件行号
        uint32_t m_elapse = 0; // 记录程序启动以来的时间ms
        uint32_t m_threadId = 0;
        uint32_t m_fiberId = 0;
        uint64_t m_time = 0;
        std::string m_threadName;
        std::stringstream m_ss; // 字符流用来接收日志内容
        std::shared_ptr<Logger> m_logger;
        LogLevel::Level m_level;
    };

    // 日志事件封装
    // 日志事件本身基本上是个数据类，这个封装应该是提供操作工具
    // 但觉得很多余，再观察一下 存疑
    class LogEventWrap
    {
    public:
        // 按值传递？不见得好 存疑
        LogEventWrap(LogEvent::ptr e);
        ~LogEventWrap();
        LogEvent::ptr getEvent() const { return m_event; }

        std::stringstream &getSS();

    private:
        LogEvent::ptr m_event;
    };
    // 日志格式化
    class LogFormatter
    {
    public:
        using ptr = std::shared_ptr<LogFormatter>;

        // 注意定义log格式
        LogFormatter(const std::string &pattern);
    };
    // 日志输出目标
    class LogAppender;
    class StdoutLogAppender; /// 子类：控制台输出
    class FileLogAppender;   /// 子类：文件输出
    // 日志器
    class Logger;
    // 日志管理类
    class LoggerManager;
};