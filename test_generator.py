import random

def generate_large_test(n=200000, m=200000, filename='large_input.txt'):
    with open(filename, 'w') as f:
        # N and M
        f.write(f"{n} {m}\n")
        
        # Generate random weights between 1 and 10^5
        weights = [str(random.randint(1, 100000)) for _ in range(n)]
        f.write(" ".join(weights) + "\n")
        
        # Generate M random edges
        # We'll just connect random nodes to keep it simple and sparse
        for _ in range(m):
            u = random.randint(1, n)
            v = random.randint(1, n)
            while u == v:
                v = random.randint(1, n)
            f.write(f"{u} {v}\n")
            
    print(f"Generated {filename} with N={n}, M={m}")

if __name__ == "__main__":
    generate_large_test()
