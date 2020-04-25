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
  typedef ReturnType (*FunctionType)(ArgumentsTypes...);

 public:
  Function(FunctionType aFunction)
      : AbstractHandler<ReturnType(ArgumentsTypes...)>(),
        mFunction(aFunction) {}

  virtual ~Function() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) {
    Q_ASSERT_X(mFunction != nullptr, Q_FUNC_INFO, "null pointer to function");

    return mFunction(aArgs...);
  }

  virtual AbstractHandler<ReturnType(ArgumentsTypes...)> *clone() const {
    return dynamic_cast<AbstractHandler<ReturnType(ArgumentsTypes...)> *>(
        new Function(mFunction));
  }

 private:
  FunctionType mFunction{nullptr};
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_FUNCTION_H
