// 封装单例模式
// 参见cpp basic 单例模式

#pragma once

#include <memory>

namespace polo
{
    // 使用静态变量实现的单例模式
    template <typename T, typename X, int N>
    T &GetInstanceX()
    {
        static T v;
        return v;
    }

    template <typename T, typename X, int N>
    std::shared_ptr<T> GetInstancePtr()
    {
        /// 此处为什么不使用make_shared
        /// 应该更好，没有理由不用
        // static std::shared_ptr<T> v(new T);
        static std::shared_ptr<T> v = std::make_shared<T>();
        return v;
    }

    // 封装单例模式
    // 返回裸指针
    template <typename T, typename X = void, int N = 0>
    class Singleton
    {
    public:
        static T *GetInstance()
        {
            static T v;
            return &v;
        }
    };

    // 智能指针封装
    template <typename T, typename X = void, int N = 0>
    class SingletonPtr
    {
    public:
        static std::shared_ptr<T> GetInstance()
        {
            // static std::shared_ptr<T> v(new T);
            // 此处也用make_shared会怎样
            static std::shared_ptr<T> v = std::make_shared<T>();
            return v;
        }
    };
}