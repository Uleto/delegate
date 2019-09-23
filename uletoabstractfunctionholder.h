#ifndef ULETO_ABSTRACTFUNCTIONHOLDER_H
#define ULETO_ABSTRACTFUNCTIONHOLDER_H

namespace Uleto
{

template <typename FunctionType>
class AbstractFunctionHolder;

template <typename ReturnType, typename ... ArgumentsTypes>
class AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)>
{
public:
    AbstractFunctionHolder()
    {}

    virtual ~AbstractFunctionHolder()
    {}

    virtual ReturnType invoke(ArgumentsTypes ... args) = 0;
    virtual AbstractFunctionHolder *clone() = 0;
private:
    AbstractFunctionHolder(const AbstractFunctionHolder &other);
    AbstractFunctionHolder &operator=(const AbstractFunctionHolder &other);
};

}

#endif // ULETO_ABSTRACTFUNCTIONHOLDER_H
