#ifndef WSJCPP_DIFF_TEXT_H
#define WSJCPP_DIFF_TEXT_H


#include <vector>
#include <string>

class WsjcppDiffTextRow {
    public:
        WsjcppDiffTextRow(
            int nNumberOfLine, 
            std::string key, 
            std::string line
        );
        int getNumberOfLine();

        std::string key;
        std::string line;
    private:
        int m_nNumberOfLine;
};

class WsjcppDiffText {
    public:
        static void compare(
            const std::string &sText1, 
            const std::string &sText2, 
            std::vector<WsjcppDiffTextRow *> &vOutput
        );
        static void merge(
            std::string &curtxt,
            std::string &txt1,
            std::string &txt2,
            std::vector<WsjcppDiffTextRow *> &arr1,
            std::vector<WsjcppDiffTextRow *> &arr2
        );
};

#endif // WSJCPP_DIFF_TEXT_H