# Results of analysis of different TSP Algorithms

## Toy Graphs 
## Backtracking - *O(N!)*
#### Shipping
>Elapsed time: 0.164492 s
>Optimal distance to be travelled: 79.2m
#### Stadiums
> Elapsed time: 11.2205 s
> Optimal distance to be travelled: 341m
#### Tourism
> Elapsed time: 9.2147e-05 s
> Optimal distance to be travelled: 2600m

## Triangular Approximation (MST) - *O(N^2 log N)*
#### Shipping
> Elapsed time: 0.000278014 s
> Optimal distance to be travelled: 90.3m
#### Stadiums
> Elapsed time: 0.000465522 s
> Optimal distance to be travelled: 391.4m
#### Tourism
> Elapsed time: 0.000147461 s
> Optimal distance to be travelled: 2600m
 
- Backtracking ensures an optimal solution but with high computational 
cost (O(N!)). It is suitable for small problem instances where the exact 
optimal solution is important.
> Tourism, the smallest graph, achieved an optimal solution of 2600m in 
just 9.2147e-05s using the Backtracking algorithm, demonstrating its 
efficiency for smaller problems. To put in contrast, the 2-approximation 
achieved the same solution but it took longer for it to finish.
 - 2-approximation method offers an efficient, near-optimal solution with 
significantly lesser computation time (O(N^2 log N)). It may not always 
give the exact optimal path but guarantees a solution within twice the 
optimal length under triangular inequality. It is ideal for larger 
instances where computational efficiency is crucial.
> approximation ratio is 14% 






