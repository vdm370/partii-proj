#!/bin/bash
g++ -std=c++14 -o exec/heur/2opt_f cpp/heuristic/improvement/2opt_full.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ && echo '2opt_full successfully compiled' &&
g++ -std=c++14 -o exec/heur/2opt_r cpp/heuristic/improvement/2opt_random.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ && echo '2opt_random successfully compiled' &&
g++ -std=c++14 -o exec/heur/3opt_f cpp/heuristic/improvement/3opt_full.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ && echo '3opt_full successfully compiled' &&
g++ -std=c++14 -o exec/heur/3opt_r cpp/heuristic/improvement/3opt_random.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp cpp/heuristic/greedy2.cpp -I headers/ && echo '3opt_random successfully compiled' &&
echo 'everything successfully compiled!!'
 
