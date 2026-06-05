import subprocess
import os
import re
import time

input_file = 'input.txt'
exe_file = r'.\main.exe'

with open(input_file, 'r') as f:
    content = f.read()

# Split by lines starting with //
blocks = re.split(r'\n//[^\n]*\n', content)
# It's possible the file doesn't start with //, so we need to handle that.
# Let's just manually parse it.
with open(input_file, 'r') as f:
    lines = f.readlines()

test_cases = []
current_case = []
for line in lines:
    if line.startswith('//'):
        if current_case:
            test_cases.append("".join(current_case))
            current_case = []
    else:
        current_case.append(line)
if current_case:
    test_cases.append("".join(current_case))

for i, tc in enumerate(test_cases):
    tc = tc.strip()
    if not tc: continue
    
    start = time.time()
    try:
        proc = subprocess.run([exe_file], input=tc.encode(), capture_output=True, timeout=5)
        elapsed = (time.time() - start) * 1000
        output = proc.stdout.decode().strip()
        print(f"--- Test Case {i+1} ---")
        print(f"Time: {elapsed:.2f} ms")
        print("Output:", output.split('\n')[0] if output else "No output")
    except subprocess.TimeoutExpired:
        print(f"--- Test Case {i+1} ---")
        print("Time: TLE (>5000 ms)")
