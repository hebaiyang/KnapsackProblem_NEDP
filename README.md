## Numerically exact dynamic programming
## Introduction
This project focuses on applying dynamic programming to solve the knapsack problem over rational numbers. The research aims to address two major challenges: 
1) the potential misjudgment of feasibility and dominance relations of packing patterns caused by rounding errors in floating-point arithmetic 
2) the high computational cost associated with rational arithmetic. The proposed algorithm aims to efficiently provide a numerically exact solution to the knapsack problem.

This program implements several dynamic programming algorithms, including:
1. a dynamic programming algorithm based on the weight interval generation strategy under floating-point operations
2. a scaling-based dynamic programming algorithm under floating-point operation
3. interval-based dynamic programming algorithms for floating-point operations
4. dynamic programming algorithms based on the weight interval generation strategy under rational operation
5. a numerically exact dynamic programming algorithm under floating-point arithmetic

Pseudocode for Algorithms 2-6 can be found in the manuscript "Numerically exact dynamic programming method for knapsack problems over rational numbers".


## code file
This project contains five files: main.cpp, dynamic_programming.h, dynamic_programming.cpp, read_problem.h and read_problem.cpp.
The read_problem.cpp file implements the functions for reading the instance data.
The dynamic_programming.cpp file implements five dynamic programming algorithms.
The main.cpp calls read_problem.cpp and dynamic_programming.cpp to read the data and run the dynamic programming algorithms.

The folder “data” stores the instances' data. These instances are generated through invoking the project GenerateInstances. The folder “data” contains four subfolders dataset1, dataset2, dataset3, and dataset4. These four folders correspond to the four experiments in the manuscript.
The folder results stores the solution results of the instances.

## Dependency libraries
The five algorithms in the program involve rational number arithmetic and large number arithmetic, so it is necessary to install the gmp library and boost library.


## Other notes
In main.cpp, the variable "data_path" in the int main() function defines the path to read the instance data.

In dynamic_programming.cpp, the variable "file_path" defines the path to save the result data.
