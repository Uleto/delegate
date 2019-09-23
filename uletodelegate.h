#ifndef ULETO_DELEGATE_H
#define ULETO_DELEGATE_H

#include "uletodelegate_global.h"

#include <QScopedPointer>

#include "uletoabstractfunctionholder.h"
#include "uletofunctionholder.h"

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

    template <typename F2unctionType>
    Delegate(F2unctionType f2unction) :
        _functionHolder(new FunctionHolder<ReturnType (ArgumentsTypes ...)>(
                            f2unction))
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
