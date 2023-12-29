#include <iostream>
#include "read_problem.h"
#include "dynamic_programming.h"

int main() {
    vector<Instance> instance_set= read_instance("../data/dataset1");

    for(unsigned int i=0;i<instance_set.size();i++){
        cout<<"-----------------------test instance "<<i<<"---------------------"<<endl;
        Instance instance = instance_set[i];
        cout<<"-------------------read "<<instance.instance_name<<"-------------"<<endl;

        FPDP fpdp;
        fpdp.DP(instance);
        cout<<"------------------------end testing instance "<<i<<"--------------------"<<endl;

    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
