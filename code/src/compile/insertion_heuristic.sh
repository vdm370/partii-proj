#!/bin/bash
g++ -std=c++14 -o exec/insheur/random2 cpp/heuristic/insertion_heuristics/random_insertion_heuristic.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo "random heur compiled!" &&
g++ -std=c++14 -o exec/insheur/cheap2 cpp/heuristic/insertion_heuristics/cheapest_insertion_heuristic.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo "cheapest heur compiled!" &&
g++ -std=c++14 -o exec/insheur/near2 cpp/heuristic/insertion_heuristics/nearest_insertion_heuristic.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo "nearest heur compiled!" &&
g++ -std=c++14 -o exec/insheur/far2 cpp/heuristic/insertion_heuristics/farthest_insertion_heuristic.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo "farthest heur compiled!" &&
g++ -std=c++14 -o exec/insheur/convexn cpp/heuristic/insertion_heuristics/convex_hull_heuristic.cpp cpp/helpers/solution.cpp cpp/helpers/graph_dist.cpp -I headers/ && echo "convex heur compiled!" &&
echo "all gut"
