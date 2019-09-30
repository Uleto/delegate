#ifndef ULETO_DELEGATE_H
#define ULETO_DELEGATE_H

#include "uletodelegate_global.h"

#include <QScopedPointer>

#include "uletoabstractfunctionholder.h"
#include "uletofunctionholder.h"
#include "uletomethodholder.h"

namespace Uleto
{

template <typename FunctionType>
class ULETO_DELEGATESHARED_EXPORT Delegate;

template <typename ReturnType, typename ... ArgumentsTypes>
class ULETO_DELEGATESHARED_EXPORT Delegate<ReturnType (ArgumentsTypes ...)>
{
public:
    Delegate()
    {}

    template <typename FunctionType>
    Delegate(FunctionType function) :
        _functionHolder(new FunctionHolder<ReturnType (ArgumentsTypes ...)>(
                            function))
    {}

    template <typename ObjectType, typename FunctionType>
    Delegate(ObjectType *object, FunctionType function) :
        _functionHolder(new MethodHolder
                        <ReturnType (ObjectType, ArgumentsTypes ...)>(
                            function, object))
    {}

    virtual ~Delegate()
    {}

    ReturnType operator()(ArgumentsTypes ... args)
    {
        Q_ASSERT_X(!_functionHolder.isNull(), "Delegate::operator()",
                   "function not specified");
        return _functionHolder->invoke(args ...);
    }

    bool isValid() const
    {
        return !_functionHolder.isNull();
    }
private:
    QScopedPointer<AbstractFunctionHolder
            <ReturnType (ArgumentsTypes ...)>> _functionHolder;
};

}

#endif // ULETO_DELEGATE_H
