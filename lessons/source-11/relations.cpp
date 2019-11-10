#include <memory>

struct SomeStruct {
    void doWork(int param) const {

    }
    friend void friendship();
private:
    void doPrivateWork(char * param) {

    }
};

void friendship() {
    SomeStruct obj;
    obj.doPrivateWork("trololo");
}

void inheritance() {
    struct Derived : SomeStruct {
        void work() {
            doWork(42);
        }
    };

    Derived derived;
    derived.work();
}

void composition() {
    struct SuperStruct {
        void work() {
            m_worker.doWork(42);
        }
    private:
        SomeStruct m_worker;
    };

    SuperStruct super;
    super.work();
}

void argument() {
    struct SuperStruct {
        void work(const SomeStruct& worker) {
            worker.doWork(42);
        }
    };

    SomeStruct worker;
    SuperStruct value;
    value.work(worker);
};

SomeStruct global;
void globalVariable() {
    global.doWork(42);
}

void templateArgument1() {
    std::unique_ptr<SomeStruct> ptr{new SomeStruct};
    ptr->doWork(42);
}

template<typename T>
void templateArgument2() {
    T worker;
    worker.doWork(42);
}

int main() {
    templateArgument2<SomeStruct>();
    return 0;
}