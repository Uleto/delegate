#ifndef ULETO_DELEGATE_ABSTRACT_HANDLER_H
#define ULETO_DELEGATE_ABSTRACT_HANDLER_H

namespace uleto {

namespace delegate {

template <typename FunctionType>
class AbstractHandler;

template <typename ReturnType, typename... ArgumentsTypes>
class AbstractHandler<ReturnType(ArgumentsTypes...)> {
 public:
  AbstractHandler() {}

  virtual ~AbstractHandler() {}

  virtual ReturnType invoke(ArgumentsTypes... aArgs) = 0;

  virtual AbstractHandler* clone() const = 0;

 private:
  AbstractHandler(const AbstractHandler& other);

  AbstractHandler& operator=(const AbstractHandler& other);
};

}  // namespace delegate

}  // namespace uleto

#endif  // ULETO_DELEGATE_ABSTRACT_HANDLER_H
