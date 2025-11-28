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
            printf("Invalid char detected: %c\n", c);
            exit(1);
    }
}


int getAffinity(int iLeft, const std::vector<int> &bioClasses){
    int iRight = iLeft+1;
    if (iLeft==-1 || iRight == static_cast<int>(bioClasses.size()))
        return 1;
    else
        return afinity[bioClasses[iLeft]][bioClasses[iRight]];
}

int getPower(int i, const std::vector<int> &powers){
    if (i==-1 || i == static_cast<int>(powers.size()))
        return 1;
    else
        return powers[i];
}

int getEnergy(int i, std::vector<int> &powers, std::vector<int> &bioClasses){
    return getPower(i-1, powers) * getPower(i, powers) * getAffinity(i-1, bioClasses) +
           getPower(i, powers) * getPower(i+1, powers) * getAffinity(i, bioClasses);
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

    std::cout << getEnergy(0, powers, bioClasses) << "\n";





    //std::cout << finalEnergy << "\n";
    //std::cout << finalSequence << "\n";

    


    std::cout << "the finale\n";
    return 0;
}
