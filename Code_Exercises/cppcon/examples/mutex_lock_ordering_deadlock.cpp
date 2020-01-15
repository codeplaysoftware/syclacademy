/*
Copyright 2018 Michael Wong

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class bank_account {
  double balance;
  std::string name;
  std::mutex m;

 public:
  bank_account(){};

  bank_account(double _balance, std::string _name)
      : balance(_balance), name(_name) {}

  bank_account(const bank_account&) = delete;
  bank_account& operator=(const bank_account&) = delete;

  void withdraw(double amount) {
    std::lock_guard<std::mutex> lg(m);
    balance += amount;
  }

  void deposit(double amount) {
    std::lock_guard<std::mutex> lg(m);
    balance += amount;
  }

  void transfer(bank_account& from, bank_account& to, double amount) {
    std::lock_guard<std::mutex> lg_1(from.m);
    std::cout << "lock for " << from.name << " account acquire by "
              << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "waiting to acquire lock for " << to.name << " account by  "
              << std::this_thread::get_id() << std::endl;
    std::lock_guard<std::mutex> lg_2(to.m);

    from.balance -= amount;
    to.balance += amount;
    std::cout << "transfer to - " << to.name << "   from - " << from.name
              << "  end \n";
  }
};

int main() {
  bank_account account;

  bank_account account_1(1000, "Gordon");
  bank_account account_2(2000, "Michael");

  std::thread thread_1(&bank_account::transfer, &account, std::ref(account_1),
                       std::ref(account_2), 500);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::thread thread_2(&bank_account::transfer, &account, std::ref(account_2),
                       std::ref(account_1), 200);

  thread_1.join();
  thread_2.join();

  return 0;
}
