#!/bin/bash
g++ -std=c++14 -o exec/exact/bb_op cpp/exact/branch_and_bound_op.cpp cpp/heuristic/improvement/3opt_random.cpp cpp/heuristic/greedy.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'op branch and bound successfully compiled' &&
g++ -std=c++14 -o exec/exact/bb cpp/exact/branch_and_bound.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'branch and bound successfully compiled' &&
g++ -std=c++14 -o exec/exact/bruteforce cpp/exact/bruteforce.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'bruteforce successfully compiled' && 
g++ -std=c++14 -o exec/exact/heldkarp cpp/exact/dyn_prog.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo 'heldkarp successfully compiled' &&
echo 'everything successfully compiled!!'
 
