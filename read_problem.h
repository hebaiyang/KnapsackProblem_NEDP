//
// Created by baiyanghe on 02/11/23.
//

#ifndef KNAPSACKPROBLEM_NEDP_READ_PROBLEM_H
#define KNAPSACKPROBLEM_NEDP_READ_PROBLEM_H

#include <fstream>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <cctype>
#include <algorithm>
#include <fenv.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/rational.hpp>
#include <cmath>
#include <gmpxx.h>

using namespace boost;
using namespace std;

typedef double FP_TYPE;
typedef int INT_TYPE;
typedef rational<INT_TYPE> R_TYPE;

#define EPSILON 1e-6

struct GMPint{
    mpz_t value;


    GMPint(){
        mpz_init(value);
    }
    GMPint operator=(GMPint gint){
        mpz_set(this->value,gint.value);

        return *this;
    }

    GMPint operator+(const GMPint& gint){
        GMPint other_gint;
        mpz_add(other_gint.value,value,gint.value);

        return other_gint;
    }

    bool operator < (const GMPint gint)const{
        return mpz_cmp(value,gint.value)<0;
    }
    bool operator > (const GMPint gint)  const{
        return mpz_cmp(value,gint.value)>0;
    }
    bool operator ==(const GMPint gint) const{
        return mpz_cmp(value,gint.value)==0;
    }
    bool operator != (const GMPint gint) const{
        return  mpz_cmp(value,gint.value)!=0;
    }
};

struct GMPrational{
    mpq_t value;

    GMPrational(){
        mpq_init(value);
    }
    GMPrational operator=(GMPrational gint){
        mpq_set(this->value,gint.value);

        return *this;
    }

    GMPrational operator+(const GMPrational& gint){
        GMPrational other_gint;
        mpq_add(other_gint.value,value,gint.value);

        return other_gint;
    }

    bool operator < (const GMPrational gint)const{
        return mpq_cmp(value,gint.value)<0;
    }
    bool operator > (const GMPrational gint)  const{
        return mpq_cmp(value,gint.value)>0;
    }
    bool operator ==(const GMPrational gint) const{
        return mpq_cmp(value,gint.value)==0;
    }
    bool operator != (const GMPrational gint) const{
        return  mpq_cmp(value,gint.value)!=0;
    }
};

struct FPinterval{
    FP_TYPE lb;
    FP_TYPE ub;

    FPinterval operator=(FPinterval fpi){
        this->lb=fpi.lb;
        this->ub=fpi.ub;

        return *this;
    }

    bool operator == (const FPinterval &other_fpi) const{
        return (lb<=other_fpi.ub && ub>=other_fpi.lb) || (other_fpi.lb<=ub && other_fpi.ub>=lb);
    }

    bool operator < (const FPinterval &other_fpi) const{
        return ub<other_fpi.lb;
    }

    bool operator > (const FPinterval &other_fpi) const{
        return lb>other_fpi.ub;
    }

};

struct FPgmpInterval{
    mpf_t lb;
    mpf_t ub;

    FPgmpInterval(){
        mpf_init(lb);
        mpf_init(ub);
    }
    FPgmpInterval operator=(FPgmpInterval fpi){
        mpf_set(this->lb,fpi.lb);
        mpf_set(this->ub,fpi.ub);

        return *this;
    }

    bool operator == (const FPgmpInterval &other_fpi) const{
        return (mpf_cmp(other_fpi.ub,lb)>=0) && (mpf_cmp(ub,other_fpi.lb)>=0);
    }

    bool operator <(const FPgmpInterval &other_fpi) const{
        return mpf_cmp(other_fpi.lb,ub)>0;
    }

    bool operator > (const FPgmpInterval &other_fpi) const{
        return mpf_cmp(lb,other_fpi.ub)>0;
    }
};


class Item{
public:
    int index;//index of the item
    FP_TYPE length;
    INT_TYPE scale_length;
    R_TYPE r_length;
    FPinterval length_interval;// length interval of the item
    int demand;//demand of the interval
    FPinterval profit_interval;
    INT_TYPE scale_profit;
    R_TYPE r_profit;
    FP_TYPE profit;
    FPinterval unit_prof_interval;

    mpf_t gmp_length;
    mpf_t gmp_profit;
    GMPint gmp_scale_length;
    GMPint gmp_scale_profit;
    mpq_t gmp_r_length;
    mpq_t gmp_r_profit;
    FPgmpInterval gmp_length_interval;
    FPgmpInterval gmp_profit_interval;

    Item();
    Item(const Item& item);
};

bool CompLength(const Item& a, const Item& b);

bool CompUnitProf(const Item& a, const Item& b);

struct Instance
{
    int digit;
    int items_number;
    int stocks_number;
    FPinterval stock_length_interval;
    vector<Item> item_set;
    FP_TYPE stock_length;
    INT_TYPE scale_stock_length;
    R_TYPE r_stock_length;
    string instance_name;

    mpf_t gmp_stock_length;
    GMPint gmp_scale_stock_length;
    mpq_t gmp_r_stock_length;
    FPgmpInterval gmp_stock_length_interval;

    Instance(){
        mpf_init(gmp_stock_length);
        mpz_init(gmp_scale_stock_length.value);
        mpq_init(gmp_r_stock_length);
        mpf_init(gmp_stock_length_interval.lb);
        mpf_init(gmp_stock_length_interval.ub);
    }

    Instance operator=(Instance& instance){
        this->digit=instance.digit;
        this->items_number=instance.items_number;
        this->stock_length_interval=instance.stock_length_interval;
        vector<Item>().swap(item_set);
        for(unsigned int i=0;i<item_set.size();i++){
            this->item_set.push_back(instance.item_set[i]);
        }
        this->scale_stock_length=instance.scale_stock_length;
        this->instance_name = instance.instance_name;
        mpf_set(this->gmp_stock_length,instance.gmp_stock_length);
        mpz_set(this->gmp_scale_stock_length.value,instance.gmp_scale_stock_length.value);
        mpq_set(this->gmp_r_stock_length,instance.gmp_r_stock_length);
        this->gmp_stock_length_interval=instance.gmp_stock_length_interval;

        return *this;
    }
};



int scanFiles(vector<string> &fileList, string inputDirectory);

int GetFiles(const string& path, vector<string> &files, vector<string> suffixs);

//
vector<string> split(string target_str, string split_symbol);

vector<Instance> read_instance(
        const string path/*data file path*/
);

void RemoveDuplicate(vector<int>& vec);

#endif //KNAPSACKPROBLEM_NEDP_READ_PROBLEM_H
