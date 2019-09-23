#ifndef ULETO_FUNCTIONHOLDER_H
#define ULETO_FUNCTIONHOLDER_H

#include "uletoabstractfunctionholder.h"

namespace Uleto
{

template <typename FunctionType>
class FunctionHolder;

template <typename ReturnType, typename ... ArgumentsTypes>
class FunctionHolder<ReturnType (ArgumentsTypes ...)> :
    public AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)>
{
public:
    typedef ReturnType (*FunctionType)(ArgumentsTypes ...);
public:
    FunctionHolder(FunctionType function) :
        AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)>(),
        _function(function)
    {}

    virtual ~FunctionHolder()
    {}

    virtual ReturnType invoke(ArgumentsTypes ... args)
    {
        Q_ASSERT_X(_function != nullptr, "MethodHolder::invoke",
                   "null pointer to function");
        return _function(args ...);
    }

    virtual AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)> *clone()
    {
        return dynamic_cast<AbstractFunctionHolder
                <ReturnType (ArgumentsTypes ...)> *>(
                    new FunctionHolder(_function));
    }
private:
    FunctionType _function;
};

}

#endif // ULETO_FUNCTIONHOLDER_H
