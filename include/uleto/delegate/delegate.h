#ifndef ULETO_DELEGATE_DELEGATE_H
#define ULETO_DELEGATE_DELEGATE_H

#include <QSharedPointer>

#include "abstract_handler.h"
#include "function.h"
#include "global.h"
#include "method.h"

namespace uleto {

namespace delegate {

template <typename ReturnType, typename... ArgumentsTypes>
class Delegate {
 public:
  using HandlerType = AbstractHandler<ReturnType, ArgumentsTypes...>;

  using FunctionType = Function<ReturnType, ArgumentsTypes...>;

  template <typename ObjectType>
  using MethodType = Method<ReturnType, ObjectType, ArgumentsTypes...>;

 public:
  Delegate() {}

  Delegate(const FunctionType &aFunction)
      : mHandler(new FunctionType(aFunction)) {}

  template <typename ObjectType>
  Delegate(const MethodType<ObjectType> &aMethod)
      : mHandler(new MethodType<ObjectType>(aMethod)) {}

  Delegate(const Delegate &aOther) = default;

  Delegate &operator=(const FunctionType &aFunction) {
    FunctionType *function{dynamic_cast<FunctionType *>(mHandler.data())};

    if (mHandler.isNull() || function == nullptr) {
      mHandler.reset(new Function<FunctionType>(aFunction));

      return *this;
      ;
    }

    *function = aFunction;

    return *this;
  };

  template <typename ObjectType>
  Delegate &operator=(const MethodType<ObjectType> &aMethod) {
    MethodType<ObjectType> *method{
        dynamic_cast<MethodType<ObjectType> *>(mHandler.data())};

    if (mHandler.isNull() || method == nullptr) {
      mHandler.reset(new MethodType<ObjectType>(aMethod));

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

    Q_ASSERT_X(handler != nullptr, Q_FUNC_INFO, "null pointer to the handler");

    return handler->invoke(aArgs...);
  }

  ReturnType operator()(ArgumentsTypes... aArgs) {
    HandlerType *handler{dynamic_cast<HandlerType *>(mHandler.data())};

    Q_ASSERT_X(handler != nullptr, Q_FUNC_INFO, "null pointer to the handler");

    return handler->invoke(aArgs...);
  }

  void clear() {
    if (isNull()) {
      return;
    }

    mHandler.clear();
  }

  bool isNull() const { return mHandler.isNull(); }

 private:
  QSharedPointer<HandlerType> mHandler;
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_DELEGATE_H
