#include <fstream>
#include <sstream>
#include <iostream>
#include "gtest_lite.h"
#include "makefile.h"
#include "database.h"
#include "recipe.h"
#include "rule.h"
#include "target.h"
#include "variable.h"

void test();
void variable_test();
void pattern_test();
void exception_test();

int main(int argc, char* argv[]) {
    try {
        if(argc == 1) { // If there's no input given, do the test
            test();
        } else { // If there's input, use it as the target
            Makefile mf("_Makefile");
            Database db(mf.rules());
            db.build(argv[1]);
        }
    }
    catch(std::exception& err) {
        std::cerr << err.what() << '\n';
    }

    return 0;
}

void test() {
    variable_test();
    pattern_test();
    exception_test();
    /* Build compulsion because of modtime differences
       cannot be tested without system calls */
}

void variable_test() {
    std::cout << "-------------------- Testing Variable interpretation" << std::endl;
    std::cout << "------------ Reading makefile1" << std::endl;
    Makefile mf1("makefile1");
    Database db1(mf1.rules());
    std::cout << "---- Building target 'target1'" << std::endl;
    db1.build("target1");
    std::cout << "------------ Reading makefile2" << std::endl;
    Makefile mf2("makefile2");
    Database db2(mf2.rules());
    std::cout << "---- Building target 'target2'" << std::endl;
    db2.build("target2");
}

void pattern_test() {
    std::cout << "-------------------- Testing Pattern interpretation" << std::endl;
    std::cout << "------------ Reading makefile3" << std::endl;
    Makefile mf3("makefile3");
    Database db3(mf3.rules());
    std::cout << "---- Building target 'target.a'" << std::endl;
    db3.build("target.a");
}

void exception_test() {
    std::cout << "-------------------- Testing Exceptions" << std::endl;
    std::cout << "------------ Reading makefile4" << std::endl;
    Makefile mf4("makefile4");
    Database db4(mf4.rules());
    std::cout << "---- Building target 'prereq'" << std::endl;
    db4.build("prereq");
    std::cout << "---- Building target 'nonexistent'" << std::endl;
    try {
        db4.build("nonexistent");
    }
    catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    std::cout << "---- Building target 'loop1'" << std::endl;
    db4.build("loop1");
    std::cout << "------------ Reading makefile5" << std::endl;
    Makefile mf5("makefile5");
    Database db5(mf5.rules());
    std::cout << "---- Building target 'looproot'" << std::endl;
    db5.build("looproot");
    std::cout << "------------ Reading makefile6" << std::endl;
    Makefile mf6("makefile6");
    Database db6(mf6.rules());
    db6.build("anything");
}
