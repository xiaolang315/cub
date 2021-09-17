#include <cctest/cctest.h>
#include "cub/dci/RoleTemplate.h"

FIXTURE(DciTemplateTest) {
    struct B {
        int x = 1;
    };

    struct A : private UseRole<B> {
        int value() {
            return ROLE_ON(*this, B).x + 1;
        }
    };

    using C = Impls<DeclRoles<Impls<Compose<A, B>, B>, A>, A>;

    TEST("Can Use Role, Impl Role and Compose Role Succ") {
        C root;
        ASSERT_EQ(2, ROLE_ON(root, A).value());
    }
};