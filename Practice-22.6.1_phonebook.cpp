#include <iostream>
#include <map>
#include <regex>  // добавлен чисто для контроля ввода
#include <string>

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
  std::cout << "Do you want to continue working with the file?\n";
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

void find_surname(std::map<std::string, std::string> phone_book,
                  std::string surname) {
  int count = 0;
  for (std::map<std::string, std::string>::iterator it = phone_book.begin();
       it != phone_book.end(); it++) {
    if (lower_case(it->second) == lower_case(surname)) {
      count++;
      if (count == 1) std::cout << "Phone numbers found for the last name Smith: \n";
      std::cout << it->first << "\n";
    }
  }

  if (count == 0) std::cout << "This surname was not found\n";
}

int main() {
  std::map<std::string, std::string> phone_book;
  phone_book["44-111"] = "Smit";
  phone_book["44-11-22"] = "Holland";
  phone_book.insert({"936-9992", "ss"});
  phone_book.insert(
      std::make_pair<std::string, std::string>("89635555551", "Holland"));

  std::string phone = "first", surname;

  do {
    request(phone, surname);

    if (phone.empty() && surname.empty()) {
      std::cout << "Invalid request entered. Try again\n";
      continue;
    } else if (!phone.empty() && !surname.empty()) {
      if (phone_book.count(phone) == 0) {
        phone_book[phone] = surname;
        std::cout << "Phone and last name successfully added\n";
      } else
        std::cout << "This phone number has already been provided before\n";
    } else if (surname.empty()) {
      if (phone_book.find(phone) != phone_book.end()) {
        std::cout << "Phone number: " << phone_book.find(phone)->first
                  << " subscriber with surname: " << phone_book[phone] << "\n";
      } else {
        std::cout << "This phone number was not found\n";
      }
    } else {
      find_surname(phone_book, surname);
    }
  } while (repeat());
}