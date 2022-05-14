#include <fstream>
#include <sstream>
#include <iostream>
#include "makefile.h"
#include "database.h"
#include "recipe.h"
#include "rule.h"
#include "target.h"
#include "variable.h"

/* void test(const char* subtest_name, const char* makefile_name, const char* expected_txt) {
    Makefile mf(makefile_name);
    Database db(mf.rules());
    std::string results = db.build("test");
    std::ifstream expected(expected_txt);
    std::stringstream buffer;
    buffer << expected.rdbuf();
    std::string expected_str = buffer.str();
    if(expected_str.compare(results) == 0) {
        std::cout << subtest_name << " subtest passed" << '\n';
    } else {
        std::cout << "Expected output:" << '\n';
        std::cout << expected_str << '\n';
        std::cout << "Actual output:" << '\n';
        std::cout << results << '\n';
        std::cout << subtest_name << " subtest failed" << '\n';
    }
}

int main() {
    try {
        test("First", "Makefile1", "results1.txt");
        test("Second", "Makefile2", "results2.txt");
    }
    catch(const std::exception& err) {
        std::cout << err.what() << '\n';
    }
    catch(...) {
        std::cout << "Unexpected exception during test" << '\n';
    }
} */

void test() {
    Makefile mf1("testmakefile1");
    Database db1(mf1.rules());
    db1.build("test1");
    db1.build("test2");
}

int main(int argc, char* argv[]) {
    try {
        if(argc == 1) {
            test();
        } else {
            Makefile mf("_Makefile");
            Database db(mf.rules());
            db.build(argv[1]);
        }
    }
    catch(std::exception& err) {
        std::cout << err.what() << '\n';
    }

    return 0;
}