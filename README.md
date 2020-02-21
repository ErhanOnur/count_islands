# Count Islands
Problem:
Given a 2 dimension array matrix of 0s and 1s, count the number of islands of 1s. An island is surrounded by a group of adjacent cells that are all 1s. A cell can only be adjacent to each other horizontally and vertically.

# First method
Saves island datas. check the island points in island datas with binary_search. Complexity is nlog(n) (n is number of points)

```Console
$ g++ count_island.cpp -std=c++17 
$ ./a.out
1 1 1 0 1 0 0 0 
0 0 0 0 1 0 1 0 
1 1 1 0 1 1 1 0 
Number of island:3
```

# Second method (fast)
Traversing the map from top to bottom. Check the island points with top ranges. Complexity is n.

```Console
$ g++ count_island_fast.cpp -std=c++17 
$ ./a.out
1 1 1 0 1 0 0 0 
0 0 0 0 1 0 1 0 
1 1 1 0 1 1 1 0 
Number of island:3
```
