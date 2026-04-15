input format
1<=N<=2e5
0<=M<=(N*(N-1))/2;
1<=Si<=1e9
1<=u,v<=N
u!=v
all pair distinct

output formate
sum of skill rating
indics of selected coder(ascending order)

run code within 5min and output your code

//greedy approach
first find highest skill then also marked its neighbour
like that when the completed
 
1.builed vector pair for storing index, 
2. sort the vector 
3. choose the highest than remove its neighbour(mark visited done by iterating adj vector)
4. repeat above process until all marked 
//