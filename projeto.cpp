#include <stdio.h>

#include <iostream>
#include <vector>
#include <utility>

using val = unsigned long long;
using par = std::pair<std::vector<int>, val>;

int afinity[4][4] = {{1, 3, 1, 3}, {5, 1, 0, 1}, {0, 1, 0, 4}, {1, 3, 2, 3}};

int aIdx(char c) {
    switch (c) {
        case 'P':
            return 0;
        case 'N':
            return 1;
        case 'A':
            return 2;
        case 'B':
            return 3;
        default:
            printf("Invalid char detected: %c\n", c);
            exit(1);
    }
}

int getAffinity(int l, int r, const std::vector<int>& bioClasses) {
    if (l < 0 || r >= static_cast<int>(bioClasses.size()))
        return 1;
    else
        return afinity[bioClasses[l]][bioClasses[r]];
}

int getPower(int i, const std::vector<int>& powers) {
    if (i == -1 || i == static_cast<int>(powers.size()))
        return 1;
    else
        return powers[i];
}

val getEnergy(int l, int i, int r, std::vector<int>& powers,
              std::vector<int>& bioClasses) {
    return getPower(l, powers) * getPower(i, powers) *
               getAffinity(l, i, bioClasses) +
           getPower(i, powers) * getPower(r, powers) *
               getAffinity(i, r, bioClasses);
}

// val newValue(int l, int vectr, int value, std::vector<std::vector<val>>& m) {
//     m[l][vectr] = value;
//     return value;
// }

par getEnergySequence(int indl, int boundl, int boundr, int indr, std::vector<std::vector<par>>& m,
                      std::vector<int>& powers, std::vector<int>& bioClasses) {
    int vectl = boundl;
    int vectr = boundr-boundl;
    if (!m[vectl][vectr].first.empty())
        return m[vectl][vectr];
    if (boundl==boundr){
        par newPar = par{std::vector<int>(1, boundl), getEnergy(indl, boundl, indr, powers, bioClasses)};
        m[vectl][vectr] = newPar;
        return newPar;
    }
    par bestSolution;
    for (int i = boundl; i <= boundr; i++) {
        // add(m(l, i) * m(i+1, r) *
        par solution = par{};
        // Left first so the first added solutionuence is already lexicographically inferior.
        if (i>boundl){
            par subseql = getEnergySequence(indl, boundl, i-1, i, m, powers, bioClasses);
            solution.first.insert(solution.first.end(), subseql.first.begin(), subseql.first.end());
            solution.second += subseql.second;
        }
        if (i<boundr){
            par subseqr = getEnergySequence(i, i + 1, boundr, indr, m, powers, bioClasses);
            solution.first.insert(solution.first.end(), subseqr.first.begin(), subseqr.first.end());
            solution.second += subseqr.second;
        }

        solution.first.push_back(i);
        solution.second += getEnergySequence(indl, i, i, indr, m, powers, bioClasses).second;


        if (bestSolution.first.empty() || bestSolution.second <= solution.second)
            bestSolution = solution;
    }
    m[vectl][vectr] = bestSolution;
    return bestSolution;
}

int main(int argc, char* argv[]) {
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

    // Alocate n*n matrix for results
    std::vector<std::vector<par>> m(n, std::vector<par>(n, par{}));

    for (int i=0; i<n; i++){
        std::cout << "Trying number " << i << " : '" << getEnergySequence(i-1, i,i, i+1, m, powers, bioClasses).second << "'\n";
    }
    std::cout << "Beta trial: '" << getEnergySequence(-1, 0,n-1, n, m, powers, bioClasses).second << "'\n";

    //std::cout << getEnergySequence(0, n - 1, m, powers, bioClasses) << "\n";

    // std::cout << finalEnergy << "\n";
    // std::cout << finalSequence << "\n";

    std::cout << "the finale\n";
    return 0;
}
