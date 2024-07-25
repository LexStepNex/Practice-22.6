#include <iostream>
#include <map>
#include <regex>  // добавлен чисто для контроля ввода
#include <string>
#include <vector>
struct book {
  std::map<std::string, std::string> surname_by_phone;
  std::map<std::string, std::vector<std::string>> phone_by_surname;

  void add(std::string phone, std::string surname) {
    if (surname_by_phone.count(phone) == 0) {
      surname_by_phone.insert({phone, surname});
      phone_by_surname[surname].push_back(phone);
      std::cout << "Phone number added successfully\n";
    } else {
      std::cout << "This phone number has already been provided before\n";
    }
  }

  void find_by_phone(std::string phone) {
    if (surname_by_phone.find(phone) != surname_by_phone.end()) {
      std::cout << "Phone number: " << surname_by_phone.find(phone)->first
                << " subscriber with surname: " << surname_by_phone[phone]
                << "\n";
    } else {
      std::cout << "This phone number was not found\n";
    }
  }

  void find_by_surname(std::string surname) {
    if (phone_by_surname.find(surname) != phone_by_surname.end()) {
      int amount_phones = phone_by_surname[surname].size();

      std::cout << "Phone numbers found for the last name "
                << phone_by_surname.find(surname)->first << ": \n";
      for (int i = 0; i < amount_phones; i++) {
        std::cout << phone_by_surname[surname][i] << "\n";
      }
    } else {
      std::cout << "This surname was not found\n";
    }
  }
};

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

void request(std::string& phone, std::string& surname) {
  using namespace std;

  cout << "Types of requests:\n";
  cout << "1)Input your phone number and last name to add them to your phone "
       << "directory.\n";
  cout << "Example: \"44-22-11 Smit\"\n";
  cout << "2)Input a phone number to find a last name by phone number.\n"
       << "Example: \"44-44-41\"\n";
  cout << "3)Input a last name to find a subscriber by last name.\n"
       << "Example: \"Potter\"\n\n";

  cout << "Input you request: ";
  std::string answer;
  if (phone != "first") std::cin.ignore();
  phone = "", surname = "";
  std::getline(std::cin, answer);

  regex phone_rgx("(\\d+\\-?\\d+\\-?\\d+)");
  cmatch result_phone;
  regex surname_rgx("([A-Za-z]+)");
  cmatch result_surname;

  if (regex_search(answer.c_str(), result_phone, phone_rgx) &&
      regex_search(answer.c_str(), result_surname, surname_rgx)) {
    phone = result_phone[1];
    surname = result_surname[1];
    return;
  }

  if (regex_match(answer.c_str(), phone_rgx)) {
    phone = answer;
    return;
  }

  if (regex_match(answer.c_str(), surname_rgx)) {
    surname = answer;
    return;
  }
}

bool repeat() {
  std::string answer;
  std::cout << "Do you want to continue working with the book?\n";
  do {
    std::cout << "Input \"yes\" or \"no\": ";
    std::cin >> answer;
    answer = lower_case(answer);
  } while (answer != "yes" && answer != "no");

  if (answer == "yes")
    return true;
  else
    return false;
}

int main() {
  book phone_book;
  /*
    phone_book.phone_by_surname["44-111"] = "Smit";
    phone_book.phone_by_surname["44-11-22"] = "Holland";
    phone_book.phone_by_surname.insert({"936-9992", "ss"});
    phone_book.phone_by_surname.insert(
        std::make_pair<std::string, std::string>("89635555551", "Holland"));

    phone_book.surname_by_phone["Smit"].pushback("44-111");
  */
  phone_book.add("44-111", "Smit");
  phone_book.add("44-11-22", "Holland");
  phone_book.add("936-9992", "Parker");
  phone_book.add("89635555551", "Holland");

  std::string phone = "first", surname;

  do {
    request(phone, surname);

    if (phone.empty() && surname.empty()) {
      std::cout << "Invalid request entered. Try again\n";
      continue;
    } else if (!phone.empty() && !surname.empty()) {
      phone_book.add(phone, surname);
    } else if (surname.empty()) {
      phone_book.find_by_phone(phone);
    } else {
      phone_book.find_by_surname(surname);
    }
  } while (repeat());
}