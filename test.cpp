#include <iostream>
#include <map>
#include <regex>
#include <string>

std::string lower_case(std::string str) {
  for (char& c : str) {
    c = std::tolower(c);
  }
  return str;
}

void request(std::string& phone, std::string& surname) {
  using namespace std;

  cout << "Types of requests:\n";
  cout << "1) Input your phone number and last name to add them to your phone "
          "directory.\n";
  cout << "Example: \"44-22-11 Smit\"\n";
  cout << "2) Input a phone number to find a last name by phone number.\n";
  cout << "Example: \"44-44-41\"\n";
  cout << "3) Input a last name to find a subscriber by last name.\n";
  cout << "Example: \"Potter\"\n";

  cout << "Input your request: ";
  std::string answer;
  std::cin.ignore();  // Очистка символа новой строки из буфера ввода
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
  std::cout << "Do you want to continue working with the phone book?\n";
  do {
    std::cout << "Input \"yes\" or \"no\": ";
    std::cin >> answer;
    answer = lower_case(answer);
  } while (answer != "yes" && answer != "no");

  return answer == "yes";
}

void find_surname(std::map<std::string, std::string>& phone_book,
                  const std::string& surname) {
  for (const auto& entry : phone_book) {
    if (entry.second == surname) {
      std::cout << "Phone number: " << entry.first
                << ", subscriber with surname: " << entry.second << "\n";
    }
  }
}

int main() {
  std::map<std::string, std::string> phone_book;
  phone_book["44-111"] = "Smit";
  phone_book["44-11-22"] = "Holland";
  phone_book.insert({"936-9992", "ss"});
  phone_book.insert(
      std::make_pair<std::string, std::string>("89635555551", "Holland"));

  std::string phone, surname;

  do {
    phone = "", surname = "";

    request(phone, surname);

    if (phone.empty() && surname.empty()) {
      std::cout << "Invalid request entered. Try again\n";
      continue;
    } else if (!phone.empty() && !surname.empty()) {
      if (phone_book.count(phone) == 0) {
        phone_book[phone] = surname;
        std::cout << "Phone and last name successfully added\n";
      } else {
        std::cout << "This phone number has already been provided before\n";
      }
    } else if (surname.empty()) {
      auto it = phone_book.find(phone);
      if (it != phone_book.end()) {
        std::cout << "Phone number: " << it->first
                  << ", subscriber with surname: " << it->second << "\n";
      } else {
        std::cout << "Phone number with this number was not found\n";
      }
    } else {
      find_surname(phone_book, surname);
    }
  } while (repeat());

  return 0;
}