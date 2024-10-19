PROJECT_NAME = S21_SmartCalc
FLAGS = -Wall -Wextra -Werror -std=c++17
CHECKFLAG = -lgtest
TEST_NAME = model_test.cc

all: create 
	cmake --build build --target all

create: clean
	mkdir -p build
	echo "Create"
	cmake . -B build/ 


install: all
	-rm -rf app
	-mkdir app
ifeq ($(shell uname),Linux) # Linux
	cp -r build/s21_smartcalc app
endif
ifeq ($(shell uname),Darwin) # MacOS
	cp -r build/s21_smartcalc.app app
endif


uninstall:
	-rm -rf app

test:
	g++ $(FLAGS) model_test.cc model/s21_model.cc -o s21_test $(CHECKFLAG)
	./s21_test

gcov_report: clean
	g++ $(FLAGS) --coverage $(TEST_NAME) model/s21_model.cc -o s21_test $(CHECKFLAG)
	./s21_test
	mkdir gcov_report
	gcovr --html --html-details gcov_report/index.html
	open gcov_report/index.html

clean: 
	rm -rf build/ a.out s21_test gcov_report *.gcda *.gcno 

clang: clean
	find . -type f -name "*.h" -o -name "*.cc" | xargs clang-format -style=Google -n

	
dvi:
	open SmartCalcReport.html 

dist: clean
	-rm files.list
	find pwd -type f -not -name ".*" -mindepth 1 |cut -c `pwd|wc -c`- | cut -c 2- >> files.list
	find . -depth -type f -not -name ".*" -print | cpio -pdm $(PROJECT_NAME)
	tar -czvf $(PROJECT_NAME).tar.gz $(PROJECT_NAME)
	rm -rf $(PROJECT_NAME)
	-rm files.list
