//
//  Functor.hpp
//  Functor
//
//  Created by BlueCocoa on 2016/8/4.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#ifndef LLAMA_CPP_SRC_UTILITY_FUNCTOR_H_
#define LLAMA_CPP_SRC_UTILITY_FUNCTOR_H_

#include <functional>
#include <typeindex>
#include <typeinfo>
#include <utility>

/**
 *  @brief Template class for generating another template from lambda expression using operator()
 */
template <typename Function>
class function_traits : public function_traits<decltype(&Function::operator())> {
};

/**
 *  @brief Template class for generating corresponding std::function and function pointer to the lambda expression
 */
template <typename ClassType, typename ReturnType, typename ... Args>
class function_traits<ReturnType(ClassType::*)(Args...) const> {
public:
    typedef std::function<ReturnType(Args...)> function;
};

/**
 *  @brief Template function for getting corresponding std::function to the lambda expression
 */
template <typename Function>
constexpr typename function_traits<Function>::function to_function(const Function& lambda) {
    return static_cast<typename function_traits<Function>::function>(lambda);
}

/**
 *  @brief A general class to store lambda expression
 */
template <typename R = void>
class FunctorWrapper final {
 public:
    /**
     *  @brief Store the pointer to the function
     */
    void * _function;

    /**
     *  @brief Constructor
     *
     *  @param lambda  The lambda expression we're going to store
     *  @param exactly Should we check the signature of this function when called
     */
    template <typename Function>
    explicit FunctorWrapper(Function lambda) {
        // using decltype to new a corresponding std::function with lambda
        auto function = new decltype(to_function(lambda))(to_function(lambda));

        _function = static_cast<void *>(function);
    }

    /**
     *  @brief Deconstructor
     */
    ~FunctorWrapper() {
        delete static_cast<std::function<void()>*>(_function);
    }

    /**
     *  @brief Return value as
     */
    template <typename AS>
    FunctorWrapper<AS> as() {
        // cast _functor.function to std::function
        auto function = static_cast<std::function<AS()>*>(_function);
        return FunctorWrapper<AS>(*function);
    }

    /**
     *  @brief Function call opreator
     *
     *  @param args Any parameters your function accecpts
     */
    template <typename ... Args>
    R operator() (Args&& ... args) {
        // cast _functor.function to std::function
        auto function = static_cast<std::function<R(Args ...)>*>(_function);

        // call it
        if (!std::is_same<R, void>::value) {
            return (*function)(std::forward<Args>(args)...);
        }
        (*function)(std::forward<Args>(args)...);
    }
};

using Functor = FunctorWrapper<>;

#endif  // LLAMA_CPP_SRC_UTILITY_FUNCTOR_H_
