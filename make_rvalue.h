#ifndef MAKE_RVALUE_H
#define MAKE_RVALUE_H

template <class T, class... U>
T make_rvalue(U&&... args) {
    T rvalue(std::forward<U>(args)...);

    return std::move(rvalue);
}

#endif // MAKE_RVALUE_H
