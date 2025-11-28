#include <stdio.h>
#include <iostream>
#include <vector>


int afinity[4][4] = {
    {1, 3, 1, 3},
    {5, 1, 0, 1},
    {0, 1, 0, 4},
    {1, 3, 2, 3}
};

int aIdx(char c) {
    switch (c) {
        case 'P': return 0;
        case 'N': return 1;
        case 'A': return 2;
        case 'B': return 3;
        default: return -1;
    }
}


int getAfinity(char bioClassLeft, char bioClassRight){
    int l = aIdx(bioClassLeft), r = aIdx(bioClassRight);
    if (l<0 || r<0)
        return -1;
    return afinity[l][r];
}

int getEnergy(int i, std::vector<int> powers, std::vector<char> acids)


int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    // Get aminoacid's powers
    std::vector<int> powers(n); 
    for (int i = 0; i < n; ++i)
        std::cin >> powers[i];

    // Get aminoacid's classes
    std::vector<char> bioClasses(n);
    for (int i = 0; i < n; ++i) {
        bioClasses[i] = aIdx(std::cin);
        std::cin >> bioClasses[i];
    }




    std::cout << finalEnergy << "\n";
    std::cout << finalSequence << "\n";

    


    std::cout << "the finale";
    return 0;
}
