#include "fe_jsbachpp.h"
#include <iostream>

using namespace std;

int main(){
  int measures;

  cout << "How many measures?" << endl;
  cin >> measures;
  generateMeasures(measures);
  return 0;
}
