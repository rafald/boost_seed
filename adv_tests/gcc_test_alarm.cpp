//  c++ gcc_test_alarm.cpp && ./a.exe

#include <iostream>
#include <climits>
#include <unistd.h>

using std::cout;

main() {
   alarm(2);
   double d = 1.4;
   for(int i=0 ; i!=INT_MAX/50; ++i)
      d *= 1.01;

   cout << "The end.";
}
