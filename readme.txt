input format
1<=N<=2e5
0<=M<=(N*(N-1))/2;
1<=Si<=1e9
1<=u,v<=N
u!=v
all pair distinct

input for test
{
5 4
100 40 40 40 40
1 2
1 3
1 4
1 5
//
3 2
100 60 60
1 2
1 3
//
6 2
10 20 30 40 50 60
1 2
5 6
//

}
output formate
sum of skill rating
indics of selected coder(ascending order)

run code within 5min and output your code
#after analysis i found that for output i also need a vector<vector> indics,sumofskils
//greedy approach
first find highest skill then also marked its neighbour
like that when the completed
 
1.builed vector pair for storing index, 
2. sort the vector 
3. choose the highest than remove its neighbour(mark visited done by iterating adj vector)
4. repeat above process until all marked 
//P&L approach
i have to check which person block how much (gain-lost due to conflict);
i will pick first max gain person and same process like above
1.first create a vector<pair> decrease skill by its neighbour .
2. how should i decrease, i think i need to another data unordered_map;
but there is one loop hole ,it failed on 2nd test case.
3 2
100 60 60
1 2
1 3
solution should be no of blocking && plskill points = no of blocks* plskill points (of equal then less no of blocks consider);//abhi impliment nhi kiya hai
