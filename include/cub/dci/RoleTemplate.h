#ifndef C1AC513D_D9CC_41E8_9098_9D88FCC80484
#define C1AC513D_D9CC_41E8_9098_9D88FCC80484

#include "cub/base/Keywords.h"

template <class T>
struct UseRole {
    ABSTRACT(T& get(T*));
};

template <class... T>
struct UseRoles;

template <class T>
struct UseRoles<T> : UseRole<T> {};

template <class T, class... Tail>
struct UseRoles<T, Tail...>
    : UseRole<T>
    , UseRoles<Tail...> {};

#define ROLE_ON(data, role) \
    (static_cast<UseRole<role>&>(data)).get((role*)nullptr)

template <class Root, class... T>
struct Impls;

template <class Root, class T>
struct Impls<Root, T> : Root {
private:
    OVERRIDE(T& get(T*)) {
        return *this;
    }
};

template <class Root, class T, class... Tail>
struct Impls<Root, T, Tail...> : Impls<Root, Tail...> {
private:
    OVERRIDE(T& get(T*)) {
        return *this;
    }
};

template <class... T>
struct Compose;

template <class T>
struct Compose<T> : protected T {};

template <class T, class... Tail>
struct Compose<T, Tail...>
    : protected T
    , protected Compose<Tail...> {};

template <class Root, class... Tail>
struct DeclRoles
    : protected Root
    , UseRoles<Tail...> {};

#endif /* C1AC513D_D9CC_41E8_9098_9D88FCC80484 */
