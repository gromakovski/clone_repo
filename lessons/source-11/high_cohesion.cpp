#include <memory>

// Module 1 - wrong
struct WorkerAndSaverToDBAndUI {
    void doWork() {
        makeCalculation();
        saveToDB();
        createUIForm();
        waitForUserClick();
        closeDialog();
    }
private:
    void makeCalculation() {}
    void saveToDB() {};
    void createUIForm() {};
    void waitForUserClick() {};
    void closeDialog() {};
};


// Module 2 - better
struct Input {
};

struct Result {

};

struct Worker {
    Result doWork(Input input) {
        Result result;
        result = m_calculator.calculate(input);
        return result;           
    }
private:
    struct Calculator {
        Result calculate(Input input) {
            Result result;
            return result;
        }
    };
    Calculator m_calculator;
};


// Module 3 - super class usage
struct SuperWorker {
    void doWork1() {}
    void doWork2() {}

    void doCalculation1() {}
    void doCalculation2() {}
};

struct SomeModule {
    void doWork() {
        worker.doWork1();
        worker.doWork2();
    }

    void doCalculation() {
        calculator.doCalculation1();
        calculator.doCalculation2();
    }
private:
    SuperWorker worker;
    SuperWorker calculator;
};




int main() {
    return 0;
}