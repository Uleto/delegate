#ifndef ULETO_DELEGATE_FUNCTION_H
#define ULETO_DELEGATE_FUNCTION_H

#include <QtGlobal>

#include "abstract_handler.h"

namespace uleto {

namespace delegate {

template <typename FunctionType>
class Function;

template <typename ReturnType, typename... ArgumentsTypes>
class Function<ReturnType(ArgumentsTypes...)>
    : public AbstractHandler<ReturnType(ArgumentsTypes...)> {
 public:
  typedef AbstractHandler<ReturnType(ArgumentsTypes...)> BasicHandler;

  typedef ReturnType (*FunctionType)(ArgumentsTypes...);

 public:
  Function(FunctionType aFunction) : BasicHandler(), mFunction(aFunction) {}

  Function(const Function &aOther) = default;

  Function &operator=(const Function &aOther) = default;

  virtual ~Function() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) const override {
    Q_ASSERT_X(mFunction != nullptr, Q_FUNC_INFO, "null pointer to function");

    return mFunction(aArgs...);
  }

  virtual ReturnType invoke(ArgumentsTypes... aArgs) override {
    Q_ASSERT_X(mFunction != nullptr, Q_FUNC_INFO, "null pointer to function");

    return mFunction(aArgs...);
  }

  virtual BasicHandler *clone() const override {
    return dynamic_cast<BasicHandler *>(new Function(mFunction));
  }

 private:
  FunctionType mFunction{nullptr};
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_FUNCTION_H
