#include <stdio.h>

#include <iostream>
#include <vector>
#include <utility>

using powerval = unsigned long long;
using bioval = short;
using val = unsigned long long;
// using par = std::pair<std::vector<int>, val>;
struct DPEntry {
    val energy;
    int choice;  // which i was removed last
    DPEntry() : energy(0), choice(-1) {} // initialization
};

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
            exit(3);
    }
}

bioval getAffinity(int l, int r, const std::vector<bioval>& bioClasses) {
    if (l < 0 || r >= static_cast<int>(bioClasses.size()))
        return 1;
    else
        return afinity[bioClasses[l]][bioClasses[r]];
}

powerval getPower(int i, const std::vector<powerval>& powers) {
    if (i == -1 || i == static_cast<int>(powers.size()))
        return 1;
    else
        return powers[i];
}

val getEnergy(int l, int i, int r, const std::vector<powerval>& powers,
              const std::vector<bioval>& bioClasses) {
    // std::cout << "l=" << l << ", i=" << i << ", r=" << r << ", pl=" << getPower(l, powers) << ", pi=" << getPower(i, powers) << ", pr=" << getPower(r, powers) << ", ali=" << getAffinity(l, i, bioClasses) << ", air=" << getAffinity(i, r, bioClasses) << ";\n";
    // std::cout << "stage1=" << getPower(l, powers) * getPower(i, powers) * getAffinity(l, i, bioClasses) << ", stage2=" << getPower(i, powers) * getPower(r, powers) * getAffinity(i, r, bioClasses) << ";\n";
    return getPower(l, powers) * getPower(i, powers) *
               getAffinity(l, i, bioClasses) +
           getPower(i, powers) * getPower(r, powers) *
               getAffinity(i, r, bioClasses);
}


val solve(int boundl, int boundr, std::vector<std::vector<DPEntry>>& dp,
          const std::vector<powerval>& powers, const std::vector<bioval>& bioClasses) {
    int vectl = boundl;
    int vectr = boundr - boundl;
    
    if (dp[vectl][vectr].choice != -1){
        // std::cout << "For the boundl=" << boundl << ", boundr=" << boundr << ";         KNOWN  " << dp[vectl][vectr].energy << "\n";
        return dp[vectl][vectr].energy;
    }
    
    if (boundl == boundr) {
        dp[vectl][vectr].energy = getEnergy(boundl-1, boundl, boundl+1, powers, bioClasses);
        dp[vectl][vectr].choice = boundl;
        // std::cout << "For the boundl=" << boundl << ", boundr=" << boundr << ";         SINGLE " << dp[vectl][vectr].energy << "\n";
        return dp[vectl][vectr].energy;
    }
    
    int solution = boundl;
    val bestEnergy = 0;
    
    for (int i = boundl; i <= boundr; i++) {
        val energy = 0;
        
        if (i > boundl)
            energy += solve(boundl, i-1, dp, powers, bioClasses);
        if (i < boundr)
            energy += solve(i+1, boundr, dp, powers, bioClasses);
        
        energy += getEnergy(boundl-1, i, boundr+1, powers, bioClasses);
        
        if (i == boundl || energy >= bestEnergy) {
            bestEnergy = energy;
            solution = i;
        }
    }
    
    dp[vectl][vectr].energy = bestEnergy;
    dp[vectl][vectr].choice = solution;
    // std::cout << "For the boundl=" << boundl << ", boundr=" << boundr << ";         we got " << bestEnergy << "\n";
    return bestEnergy;
}

void traceback(int boundl, int boundr, const std::vector<std::vector<DPEntry>>& dp,
                 std::vector<int>& sequence) {
    if (boundl > boundr) return;
    
    int vectl = boundl;
    int vectr = boundr - boundl;
    int i = dp[vectl][vectr].choice;
    
    // traceback left, then right, then add i (which was removed last)
    if (i > boundl)
        traceback(boundl, i-1, dp, sequence);
    if (i < boundr)
        traceback(i+1, boundr, dp, sequence);
    
    sequence.push_back(i);
}

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    // Get aminoacid's powers
    std::vector<powerval> powers(n);
    for (int i = 0; i < n; i++)
        std::cin >> powers[i];

    // Get aminoacid's classes
    std::vector<char> bioClassesChars(n);
    for (int i = 0; i < n; i++) {
        std::cin >> bioClassesChars[i];
    }

    std::vector<bioval> bioClasses(n);
    for (int i = 0; i < n; i++) {
        int current = aIdx(bioClassesChars[i]);
        bioClasses[i] = current;
    }

    
    std::vector<std::vector<DPEntry>> dp(n, std::vector<DPEntry>(n));
    
    // TODO remove recursivity
    val totalEnergy = solve(0, n-1, dp, powers, bioClasses);
    
    // Get the sequence.
    std::vector<int> sequence;
    traceback(0, n-1, dp, sequence);
    
    std::cout << totalEnergy << "\n";
    for (int i = 0; i < n; i++) {
        if (i > 0) std::cout << " ";
        std::cout << sequence[i] + 1;
    }
    std::cout << "\n";
    return 0;
}
