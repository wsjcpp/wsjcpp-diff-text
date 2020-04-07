#ifndef UNIT_TEST_BASIC_H
#define UNIT_TEST_BASIC_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestBasic : public WsjcppUnitTestBase {
    public:
        UnitTestBasic();
        virtual void init();
        virtual bool run();
    private:
        std::string text001();
        std::string text002();
};

#endif // UNIT_TEST_BASIC_H

