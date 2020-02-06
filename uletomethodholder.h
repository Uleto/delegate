#ifndef ULETO_METHODHOLDER_H
#define ULETO_METHODHOLDER_H

#include <QtGlobal>

#include "uletoabstractfunctionholder.h"

namespace Uleto
{

template <typename FunctionType>
class MethodHolder;

template <typename ReturnType, typename ObjectType, typename ... ArgumentsTypes>
class MethodHolder<ReturnType (ObjectType, ArgumentsTypes ...)> :
    public AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)>
{
public:
    typedef ReturnType (ObjectType::*FunctionType)(ArgumentsTypes ...);
public:
    MethodHolder(FunctionType function, ObjectType *object = nullptr) :
        AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)>(),
        _function(function),
        _object(object)
    {}

    virtual ~MethodHolder()
    {}

    virtual ReturnType invoke(ArgumentsTypes ... args)
    {
        return invoke(_object, args ...);
    }

    virtual ReturnType invoke(ObjectType *object, ArgumentsTypes ... args)
    {
        Q_ASSERT_X(object != nullptr, Q_FUNC_INFO, "null pointer to object");

        Q_ASSERT_X(_function != nullptr, Q_FUNC_INFO,
                   "null pointer to function");

        return (object->*_function)(args ...);
    }

    virtual AbstractFunctionHolder<ReturnType (ArgumentsTypes ...)> *clone()
    {
        return dynamic_cast<AbstractFunctionHolder
                <ReturnType (ArgumentsTypes ...)> *>(
                    new MethodHolder(_function, _object));
    }
private:
    FunctionType _function;
    ObjectType *_object;
};

}

#endif // ULETO_METHODHOLDER_H
