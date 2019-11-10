#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

void test1_simple_threads() {

    std::cout << "\ntest1_simple_threads\n";

    auto worker = [](int number, const std::string& str) {
        for (int i = 0; i < 10; ++i)
            std::cout << str << "Hello from thread number: " << number << std::endl;
    };

    auto bad_worker = []() {
        throw std::logic_error("Ooooops");
    };

    const std::string str = "Str ";
    std::thread thread1(worker, 0, std::ref(str));
    std::thread thread2(worker, 1, std::ref(str));

    // std::thread bad_thread(bad_worker);
    // bad_thread.join();

    thread1.detach();
    thread2.join();
}


void test2_methods() {

    std::cout << "\ntest2_methods\n";

    auto worker = [](int number) {
        for (int i = 0; i < 3; ++i)
            std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
    };

    auto threadCount = std::thread::hardware_concurrency();
    std::cout << "threadCount = " << threadCount << std::endl;
    if (!threadCount)
        threadCount = 2;

    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& th : threads) {
        auto handle = th.native_handle();
        if (th.joinable())
            th.join();
    }
}


void test3_mutex() {

    std::cout << "\ntest3_mutex\n";

    std::mutex coutMutex;
    auto worker = [&coutMutex](int number) {
        for (int i = 0; i < 3; ++i) {
            coutMutex.lock();
            std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
            coutMutex.unlock();
        }
    };

    auto threadCount = std::thread::hardware_concurrency();
    std::cout << "threadCount = " << threadCount << std::endl;
    if (!threadCount)
        threadCount = 2;

    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& th : threads) {
        auto handle = th.native_handle();
        if (th.joinable())
            th.join();
    }
}


void test4_mutexes() {
    std::cout << "\ntest4_mutexes\n";

    std::mutex coutMutex;
    std::mutex cerrMutex;

    auto worker = [&coutMutex, &cerrMutex](int number) -> int {
        for (int i = 0; i < 3; ++i) {
            coutMutex.lock();
            std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
            coutMutex.unlock();

            cerrMutex.lock();
            std::cout << "Error from thread with id = " << std::this_thread::get_id() << std::endl;
            cerrMutex.unlock();
        }

        return 0;
    };

    std::thread thread1(worker, 0);
    std::thread thread2(worker, 1);

    thread1.join();
    thread2.join();
}


void test5_lock_guard() {

    std::cout << "\ntest5_lock_guard\n";

    std::mutex coutMutex;

    auto worker = [&coutMutex](int number) {
        for (int i = 0; i < 10; ++i) {
            std::lock_guard<std::mutex> guard{coutMutex};
            std::cout << "Hello from thread number: " << number << std::endl;
        }
    };

    std::thread thread1(worker, 0);
    std::thread thread2(worker, 1);

    thread1.join();
    thread2.join();
}

void test6_deadlock() {
    std::mutex coutMutex;
    std::mutex cerrMutex;

    auto worker1 = [&coutMutex, &cerrMutex](int number) {
        std::lock_guard<std::mutex> cerrGuard{cerrMutex};

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> coutGuard{coutMutex};

        std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
        std::cout << "Error from thread with id = " << std::this_thread::get_id() << std::endl;

    };

    auto worker2 = [&coutMutex, &cerrMutex](int number) {
        std::lock_guard<std::mutex> coutGuard{coutMutex};

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> cerrGuard{cerrMutex};

        std::cerr << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
        std::cerr << "Error from thread with id = " << std::this_thread::get_id() << std::endl;
    };

    std::thread thread1(worker1, 0);
    std::thread thread2(worker2, 1);

    thread1.join();
    thread2.join();
}


void test7_lock() {
    std::mutex coutMutex;
    std::mutex cerrMutex;

    auto worker1 = [&coutMutex, &cerrMutex](int number) {
        std::lock(coutMutex, cerrMutex);

        std::lock_guard<std::mutex> cerrGuard{cerrMutex, std::adopt_lock};

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> coutGuard{coutMutex, std::adopt_lock};

        std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
        std::cout << "Error from thread with id = " << std::this_thread::get_id() << std::endl;

    };

    auto worker2 = [&coutMutex, &cerrMutex](int number) {
        std::lock(coutMutex, cerrMutex);

        std::lock_guard<std::mutex> coutGuard{coutMutex, std::adopt_lock};

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> cerrGuard{cerrMutex, std::adopt_lock};

        std::cout << "Hello from thread with id = " << std::this_thread::get_id() << std::endl;
        std::cout << "Error from thread with id = " << std::this_thread::get_id() << std::endl;
    };

    std::thread thread1(worker1, 0);
    std::thread thread2(worker2, 1);

    thread1.join();
    thread2.join();
}


int main()
{
    test1_simple_threads();

    // test2_methods();

    // test3_mutex();

    // test4_mutexes();

    // test5_lock_guard();

    // test6_deadlock();

    // test7_lock();

    return 0;
}
