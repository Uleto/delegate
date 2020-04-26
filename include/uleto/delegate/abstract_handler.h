#ifndef ULETO_DELEGATE_ABSTRACT_HANDLER_H
#define ULETO_DELEGATE_ABSTRACT_HANDLER_H

namespace uleto {

namespace delegate {

template <typename ReturnType, typename... ArgumentsTypes>
class AbstractHandler {
 public:
  AbstractHandler() {}

  AbstractHandler(const AbstractHandler& aOther) = default;

  AbstractHandler& operator=(const AbstractHandler& aOther) = default;

  virtual ~AbstractHandler() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) const = 0;

  virtual ReturnType invoke(ArgumentsTypes... aArgs) = 0;

  virtual AbstractHandler* clone() const = 0;
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_ABSTRACT_HANDLER_H
