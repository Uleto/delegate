#ifndef ULETO_DELEGATE_DELEGATE_H
#define ULETO_DELEGATE_DELEGATE_H

#include <QScopedPointer>

#include "abstract_handler.h"
#include "function.h"
#include "global.h"
#include "method.h"

namespace uleto {

namespace delegate {

template <typename FunctionType>
class Delegate;

template <typename ReturnType, typename... ArgumentsTypes>
class Delegate<ReturnType(ArgumentsTypes...)> {
 public:
  Delegate() {}

  template <typename FunctionType>
  Delegate(FunctionType aFunction)
      : mHandler(new Function<ReturnType(ArgumentsTypes...)>(aFunction)) {}

  template <typename ObjectType, typename MethodType>
  Delegate(ObjectType *const aObject, MethodType aMethod)
      : mHandler(new Method<ReturnType(ObjectType, ArgumentsTypes...)>(
            aMethod, aObject)) {}

  virtual ~Delegate() {}

  ReturnType operator()(ArgumentsTypes... aArgs) {
    Q_ASSERT_X(!mHandler.isNull(), Q_FUNC_INFO, "null pointer to handler");

    return mHandler->invoke(aArgs...);
  }

  bool isValid() const { return !mHandler.isNull(); }

 private:
  QScopedPointer<AbstractHandler<ReturnType(ArgumentsTypes...)>> mHandler;
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_DELEGATE_H
