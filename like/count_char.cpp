#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;
typedef map<char, int> MAP;
void print(MAP::value_type t) {
    cout << t.first << ": have" << t.second << "" << endl;
}
void CountCharacter(MAP& m, char* szText) {
    char* p = szText;
    if (!p)
        return;
    while (*p) {
        MAP::iterator it;
        it = m.find(*p);
        if (it == m.end()) {
            m.insert(MAP::value_type(*p, 1));
        } else {
            ++(it->second);
        }
        ++p;
    }
    return;
}
int main() {
    MAP myMap;
    char szText[512] = {0};
    cout << "input a string:" << endl;
    fgets(szText, 512, stdin);
    szText[strlen(szText) - 1] = 0;
    CountCharacter(myMap, szText);
    for_each(myMap.begin(), myMap.end(), print);
    return 0;
}