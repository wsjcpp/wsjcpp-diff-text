
#include "wsjcpp_diff_text.h"
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppDiffTextRow

WsjcppDiffTextRow::WsjcppDiffTextRow(
    int nNumberOfLine,
    const std::string &sKey,
    const std::string &sLine
) {
    m_nNumberOfLine = nNumberOfLine;
    m_sKey = sKey; 
    m_sLine = sLine;
}

// ---------------------------------------------------------------------

int WsjcppDiffTextRow::getNumberOfLine() {
    return m_nNumberOfLine;
}

// ---------------------------------------------------------------------

std::string WsjcppDiffTextRow::getKey() {
    return m_sKey;
}

// ---------------------------------------------------------------------

std::string WsjcppDiffTextRow::getLine() {
    return m_sLine;
}

// ---------------------------------------------------------------------
// WsjcppDiffText

void WsjcppDiffText::compare(
    const std::string &sText1, 
    const std::string &sText2, 
    std::vector<WsjcppDiffTextRow *> &vOutput
) {
    std::vector<std::string> list1;
    std::istringstream isTxt1(sText1);
    std::string sLine = "";
    while (getline(isTxt1, sLine, '\n')) {
        list1.push_back(sLine);
    }

    std::vector<std::string> list2;
    std::istringstream isTxt2(sText2);
    sLine = "";
    while (getline(isTxt2, sLine, '\n')) {
        list2.push_back(sLine);
    }

    std::vector<std::string> sWord;
    sWord.push_back("!add");
    sWord.push_back("!del");

    int len1 = list1.size();
    int len2 = list2.size();
    int i=0, j=0;
    //main comparisons
    while ((i<len1) && (j<len2)) {
        if (list1[i] != list2[j]) {
            //checkout for added rows
            for (int k = j + 1; k < len2; ++k) {
                if (list1[i] == list2[k]) {
                    while (j<k) {
                        vOutput.push_back(new WsjcppDiffTextRow(j, sWord.at(0), list2.at(j)));
                        j++;
                    }
                    goto exit;
                }
            }
            //checkout for deleted rows
            for (int k=i+1;k<len1;++k) {
                if (list1[k]==list2[j]) {
                    while (i<k) {
                        vOutput.push_back(new WsjcppDiffTextRow(i, sWord.at(1), list1.at(i)));
                        i++;
                    }
                    goto exit;
                }
            }
            vOutput.push_back(new WsjcppDiffTextRow(i, list1.at(i), list2.at(j)));
            exit:;
        }
        i++, j++;
    }
    //work with the end of the texts
    while (j<len2) {
        vOutput.push_back(new WsjcppDiffTextRow(j, sWord.at(0), list2.at(j)));
        j++;
    }
    while (i<len1) {
        vOutput.push_back(new WsjcppDiffTextRow(i, sWord.at(1), list1.at(i)));
        i++;
    }
}

// ---------------------------------------------------------------------

void WsjcppDiffText::merge(
    std::string &curtxt,
    std::string &txt1,
    std::string &txt2,
    std::vector<WsjcppDiffTextRow *> &arr1,
    std::vector<WsjcppDiffTextRow *> &arr2
) {
    WsjcppDiffText::compare(txt1, txt2, arr1);
    WsjcppDiffText::compare(txt1, curtxt, arr2);
    for (unsigned int i=0;i<arr2.size();++i) {
        for (unsigned int j=0;j<arr1.size();++j) {
            //delete of matches and 'del'/'add' overlays from the first vector
            bool bLinesEqual = arr2.at(i)->getLine() == arr1.at(j)->getLine();
            bool bKeysEqual = arr2.at(i)->getKey() == arr1.at(j)->getLine(); // TODO why comparing key and line ???
            std::string sKey1 = arr1.at(j)->getKey();
            std::string sKey2 = arr2.at(i)->getKey();
            if ((bLinesEqual && (sKey1 == sKey2 || sKey1 == "!add"))
                    || (bKeysEqual && (sKey1 == "!del")))
            {
                arr1.erase(arr1.begin()+j);
                break;
            }
        }
    }
    for (unsigned int i = 0; i < arr1.size(); ++i) {
        for (unsigned int j = 0; j < arr2.size(); ++j) {
            //delete of del overlays from the second vector and update of priority
            bool bLinesEqual = arr1.at(i)->getKey() == arr2.at(j)->getLine(); // TODO check why comparing key and line here ?
            bool bKeysEqual = arr1.at(i)->getKey() == arr2.at(j)->getKey();
            std::string sKey = arr2.at(j)->getKey();
            if ((bLinesEqual && (sKey == "!del"))
                    || (bKeysEqual && (sKey != "!add") && (sKey != "!del")))
            {
                arr2.erase(arr2.begin()+j);
                break;
            }
        }
    }
    // merge and sort vectors
    arr1.reserve(arr1.size()+arr2.size());
    arr1.insert(arr1.end(),arr2.begin(),arr2.end());
    for (unsigned int i=0; i < arr1.size(); ++i) {
        for (unsigned int j = arr1.size()-1; j > i; --j) {
            if (arr1.at(j-1)->getNumberOfLine() > arr1.at(j)->getNumberOfLine()) {
                // TODO redesign
                std::swap(arr1.at(j-1), arr1.at(j));
            }
        }
    }
}
