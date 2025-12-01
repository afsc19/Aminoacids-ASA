#!/usr/bin/env python3
import random
import sys

def generate_test(n, min_power=0, max_power=99999999):
    """Generate a random test case with n amino acids"""
    
    # Generate n random powers (8 digits)
    powers = [random.randint(min_power, max_power) for _ in range(n)]
    
    # Generate n random classes
    classes = ''.join(random.choice('PNAB') for _ in range(n))
    
    # Output in the required format
    print(n)
    print(' '.join(map(str, powers)))
    print(classes)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        n = int(sys.argv[1])
    else:
        # Default to random size between 5 and 20
        n = random.randint(5, 2000)
    
    generate_test(n)
