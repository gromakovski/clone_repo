// Signals2

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <boost/signals2/signal.hpp>

namespace bs = boost::signals2;

void signal_vs_function() {
    std::cout << "\nsignal_vs_function\n";

    std::function<void()> func;
    func = []{ std::cout << "Hello from function!" << std::endl;};
    func();

    bs::signal<void()> s;
    s.connect([]{ std::cout << "Hello from signal!" << std::endl;});
    s();

    std::cout << std::endl;
}



void signal_vs_function2() {
    std::cout << "\nsignal_vs_function2\n";

    std::function<void()> func;
    func = []{ std::cout << "Hello " << std::endl;};
    func = []{ std::cout << "from function!" << std::endl;};
    func();

    bs::signal<void()> s;
    s.connect([]{ std::cout << "Hello " << std::endl;});
    s.connect([]{ std::cout << " from signal!" << std::endl;});
    s();

    std::cout << std::endl;
}



#pragma region (Disconnect)
void disconnect_test() {
    std::cout << "\ndisconnect_test\n";

    bs::signal<void()> s;

    auto func1 = []{ std::cout << "Hello from the first function!" << std::endl;};
    auto func2 = []{ std::cout << "Hello from the second function!" << std::endl;};
    auto func3 = []{ std::cout << "Hello from the third function!" << std::endl;};

    s.connect(func1);
    s.connect(func2);
    auto connection = s.connect(func3);
    
    std::cout << "Num slots = " << s.num_slots() << std::endl;

    // MSVC compile error :(
    // s.disconnect(func1);
    // std::cout << "Num slots = " << s.num_slots() << std::endl;

    s();

    connection.disconnect();
    std::cout << "Num slots = " << s.num_slots() << std::endl;

    s.disconnect_all_slots();
    std::cout << "Num slots = " << s.num_slots() << std::endl;

    s();

    std::cout << std::endl;
}
#pragma endregion (Disconnect)



#pragma region (DisconnectAll)
void disconnect_all_test() {
    std::cout << "\ndisconnect_all_test\n";

    {
        bs::signal<void()> void_signal;
        // Compile error - functions returns void
        // auto result = void_signal();
    }

    bs::signal<int()> s;

    s.connect([]{ return 42; });
    s.connect([]{ return 24; });
    s.connect([]{ return 178; });
    s.connect([]{ return 0; });

    // result type ?
    auto result = s();

    if (result)
        std::cout << *result << std::endl;
    else
        std::cout << "No results!" << std::endl;

    s.disconnect_all_slots();
    auto resul2 = s();
    if (resul2)
        std::cout << *resul2 << std::endl;
    else
        std::cout << "No results!" << std::endl;

    std::cout << std::endl;
}
#pragma endregion (DisconnectAll)



#pragma endregion (MaxElement)
template<typename T>
struct get_max {
    using result_type = T;

    template<typename Iter>
    T operator()(Iter first, Iter last) const {
        std::vector<T> results(first, last);
        return *std::max_element(results.cbegin(), results.cend());
    }
};

void test_max_element() {
    std::cout << "\ntest_max_element\n";

    bs::signal<int(), get_max<int>> s;
    
    s.connect([]{ return 42; });
    s.connect([]{ return 24; });
    s.connect([]{ return 178; });
    s.connect([]{ return 0; });

    // result type ?
    auto result = s();

    std::cout << result << std::endl;

    s.disconnect_all_slots();

    // Segmentation fault here. 
    // auto result2 = s();
    // std::cout << result2 << std::endl;

    std::cout << std::endl;

}
#pragma endregion (MaxElement)


#pragma region (ReturnAll)
template<typename T>
struct get_all {
   using result_type = T;

    template<typename Iter>
    T operator()(Iter first, Iter last) const {
        return T(first, last);
    }
};

void test_return_all() {
    std::cout << "\ntest_return_all\n";

    bs::signal<int(), get_all<std::vector<int>>> s;
    
    s.connect([]{ return 42; });
    s.connect([]{ return 24; });
    s.connect([]{ return 178; });
    s.connect([]{ return 0; });

    // result type ?
    auto result = s();

    for(auto& v : result)
        std::cout << v << ' ';
    std::cout << std::endl;
}
#pragma endregion (ReturnAll)


#pragma region (BigExample)
template<typename T>
struct return_all {
    typedef T result_type;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const {
        return T(first, last);
    }
};

using m_update_signal_t = bs::signal<bool(const std::string &), return_all<std::vector<bool>>>;


// Publisher (Observable)
class Document {
public:
    Document() {};

    bs::connection connect(const m_update_signal_t::slot_type &subscriber) {
        return m_signal.connect(subscriber);
    }

    void paragraph(const std::string &p) {
        m_text += p + "\n";
        auto r = m_signal(p);
        for (auto i : r) {
            std::cout << i;
        }
        std::cout << std::endl;
    }

    const std::string &get() const {
        return m_text;
    }
private:
    m_update_signal_t m_signal;
    std::string m_text;
};


// Sibsriber (Observer)
class AutoSaver {
public:
    AutoSaver(Document &doc, const std::string &fname) : m_fname(fname), m_document(doc) {
        m_connection = doc.connect(std::bind(&AutoSaver::refresh, this, std::placeholders::_1));
    }

    ~AutoSaver() {
        m_connection.disconnect();
    }

    bool refresh(const std::string &p) const {
        std::cout << "=== " << m_fname << " === " << p << std::endl;
        std::cout << m_document.get() << std::endl;
        std::cout << "=== end ===" << std::endl;
        return true;
    }
private:
    std::string m_fname;
    Document &m_document;
    bs::connection m_connection;
};


// Sibsriber (Observer)
class Renderer {
public:
    Renderer(Document &doc) {
        m_connection = doc.connect(std::bind(&Renderer::refresh, this, std::placeholders::_1));
    }

    ~Renderer() {
        m_connection.disconnect();
    }

    bool refresh(const std::string &p) const {
        std::cout << "=== window update === " << p << std::endl;
        return false;
    }
private:
    bs::connection m_connection;
};


void test_document() {
    Document doc;

    AutoSaver as(doc, "tmp.txt");
    doc.paragraph("Report");

    {
        Renderer r(doc);
        doc.paragraph("Hello");
    }

    doc.paragraph("World");
}
#pragma endregion (BigExample)


int main(int, char *[]) {

    signal_vs_function();
    signal_vs_function2();
    disconnect_test();
    disconnect_all_test();
    test_max_element();
    test_return_all();

    test_document();

    return 0;
}
