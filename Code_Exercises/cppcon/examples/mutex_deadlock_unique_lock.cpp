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
    std::cout << std::this_thread::get_id()
              << " hold the lock for both mutex \n";
    std::unique_lock<std::mutex> ul_1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> ul_2(to.m, std::defer_lock);
    std::lock(ul_1, ul_2);
    from.balance -= amount;
    to.balance += amount;
    std::cout << "transfer to - " << to.name << "   from - " << from.name
              << "  end \n";
  }
};  // end class bank_account

int main() {
  bank_account account;
  bank_account account_1(1000, "Gordon");
  bank_account account_2(2000, "Michael");
  std::thread thread_1(&bank_account::transfer, &account, std::ref(account_1),
                       std::ref(account_2), 500);
  std::thread thread_2(&bank_account::transfer, &account, std::ref(account_2),
                       std::ref(account_1), 200);
  thread_1.join();
  thread_2.join();
  return 0;
}
