#!/bin/bash
g++ -std=c++14 -o exec/approx/christo cpp/approximation/christofides.cpp cpp/approximation/christofides_matching.cpp cpp/helpers/unweighted_graph.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ -lemon && echo 'christofides successfully compiled' &&
g++ -std=c++14 -o exec/approx/2approx cpp/approximation/2approx.cpp cpp/helpers/unweighted_graph.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ && echo '2approx successfully compiled' &&
echo 'everything successfully compiled!!'
 
