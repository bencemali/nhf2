#include <fstream>
#include <sstream>
#include <iostream>
#include "makefile.h"
#include "database.h"
#include "recipe.h"
#include "rule.h"
#include "target.h"
#include "variable.h"

void test() {
    Makefile mf1("../test/testmakefile1");
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
