#include <iostream>
#include "read_problem.h"
#include "dynamic_programming.h"

int main() {
    vector<Instance> instance_set= read_instance("../data/scale_analysis");

    for(unsigned int i=4;i<instance_set.size();i++){
        cout<<"-----------------------test instance "<<i<<"---------------------"<<endl;
        Instance instance = instance_set[i];
        cout<<"-------------------read "<<instance.instance_name<<"-------------"<<endl;
//        if(instance.instance_name=="Uncorrelated_2_6.txt" || instance.instance_name=="Uncorrelated_4_4.txt"){
//            cout<<"------------------------jump testing instance "<<i<<"--------------------"<<endl;
//            continue;
//        }
        FPDP fpdp;
        Result result;
        fpdp.DP(instance,result);
        cout<<"------------------------end testing instance "<<i<<"--------------------"<<endl;

    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
