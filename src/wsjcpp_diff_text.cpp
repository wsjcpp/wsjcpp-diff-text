
#include "wsjcpp_diff_text.h"
#include <sstream>

namespace wsjcpp {

diff_text_row::diff_text_row(
  int number_of_line,
  const std::string &key,
  const std::string &line
) :
  m_number_of_line(number_of_line)
  , m_key(key)
  , m_line(line)
{}

int diff_text_row::getNumberOfLine() const {
  return m_number_of_line;
}

std::string diff_text_row::key() const {
  return m_key;
}

diff_text_row_action diff_text_row::action() const {
  if (m_key == "!del") {
    return diff_text_row_action::DELETE;
  }
  if (m_key == "!add") {
    return diff_text_row_action::INSERT;
  }
  if (m_key == m_line) {
    return diff_text_row_action::NONE;
  }
  return diff_text_row_action::NONE;
}

bool diff_text_row::is_delete() const {
  return action() == diff_text_row_action::DELETE;
}

bool diff_text_row::is_insert() const {
  return action() == diff_text_row_action::INSERT;
}

std::string diff_text_row::line() const {
  return m_line;
}

void diff_text_split(const std::string &text, std::vector<std::string> &output) {
  std::istringstream is_text(text);
  std::string line = "";
  while (getline(is_text, line, '\n')) {
    output.push_back(line);
  }
}

void diff_text_compare(
  const std::string &text_left,
  const std::string &text_right,
  std::vector<diff_text_row> &output_diff
) {
  std::vector<std::string> list_left;
  diff_text_split(text_left, list_left);

  std::vector<std::string> list_right;
  diff_text_split(text_right, list_right);

  std::vector<std::string> sWord;
  sWord.push_back("!add");
  sWord.push_back("!del");

  int len1 = list_left.size();
  int len2 = list_right.size();
  int i = 0, j = 0;
  //main comparisons
  while ((i<len1) && (j<len2)) {
    if (list_left[i] != list_right[j]) {
      // checkout for added rows
      for (int k = j + 1; k < len2; ++k) {
        if (list_left[i] == list_right[k]) {
          while (j<k) {
            output_diff.push_back(diff_text_row(j, sWord.at(0), list_right.at(j)));
            j++;
          }
          goto exit;
        }
      }
      // checkout for deleted rows
      for (int k = i + 1; k < len1; ++k) {
        if (list_left[k] == list_right[j]) {
          while (i<k) {
            output_diff.push_back(diff_text_row(i, sWord.at(1), list_left.at(i)));
            i++;
          }
          goto exit;
        }
      }
      output_diff.push_back(diff_text_row(i, list_left.at(i), list_right.at(j)));
      exit:;
    }
    i++, j++;
  }
  //work with the end of the texts
  while (j < len2) {
    output_diff.push_back(diff_text_row(j, sWord.at(0), list_right.at(j)));
    j++;
  }
  while (i < len1) {
    output_diff.push_back(diff_text_row(i, sWord.at(1), list_left.at(i)));
    i++;
  }
}

void diff_text_merge(
  std::string &curtxt,
  std::string &txt1,
  std::string &txt2,
  std::vector<diff_text_row> &arr1,
  std::vector<diff_text_row> &arr2
) {
  diff_text_compare(txt1, txt2, arr1);
  diff_text_compare(txt1, curtxt, arr2);
  for (unsigned int i = 0; i < arr2.size(); ++i) {
    for (unsigned int j = 0; j < arr1.size(); ++j) {
      //delete of matches and 'del'/'add' overlays from the first vector
      bool bLinesEqual = arr2[i].line() == arr1[j].line();
      bool bKeysEqual = arr2[i].key() == arr1[j].line(); // TODO why comparing key and line ???
      std::string sKey1 = arr1[j].key();
      std::string sKey2 = arr2[i].key();
      if (
        (bLinesEqual && (sKey1 == sKey2 || sKey1 == "!add"))
        || (bKeysEqual && (sKey1 == "!del"))
      ) {
        arr1.erase(arr1.begin()+j);
        break;
      }
    }
  }
  for (unsigned int i = 0; i < arr1.size(); ++i) {
    for (unsigned int j = 0; j < arr2.size(); ++j) {
      //delete of del overlays from the second vector and update of priority
      bool bLinesEqual = arr1[i].key() == arr2.at(j).line(); // TODO check why comparing key and line here ?
      bool bKeysEqual = arr1.at(i).key() == arr2.at(j).key();
      std::string sKey = arr2.at(j).key();
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
    for (unsigned int j = arr1.size() - 1; j > i; --j) {
      if (arr1.at(j-1).getNumberOfLine() > arr1.at(j).getNumberOfLine()) {
        // TODO redesign
        std::swap(arr1.at(j-1), arr1.at(j));
      }
    }
  }
}

} // namespace wsjcpp
