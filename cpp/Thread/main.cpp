#include <iostream>
#include <thread>
#include <memory>
#include <future>
#include <vector>
#include <chrono>
#include <latch>

void foo_0x1() {
  std::thread worker([]{
    std::cout << "hello" << std::endl;
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void foo_0x2() {
  auto some_function = []{
    std::cout << "some function" << std::endl;
  };
  auto some_other_function = []{
    std::cout << "some other function" << std::endl;
  };

  std::thread t1(some_function);
  std::thread t2 = std::move(t1);
  t1 = std::thread(some_other_function);

  std::thread t3;
  t3 = std::move(t2);
  t1.detach();
  t1 = std::move(t3);
  t1.join();
}

void foo_0x3() {
  auto f = std::async([] {
    throw std::out_of_range("x < 0");
    return 10;
  });

  using namespace std::chrono_literals;

  std::cout << "hello,world" << std::endl;
  std::this_thread::sleep_for(2000ms);
  std::cout << "hello,world" << std::endl;
  f.wait();
  std::cout << "hello,world" << std::endl;
} 

void foo_0x4() {
  std::promise<int32_t> pe;
  auto f1 = pe.get_future();
  std::cout << f1.valid() << std::endl;
  auto f2 = pe.get_future();
  std::cout << f2.valid() << std::endl;
}

void foo_0x5() {
  auto tp = std::chrono::system_clock::now();
  auto tp2 = std::chrono::system_clock::now();
  // std::cout << tp.time_since_epoch().count() << std::endl;
  // std::cout << std::chrono::duration<int64_t, std::chrono::seconds>(tp).cout() << std::endl;
  auto aa = std::chrono::duration<int64_t, std::chrono::nanoseconds::period>(tp - tp2);
}

void foo_0x6() {
  auto f = std::async(std::launch::async, [&] {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  });
  std::cout << "execute async" << std::endl;
  std::cout << "return funtion" << std::endl;
}

class Foo {
public:
  Foo() {
    std::cout << "Foo constructor" << std::endl;
  }
  ~Foo() {
    std::cout << "Foo destructor" << std::endl;
  }
  Foo(const Foo &f) {
    std::cout << "Foo copy-constructor" << std::endl;
  }
};

void foo_0x7() {
  std::mutex mut;
  std::unique_lock lock(mut);

  std::condition_variable cond;
  cond.wait(lock);

  std::cout << "hello,world" << std::endl;
}

int32_t main (int32_t argc, char *argv[]) {
  // foo_0x1();
  // foo_0x2();
  // foo_0x3();
  // foo_0x4();
  // foo_0x5();
  // foo_0x6();
  foo_0x7();

  return 0;
}
