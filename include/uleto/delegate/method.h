#ifndef ULETO_DELEGATE_METHOD_H
#define ULETO_DELEGATE_METHOD_H

#include <QtGlobal>

#include "abstract_handler.h"

namespace uleto {

namespace delegate {

template <typename MethodType>
class Method;

template <typename ReturnType, typename ObjectType, typename... ArgumentsTypes>
class Method<ReturnType(ObjectType, ArgumentsTypes...)>
    : public AbstractHandler<ReturnType(ArgumentsTypes...)> {
 public:
  typedef ReturnType (ObjectType::*MethodType)(ArgumentsTypes...);

 public:
  Method(MethodType aMethod, ObjectType *const aObject = nullptr)
      : AbstractHandler<ReturnType(ArgumentsTypes...)>(),
        mMethod(aMethod),
        mObject(aObject) {}

  virtual ~Method() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) {
    return invoke(mObject, aArgs...);
  }

  virtual ReturnType invoke(ObjectType *const aObject,
                            ArgumentsTypes... aArgs) {
    Q_ASSERT_X(aObject != nullptr, Q_FUNC_INFO, "null pointer to object");

    Q_ASSERT_X(mMethod != nullptr, Q_FUNC_INFO, "null pointer to method");

    return (aObject->*mMethod)(aArgs...);
  }

  virtual AbstractHandler<ReturnType(ArgumentsTypes...)> *clone() const {
    return dynamic_cast<AbstractHandler<ReturnType(ArgumentsTypes...)> *>(
        new Method(mMethod, mObject));
  }

 private:
  MethodType mMethod {nullptr};

  ObjectType *mObject {nullptr};
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_METHOD_H
