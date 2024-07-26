#include <iostream>
#include <map>
#include <regex>

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

std::string input_word(std::string number) {
  std::regex control_letter("([A-Za-z]+)");
  std::string word;

  do {
    std::cout << "Input " << number << " word: ";
    std::cin >> word;
    if (!std::regex_match(word.c_str(), control_letter)) {
      std::cout << "The word must consist only of letters\n";
    }
  } while (!std::regex_match(word.c_str(), control_letter));
  word = lower_case(word);
  return word;
}

std::multimap <char, char> add_word_in_map (std::string wordOne) {
  std::multimap<char, char> word_map;
  int wordLen = wordOne.length();
  for (int i = 0; i < wordLen; i++) {
    word_map.insert({wordOne[i], wordOne[i]});
  }
  return word_map;
}

bool anagram_check(std::string wordOne, std::string wordTwo) {
  if (wordOne.length() != wordTwo.length()) return false;

  std::multimap<char, char> words_check;
  words_check = add_word_in_map(wordOne);
  
  int wordLen = wordOne.length();
  for (int i = 0; i < wordLen; i++) {
    if (words_check.find(wordTwo[i]) != words_check.end()) {
      int count_letter = words_check.count(wordTwo[i]);

      words_check.erase(wordTwo[i]);
      words_check.insert({'*', wordTwo[i]}); //значение по ключу для удобства отладки

      for (int j = 0; j < count_letter - 1; j++) {
        words_check.insert({wordTwo[i], j});
      }
    } else {
        return false;
    }
  }
  return true;
}
int main() {
  std::cout << "Checking two words for an anagram\n";
  std::string wordOne = input_word("first");
  std::string wordTwo = input_word("Second");

  if (anagram_check(wordOne, wordTwo))
    std::cout << "The words are an anagram\n";
  else
    std::cout << "The words are not an anagram\n";
}