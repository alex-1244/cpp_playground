#include <iostream>
#include <string>
#include <vector>

int main() {
    int x; std::cout << x << "\n";                    // 1. prediction: random crap thats in memory at the location x points at. CPP compiler does not "alocate" memory when you init variable.
    std::string s = "abc" + 1; std::cout << s << "\n";// 2. prediction:  think its some pointer magic. for sure not "abc1" string, its not js. we probbaly increase pointer value so it'll be "bc" followed by some random memory serialized as char
    int y = 3.9; std::cout << y << "\n";              // 3. prediction: 3, double part will be ""cut off" similar to C#
    int z = 0; if (z = 5) std::cout << "yes " << z;   // 4. prediction: assignment inside if, it probably returns true for some weird reason, so it prints "yes 5"
}