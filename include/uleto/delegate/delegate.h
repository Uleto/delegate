#ifndef ULETO_DELEGATE_DELEGATE_H
#define ULETO_DELEGATE_DELEGATE_H

#include <QSharedPointer>

#include "abstract_handler.h"
#include "function.h"
#include "global.h"
#include "method.h"

namespace uleto {

namespace delegate {

template <typename HandlerType>
class Delegate;

template <typename ReturnType, typename... ArgumentsTypes>
class Delegate<ReturnType(ArgumentsTypes...)> {
 public:
  typedef AbstractHandler<ReturnType(ArgumentsTypes...)> HandlerType;

 public:
  Delegate() {}

  template <typename FunctionType>
  Delegate(const Function<FunctionType> &aFunction)
      : mHandler(new Function<FunctionType>(aFunction)) {}

  template <typename MethodType>
  Delegate(const Method<MethodType> &aMethod)
      : mHandler(new Method<MethodType>(aMethod)) {}

  Delegate(const Delegate &aOther) = default;

  template <typename FunctionType>
  Delegate &operator=(const Function<FunctionType> &aFunction) {
    Function<FunctionType> *function{
        dynamic_cast<Function<FunctionType> *>(mHandler.data())};

    if (mHandler.isNull() || function == nullptr) {
      mHandler.reset(new Function<FunctionType>(aFunction));

      return *this;
      ;
    }

    *function = aFunction;

    return *this;
  };

  template <typename MethodType>
  Delegate &operator=(const Method<MethodType> &aMethod) {
    Method<MethodType> *method{
        dynamic_cast<Method<MethodType> *>(mHandler.data())};

    if (mHandler.isNull() || method == nullptr) {
      mHandler.reset(new Method<MethodType>(aMethod));

      return *this;
      ;
    }

    *method = aMethod;

    return *this;
  };

  Delegate &operator=(const Delegate &aOther) = default;

  virtual ~Delegate() {}

  ReturnType operator()(ArgumentsTypes... aArgs) const {
    const HandlerType *handler{
        dynamic_cast<const HandlerType *>(mHandler.data())};

    Q_ASSERT_X(handler != nullptr, Q_FUNC_INFO, "null pointer to handler");

    return handler->invoke(aArgs...);
  }

  ReturnType operator()(ArgumentsTypes... aArgs) {
    HandlerType *handler{dynamic_cast<HandlerType *>(mHandler.data())};

    Q_ASSERT_X(handler != nullptr, Q_FUNC_INFO, "null pointer to handler");

    return handler->invoke(aArgs...);
  }

  bool isNull() const { return mHandler.isNull(); }

 private:
  QSharedPointer<HandlerType> mHandler;
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_DELEGATE_H
