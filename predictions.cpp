#include <iostream>
#include <vector>

int main() {
    int x; std::cout << x << "\n";                    // 1. prediction?
    std::string s = "abc" + 1; std::cout << s << "\n";// 2. prediction?
    int y = 3.9; std::cout << y << "\n";              // 3. prediction?
    int z = 0; if (z = 5) std::cout << "yes " << z;   // 4. prediction?
}