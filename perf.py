#!/usr/bin/env python3
import subprocess
import sys
import re
import random
import matplotlib.pyplot as plt

def generate_test_input(n, min_power=0, max_power=99999999):
    """Generate a random test case with n amino acids"""
    powers = [random.randint(min_power, max_power) for _ in range(n)]
    classes = ''.join(random.choice('PNAB') for _ in range(n))
    
    return f"{n}\n{' '.join(map(str, powers))}\n{classes}\n"

def run_single_test(project, n, max_power):
    """Run a single test and measure execution time"""
    test_input = generate_test_input(n, 0, max_power)
    
    cmd = [f'./{project}']
    result = subprocess.run(cmd, input=test_input, capture_output=True, text=True, timeout=60)
    
    # Get execution time from /usr/bin/time or measure it ourselves
    import time
    start = time.time()
    result = subprocess.run(cmd, input=test_input, capture_output=True, text=True, timeout=60)
    elapsed = time.time() - start
    
    return elapsed

def run_tests(project, pmax, n_start, n_add, repetitions, seed=None):
    """Run multiple tests with increasing N"""
    if seed is not None:
        random.seed(seed)
    
    n_values = []
    times = []
    
    current_n = n_start
    for i in range(repetitions):
        print(f"Test {i} (N={current_n})...", end=' ', flush=True)
        try:
            n_avg = 5 #maybe change to args
            total=0
            for i in range(n_avg):
                total += run_single_test(project, current_n, pmax)
            elapsed = total/n_avg
            n_values.append(current_n**2)
            times.append(elapsed)
            print(f"{elapsed:.3f}s")
        except subprocess.TimeoutExpired:
            print("TIMEOUT")
            break
        except Exception as e:
            print(f"ERROR: {e}")
            break
        
        current_n += n_add
    
    return n_values, times

def plot_results(n_values, times, project):
    """Create a plot of N vs execution time"""
    plt.figure(figsize=(10, 6))
    plt.plot(n_values, times, 'bo-', linewidth=2, markersize=8)
    plt.xlabel('n^2', fontsize=12)
    plt.ylabel('Tempo (segundos)', fontsize=12)
    plt.title(f'Análise experimental', fontsize=14)
    plt.grid(True, alpha=0.3)
    
    # Add value labels on points
    for n, t in zip(n_values, times):
        plt.annotate(f'{t:.3f}s', (n, t), textcoords="offset points", 
                    xytext=(0,10), ha='center', fontsize=9)
    
    plt.tight_layout()
    plt.savefig(f'{project}_performance.png', dpi=150)
    print(f"Graph saved as '{project}_performance.png'")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 6:
        print("Usage: python3 perf.py <project> <Pmax> <N_start> <N_add> <repetitions> [seed]")
        print("Example: python3 perf.py projeto 99999 100 100 10")
        sys.exit(1)
    
    project = sys.argv[1]
    pmax = int(sys.argv[2])
    n_start = int(sys.argv[3])
    n_add = int(sys.argv[4])
    repetitions = int(sys.argv[5])
    seed = int(sys.argv[6]) if len(sys.argv) > 6 else None
    
    print(f"Running performance tests for {project}...")
    print(f"Starting N={n_start}, increment={n_add}, repetitions={repetitions}")
    print("---")
    
    n_values, times = run_tests(project, pmax, n_start, n_add, repetitions, seed)
    
    if not n_values:
        print("ERROR: No timing data collected")
        sys.exit(1)
    
    print(f"\nCollected {len(n_values)} data points")
    print("N values:", n_values)
    print("Times:", [f"{t:.3f}" for t in times])
    print()
    
    plot_results(n_values, times, project)
