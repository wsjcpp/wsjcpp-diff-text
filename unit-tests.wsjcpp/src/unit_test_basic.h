#ifndef UNIT_TEST_BASIC_H
#define UNIT_TEST_BASIC_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestBasic : public WsjcppUnitTestBase {
    public:
        UnitTestBasic();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
    private:
        std::string text001();
        std::string text002();
};

#endif // UNIT_TEST_BASIC_H

