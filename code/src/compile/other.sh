#!/bin/bash
g++ -std=c++14 -o exec/other/random cpp/heuristic/random.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'random successfully compiled' &&
g++ -std=c++14 -o exec/other/greedy cpp/heuristic/greedy.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'greedy successfully compiled' &&
g++ -std=c++14 -o exec/other/aco cpp/heuristic/ant_colony.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'ACO successfully compiled' &&
g++ -std=c++14 -o exec/heur/lkh cpp/heuristic/improvement/kernighen_lin.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ && echo 'LKH successfully compiled' &&
echo 'everything successfully compiled!!'
 
