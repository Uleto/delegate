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
  typedef AbstractHandler<ReturnType(ArgumentsTypes...)> BasicHandler;

  typedef ReturnType (ObjectType::*MethodType)(ArgumentsTypes...);

  typedef ReturnType (ObjectType::*ConstMethodType)(ArgumentsTypes...) const;

 public:
  Method(MethodType aMethod, ObjectType *const aObject = nullptr)
      : BasicHandler(), mMethod(aMethod), mObject(aObject) {}

  Method(const Method &aOther) = default;

  Method &operator=(const Method &aOther) = default;

  virtual ~Method() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) const override {
    return invoke(mObject, aArgs...);
  }

  virtual ReturnType invoke(ArgumentsTypes... aArgs) override {
    return invoke(mObject, aArgs...);
  }

  virtual ReturnType invoke(ObjectType *const aObject,
                            ArgumentsTypes... aArgs) const {
    Q_ASSERT_X(aObject != nullptr, Q_FUNC_INFO, "null pointer to object");

    Q_ASSERT_X(mMethod != nullptr, Q_FUNC_INFO, "null pointer to method");

    return (aObject->*mMethod)(aArgs...);
  }

  virtual ReturnType invoke(ObjectType *const aObject,
                            ArgumentsTypes... aArgs) {
    Q_ASSERT_X(aObject != nullptr, Q_FUNC_INFO, "null pointer to object");

    Q_ASSERT_X(mMethod != nullptr, Q_FUNC_INFO, "null pointer to method");

    return (aObject->*mMethod)(aArgs...);
  }

  virtual BasicHandler *clone() const override {
    return dynamic_cast<BasicHandler *>(new Method(mMethod, mObject));
  }

 private:
  MethodType mMethod{nullptr};

  ConstMethodType mConstMethod{nullptr};

  ObjectType *mObject{nullptr};
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_METHOD_H
