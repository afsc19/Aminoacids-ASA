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
        default: 
            printf("Invalid char detected\n");
            exit(1);
    }
}


int getAffinity(int bioClassLeft, int bioClassRight){
    return afinity[bioClassLeft][bioClassRight];
}

int getEnergy(int i, std::vector<int> &powers, std::vector<int> &bioClasses){
    return powers[i-1] * powers[i] * getAffinity(bioClasses[i-1], bioClasses[i]) +
           powers[i] * powers[i+1] * getAffinity(bioClasses[i], bioClasses[i+1]);
}


int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    // Get aminoacid's powers
    std::vector<int> powers(n); 
    for (int i = 0; i < n; i++)
        std::cin >> powers[i];

    // Get aminoacid's classes
    std::vector<char> bioClassesChars(n);
    for (int i = 0; i < n; i++) {
        std::cin >> bioClassesChars[i];
    }

    std::vector<int> bioClasses(n);
    for (int i = 0; i < n; i++) {
        int current = aIdx(bioClassesChars[i]);
        bioClasses[i] = current;
    }





    std::cout << finalEnergy << "\n";
    std::cout << finalSequence << "\n";

    


    std::cout << "the finale";
    return 0;
}
