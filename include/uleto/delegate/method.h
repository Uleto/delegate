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
  Method(ConstMethodType aConstMethod,
         const ObjectType *const aObject = nullptr)
      : BasicHandler(), mConstMethod(aConstMethod), mConstObject(aObject) {}

  Method(MethodType aMethod, ObjectType *const aObject = nullptr)
      : BasicHandler(), mMethod(aMethod), mObject(aObject) {}

  Method(MethodType aMethod, ConstMethodType aConstMethod,
         ObjectType *const aObject = nullptr)
      : BasicHandler(),
        mMethod(aMethod),
        mConstMethod(aConstMethod),
        mObject(aObject) {}

  Method(const Method &aOther) = default;

  Method &operator=(const Method &aOther) = default;

  virtual ~Method() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) const override {
    if (mObject != nullptr) {
      return invoke(mObject, aArgs...);
    }

    return invoke(mConstObject, aArgs...);
  }

  virtual ReturnType invoke(ArgumentsTypes... aArgs) override {
    if (mObject != nullptr) {
      return invoke(mObject, aArgs...);
    }

    return invoke(mConstObject, aArgs...);
  }

  virtual ReturnType invoke(const ObjectType *const aObject,
                            ArgumentsTypes... aArgs) const {
    Q_ASSERT_X(aObject != nullptr, Q_FUNC_INFO, "null pointer to the object");

    Q_ASSERT_X(mConstMethod != nullptr, Q_FUNC_INFO,
               "null pointer to the const method");

    return (aObject->*mConstMethod)(aArgs...);
  }

  virtual ReturnType invoke(ObjectType *const aObject,
                            ArgumentsTypes... aArgs) const {
    Q_ASSERT_X(aObject != nullptr, Q_FUNC_INFO, "null pointer to the object");

    Q_ASSERT_X(mConstMethod != nullptr, Q_FUNC_INFO,
               "null pointer to the const method");

    return (aObject->*mConstMethod)(aArgs...);
  }

  virtual ReturnType invoke(ObjectType *const aObject,
                            ArgumentsTypes... aArgs) {
    Q_ASSERT_X(aObject != nullptr, Q_FUNC_INFO, "null pointer to the object");

    Q_ASSERT_X(mMethod != nullptr || mConstMethod != nullptr, Q_FUNC_INFO,
               "null pointer to the method");

    return mMethod != nullptr ? (aObject->*mMethod)(aArgs...)
                              : (aObject->*mConstMethod)(aArgs...);
  }

  virtual BasicHandler *clone() const override {
    return dynamic_cast<BasicHandler *>(new Method(mMethod, mObject));
  }

 private:
  MethodType mMethod{nullptr};

  ConstMethodType mConstMethod{nullptr};

  ObjectType *mObject{nullptr};

  const ObjectType *mConstObject{nullptr};
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_METHOD_H
