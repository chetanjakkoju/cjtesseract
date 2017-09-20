g++ -c -fPIC -std=c++11 -lpthread cjtesseract.cpp -o cjtesseract.o -llept -ltesseract
g++ -shared -Wl,-soname,libcjtesseract.so -o  libcjtesseract.so cjtesseract.o -llept -ltesseract
