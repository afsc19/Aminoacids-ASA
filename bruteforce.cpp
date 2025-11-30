#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using powerval = unsigned long long;
using bioval = short;
using val = unsigned long long;

int afinity[4][4] = {{1, 3, 1, 3}, {5, 1, 0, 1}, {0, 1, 0, 4}, {1, 3, 2, 3}};

int aIdx(char c) {
    switch (c) {
        case 'P': return 0;
        case 'N': return 1;
        case 'A': return 2;
        case 'B': return 3;
        default:
            std::cerr << "Invalid char: " << c << "\n";
            exit(3);
    }
}

struct State {
    std::vector<int> remaining;  // indices still in the chain
    std::vector<int> sequence;   // removal order so far
    val totalEnergy;
};

int getAffinity(int idxL, int idxR, const std::vector<bioval>& bioClasses) {
    if (idxL == -1 || idxR == -1) return 1;
    return afinity[bioClasses[idxL]][bioClasses[idxR]];
}

powerval getPower(int idx, const std::vector<powerval>& powers) {
    if (idx == -1) return 1;
    return powers[idx];
}

val computeEnergy(int leftIdx, int midIdx, int rightIdx, 
                  const std::vector<powerval>& powers, 
                  const std::vector<bioval>& bioClasses) {
    return getPower(leftIdx, powers) * getPower(midIdx, powers) * getAffinity(leftIdx, midIdx, bioClasses) +
           getPower(midIdx, powers) * getPower(rightIdx, powers) * getAffinity(midIdx, rightIdx, bioClasses);
}

State bestSolution;

void bruteforce(State current, const std::vector<powerval>& powers, const std::vector<bioval>& bioClasses) {
    if (current.remaining.empty()) {
        // Found a complete solution
        if (bestSolution.sequence.empty() || 
            current.totalEnergy > bestSolution.totalEnergy ||
            (current.totalEnergy == bestSolution.totalEnergy && current.sequence < bestSolution.sequence)) {
            bestSolution = current;
        }
        return;
    }
    
    // Try removing each position in the current chain
    for (size_t i = 0; i < current.remaining.size(); i++) {
        State next;
        next.sequence = current.sequence;
        next.sequence.push_back(current.remaining[i]);
        
        // Find neighbors in current chain
        int leftIdx = (i > 0) ? current.remaining[i-1] : -1;
        int midIdx = current.remaining[i];
        int rightIdx = (i < current.remaining.size() - 1) ? current.remaining[i+1] : -1;
        
        // Compute energy for removing this position
        val energy = computeEnergy(leftIdx, midIdx, rightIdx, powers, bioClasses);
        next.totalEnergy = current.totalEnergy + energy;
        
        // Build new remaining chain without position i
        next.remaining.reserve(current.remaining.size() - 1);
        for (size_t j = 0; j < current.remaining.size(); j++) {
            if (j != i) next.remaining.push_back(current.remaining[j]);
        }
        
        bruteforce(next, powers, bioClasses);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    if (n > 10) {
        std::cerr << "Brute force only works for n <= 10\n";
        return 1;
    }

    std::vector<powerval> powers(n);
    for (int i = 0; i < n; i++)
        std::cin >> powers[i];

    std::vector<char> bioClassesChars(n);
    for (int i = 0; i < n; i++)
        std::cin >> bioClassesChars[i];

    std::vector<bioval> bioClasses(n);
    for (int i = 0; i < n; i++)
        bioClasses[i] = aIdx(bioClassesChars[i]);

    // Initialize with all positions
    State initial;
    initial.totalEnergy = 0;
    for (int i = 0; i < n; i++)
        initial.remaining.push_back(i);

    bestSolution = State{};
    bruteforce(initial, powers, bioClasses);

    std::cout << bestSolution.totalEnergy << "\n";
    for (int i = 0; i < n; i++) {
        if (i > 0) std::cout << " ";
        std::cout << bestSolution.sequence[i] + 1;
    }
    std::cout << "\n";

    return 0;
}
