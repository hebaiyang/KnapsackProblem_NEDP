//
// Created by baiyanghe on 03/11/23.
//

#ifndef KNAPSACKPROBLEM_NEDP_DYNAMIC_PROGRAMMING_H
#define KNAPSACKPROBLEM_NEDP_DYNAMIC_PROGRAMMING_H
#include "read_problem.h"
#include <map>
#include <math.h>
#include <limits>
#include <time.h>
#include <chrono>


#define FP_DECIMAL_DIGIT
//The length state during recurision is represented by the length interval
struct LengthState{
    FPinterval length_lb;
    FPinterval length_ub = {0,0};

    bool operator < (const LengthState &ls) const
    {
        return length_lb.ub < ls.length_lb.lb || length_ub.ub < ls.length_ub.ub;
    }
};
struct ScaleLengthState{
    INT_TYPE length_lb;
    INT_TYPE length_ub;

    bool operator < (const ScaleLengthState &ls) const
    {
        return length_lb < ls.length_lb || length_ub < ls.length_ub;
    }

};
struct GMPscaleLengthState{
    GMPint length_lb;
    GMPint length_ub;

    GMPscaleLengthState operator=(GMPscaleLengthState other_ls){
        mpz_set(this->length_lb.value,other_ls.length_lb.value);
        mpz_set(this->length_ub.value,other_ls.length_ub.value);

        return *this;
    }

    bool operator < (const GMPscaleLengthState &ls) const
    {
        //cout<<ls.length_lb.value<<"--"<<length_lb.value<<"--"<<ls.length_ub.value<<"--"<<length_ub.value<<endl;
        return mpz_cmp(ls.length_lb.value,length_lb.value)>0;
    }
    bool operator > (const GMPscaleLengthState &ls) const
    {
        //cout<<ls.length_lb.value<<"--"<<length_lb.value<<"--"<<ls.length_ub.value<<"--"<<length_ub.value<<endl;
        return mpz_cmp(ls.length_lb.value,length_lb.value)<0;
    }
    bool operator== (const GMPscaleLengthState &ls) const
    {
        //cout<<ls.length_lb.value<<"--"<<length_lb.value<<"--"<<ls.length_ub.value<<"--"<<length_ub.value<<endl;
        return mpz_cmp(ls.length_lb.value,length_lb.value)==0;
    }
};
struct RLengthState{
    R_TYPE length_lb;
    R_TYPE length_ub;

    bool operator < (const RLengthState &ls) const
    {
        return length_lb < ls.length_lb || length_ub < ls.length_ub;
    }
};

//The pattern represents the number of the used items in the stock
struct ItemPattern{
    int included_item;
    int included_item_number;
    ItemPattern operator=(ItemPattern other_ip){
        this->included_item=other_ip.included_item;
        this->included_item_number=other_ip.included_item_number;

        return *this;
    }
};

struct CuttingPattern{
    int stock_index;
    FPinterval profit;
    FPinterval length;
    vector<ItemPattern> ip_list;
    vector<int> stage;
    CuttingPattern operator=(CuttingPattern& other_cp){
        this->stock_index=other_cp.stock_index;
        this->profit=other_cp.profit;
        this->length=other_cp.length;
        this->ip_list=other_cp.ip_list;
        this->stage=other_cp.stage;

        return *this;
    }
};
struct ScaleCuttingPattern{
    int stock_index;
    INT_TYPE profit;
    INT_TYPE length;
    vector<ItemPattern> ip_list;
    vector<int> stage;
    bool finishd_cp;
    ScaleCuttingPattern operator=(ScaleCuttingPattern& other_cp){
        this->stock_index=other_cp.stock_index;
        this->profit=other_cp.profit;
        this->length=other_cp.length;
        this->ip_list=other_cp.ip_list;
        this->stage=other_cp.stage;
        this->finishd_cp=other_cp.finishd_cp;

        return *this;
    }
};
struct GMPscaleCuttingPattern{
    int stock_index;
    GMPint profit;
    GMPint length;
    vector<ItemPattern> ip_list;
    vector<int> stage;
    bool finishd_cp;
    GMPscaleCuttingPattern operator=(GMPscaleCuttingPattern& other_cp){
        this->stock_index=other_cp.stock_index;
        mpz_set(this->profit.value,other_cp.profit.value);
        mpz_set(this->length.value,other_cp.length.value);
        this->ip_list=other_cp.ip_list;
        this->stage=other_cp.stage;
        this->finishd_cp=other_cp.finishd_cp;

        return *this;
    }
};
struct RCuttingPattern{
    int stock_index;
    R_TYPE profit;
    R_TYPE length;
    vector<ItemPattern> ip_list;
    vector<int> stage;
    RCuttingPattern operator=(RCuttingPattern& other_cp){
        this->stock_index=other_cp.stock_index;
        this->profit=other_cp.profit;
        this->length=other_cp.length;
        this->ip_list=other_cp.ip_list;
        this->stage=other_cp.stage;

        return *this;
    }
};

struct FloatCuttingPattern{
    int stock_index;
    FP_TYPE profit;
    FP_TYPE length;
    vector<ItemPattern> ip_list;
    vector<int> stage;
    FloatCuttingPattern operator=(FloatCuttingPattern& other_cp){
        this->stock_index=other_cp.stock_index;
        this->profit=other_cp.profit;
        this->length=other_cp.length;
        this->ip_list=other_cp.ip_list;
        this->stage=other_cp.stage;

        return *this;
    }
};

//The pool of the cutting pattern is the collection of the data of cutting patterns.
struct PatternStatePool{
//    map<LengthState,int> lengthState_map_location;//
//    vector<LengthState> length_state_set;
    map<FPinterval,int> lengthState_map_location;//
    vector<FPinterval> length_state_set;
    vector<FPinterval> profit_set;
    vector<CuttingPattern> cp_set;

    PatternStatePool operator=(PatternStatePool psp){
        this->lengthState_map_location=psp.lengthState_map_location;
        this->length_state_set=psp.length_state_set;
        this->profit_set=psp.profit_set;
        vector<CuttingPattern>().swap(cp_set);
        for(unsigned int i=0;i<psp.cp_set.size();i++){
            this->cp_set.push_back(psp.cp_set[i]);
        }

        return *this;
    }
};
struct ScalePatternStatePool{
    map<ScaleLengthState,int> lengthState_map_location;//
    vector<ScaleLengthState> length_state_set;
    vector<INT_TYPE> profit_set;
    vector<ScaleCuttingPattern> cp_set;

    ScalePatternStatePool operator=(ScalePatternStatePool psp){
//        this->lengthState_map_location=psp.lengthState_map_location;
//        this->length_state_set=psp.length_state_set;
//        this->profit_set=psp.profit_set;
//        vector<ScaleCuttingPattern>().swap(cp_set);
//        for(unsigned int i=0;i<psp.cp_set.size();i++){
//            this->cp_set.push_back(psp.cp_set[i]);
//        }

        this->lengthState_map_location=psp.lengthState_map_location;
        vector<ScaleLengthState>().swap(length_state_set);
        for(unsigned int i=0;i<psp.length_state_set.size();i++){
            this->length_state_set.push_back(psp.length_state_set[i]);
        }
        this->profit_set=psp.profit_set;
        vector<ScaleCuttingPattern>().swap(cp_set);
        for(unsigned int i=0;i<psp.cp_set.size();i++){
            this->cp_set.push_back(psp.cp_set[i]);
        }

        return *this;
    }
};

struct GMPscalePatternStatePool{
    map<GMPscaleLengthState,int> lengthState_map_location;//
    vector<GMPscaleLengthState> length_state_set;
    vector<GMPint> profit_set;
    vector<GMPscaleCuttingPattern> cp_set;
    int pattern_number;

    GMPscalePatternStatePool operator=(GMPscalePatternStatePool psp){
        this->lengthState_map_location=psp.lengthState_map_location;
        vector<GMPscaleLengthState>().swap(length_state_set);
        for(unsigned int i=0;i<psp.length_state_set.size();i++){
            this->length_state_set.push_back(psp.length_state_set[i]);
        }
        this->profit_set=psp.profit_set;
        vector<GMPscaleCuttingPattern>().swap(cp_set);
        for(unsigned int i=0;i<psp.cp_set.size();i++){
            this->cp_set.push_back(psp.cp_set[i]);
        }
        this->pattern_number=psp.pattern_number;

        return *this;
    }
};

struct RPatternStatePool{
    map<RLengthState,int> lengthState_map_location;//
    vector<RLengthState> length_state_set;
    vector<R_TYPE> profit_set;
    vector<RCuttingPattern> cp_set;

    RPatternStatePool operator=(RPatternStatePool psp){
        this->lengthState_map_location=psp.lengthState_map_location;
        this->length_state_set=psp.length_state_set;
        this->profit_set=psp.profit_set;
        vector<RCuttingPattern>().swap(cp_set);
        for(unsigned int i=0;i<psp.cp_set.size();i++){
            this->cp_set.push_back(psp.cp_set[i]);
        }

        return *this;
    }
};

struct FloatPatternStatePool{
    map<FP_TYPE,int> lengthState_map_location;//
    vector<FP_TYPE> length_state_set;
    vector<FP_TYPE> profit_set;
    vector<FloatCuttingPattern> cp_set;

    FloatPatternStatePool operator=(FloatPatternStatePool psp){
        this->lengthState_map_location=psp.lengthState_map_location;
        this->length_state_set=psp.length_state_set;
        this->profit_set=psp.profit_set;
        vector<FloatCuttingPattern>().swap(cp_set);
        for(unsigned int i=0;i<psp.cp_set.size();i++){
            this->cp_set.push_back(psp.cp_set[i]);
        }

        return *this;
    }
};

struct Result{
    CuttingPattern cp;

    Result operator=(Result other_result){
        this->cp=other_result.cp;

        return *this;
    }
};

struct ScaleResult{
    ScaleCuttingPattern cp;

    ScaleResult operator=(ScaleResult other_sr){
        this->cp=other_sr.cp;

        return *this;
    }
};
struct GMPscaleResult{
    GMPscaleCuttingPattern cp;

    GMPscaleResult operator=(GMPscaleResult other_sr){
        this->cp=other_sr.cp;

        return *this;
    }
};
struct FloatResult{
    FloatCuttingPattern cp;

    FloatResult operator=(FloatResult other_sr){
        this->cp=other_sr.cp;

        return *this;
    }
};
struct RResult{
    RCuttingPattern cp;

    RResult operator=(RResult other_sr){
        this->cp=other_sr.cp;

        return *this;
    }
};

class FPDP{
public:
    RPatternStatePool rpsp_prev;
    RPatternStatePool rpsp_next;
    ScalePatternStatePool spsp_prev;
    ScalePatternStatePool spsp_next;
    PatternStatePool psp_prev;
    PatternStatePool psp_next;
    FloatPatternStatePool fpsp_next;
    FloatPatternStatePool fpsp_prev;
    GMPscalePatternStatePool gspsp_prev;
    GMPscalePatternStatePool gspsp_next;

    vector<R_TYPE> r_length_list_prev;
    vector<R_TYPE> r_length_list_next;
    vector<INT_TYPE> scale_length_list_prev;
    vector<INT_TYPE> scale_length_list_next;
    vector<FPinterval> fpiLength_list_prev;
    vector<FPinterval> fpiLength_list_next;
    vector<FP_TYPE> f_length_list_prev;
    vector<FP_TYPE> f_length_list_next;
    vector<GMPint> gs_length_list_prev;
    vector<GMPint> gs_length_list_next;

    vector<int> unfinished_index_set_prev;//store the index of the cutting pattern where items can be continued added
    vector<int> unfinished_index_set_next;

    int fp_decimal_digit;
    int dp_flag;//0: using rational class and classical dp; 1: using int class in each stage of classical dp;
    // 2:using int class in part of stages of class dp and using other mehod in the remaining stages;
    //3: using floating-point class and interval dp; this way is executed in the latter part of the way of flag 2
    //4: using floating-point class and interval dp, and then using rational class and classical dp in the remaining stages;
    string fp_type_name;
    FP_TYPE integer_scale_range;
    FP_TYPE max_integer_over_fp;
    int max_scale_factor;
    int max_decimal_digit;

    FPDP();
    ~FPDP();
    void GetFPdecimalDigit(Instance instance);
    int GlobalCheckIntervalAssumption(Instance instance);
    bool StageCheckIntervalAssumption(int stage_max_decimal_digit, int fp_decimal_digit, int stage_a, int stage_b);
    PatternStatePool InitialPatternStatePool(Instance instance);
    vector<FPinterval> InitialPatternLengthList(Instance instance);
    string QueryLengthFPi(FPinterval queried_fpiLength, vector<FPinterval> fpiLength_list);
    bool ParseQuerInfo(string queried_result, int& updated_location);
    int GetDecimalDigit(FPinterval fp_interval, int& scale_factor);
    void GetMaxDecimalDigit(vector<FPinterval> fp_intervals);
    void GetMaxDecimalDigit(Instance instance);
    void GetScaleRange(int scale_factor);
    int GlobalCheckScaleAssumption(Instance instance, int scale_factor);
    bool StageCheckScaleAssumption(INT_TYPE number1, INT_TYPE number2);
    void TransformScaleToInterval();
    void AddPatternState(Instance instance, ItemPattern ip, int prev_iter, FPinterval new_fpiLength,FPinterval new_fpiProfit, int updated_location, vector<int> stage);
    void ReplacePatternState(Instance instance, ItemPattern ip, int prev_iter, FPinterval new_fpiProfit, int updated_location, vector<int> stage);
    void UpdatePatternState(Instance instance, ItemPattern ip, int prev_iter, FPinterval new_fpiLength, FPinterval new_fpiProfit);
    Result GetMaximalPattern();
    void WriteIntervalResults(string name, double computation_time, Result result);

    ScalePatternStatePool InitialScalePatternStatePool(Instance instance);
    vector<INT_TYPE> InitialScalePatternLengthList(Instance instance);
    string QueryScaleLength(INT_TYPE queried_intLength, vector<INT_TYPE> scale_length_list);
    void AddScalePatternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit, int updated_location, vector<int> stage);
    void ReplaceScalePatternState(Instance instance, ItemPattern ip, int prev_iter, int updated_location, INT_TYPE new_intProfit, vector<int> stage);
    ScaleResult GetMaximalScalePattern();
    Instance ScaleData(Instance instance, int scale_factor);
    void UpdateScalePatternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit);
    bool CheckFinishedScalePattern(Instance instance, INT_TYPE length);
    void WriteScaleResults(string name, double computation_time, ScaleResult sr);
    int DPrationalMethod2(Instance instance, RResult rr);

        RPatternStatePool InitialRationalPatternStatePool(Instance instance);
    vector<R_TYPE> InitialRationalPatternLengthList(Instance instance);
    string QueryRLength(R_TYPE queried_intLength, vector<R_TYPE> r_length_list);
    void AddRationalPatternState(Instance instance, ItemPattern ip, int prev_iter, R_TYPE new_rLength, R_TYPE new_rProfit, int updated_location, vector<int> stage);
    void ReplaceRationalPatternState(Instance instance, ItemPattern ip, int prev_iter, int updated_location, R_TYPE new_rProfit,vector<int> stage);
    RResult GetMaximalRationalPattern();
    void UpdateRationalPatternState(Instance instance, ItemPattern ip, int prev_iter, R_TYPE new_rLength, R_TYPE new_rProfit);
    void WriteRationalResults(string name, double computation_time, RResult rr);

    FloatPatternStatePool InitialFloatPatternStatePool(Instance instance);
    vector<FP_TYPE > InitialFloatPatternLengthList(Instance instance);
    void UpdateFloatPatternState(Instance instance, ItemPattern ip, int prev_iter, FP_TYPE new_fpiLength, FP_TYPE new_fpiProfit);
    string QueryFloatLength(FP_TYPE queried_fpiLength, vector<FP_TYPE> fpiLength_list);
    void AddFloatPatternState(Instance instance, ItemPattern ip, int prev_iter, FP_TYPE new_fpiLength, FP_TYPE new_fpiProfit, int updated_location, vector<int> stage);
    void ReplaceFloatPatternState(Instance instance, ItemPattern ip, int prev_iter, FP_TYPE new_fpiProfit, int updated_location, vector<int> stage);
    FloatResult GetMaximalFloatPattern();
    void WriteFloatResults(string name, double computation_time, FloatResult sr);
    string QueryEpsilonFloatLength(FP_TYPE queried_fpiLength, vector<FP_TYPE> fpiLength_list);

        GMPscalePatternStatePool InitialGMPscalePatternStatePool(Instance instance);
    vector<GMPint> InitialGMPscalePatternLengthList(Instance instance);
    string QueryGMPscaleLength(GMPint queried_intLength, vector<GMPint> scale_length_list);
    void UpdateGMPscalePatternState(Instance instance, ItemPattern ip, int prev_iter, GMPint new_intLength, GMPint new_intProfit);
    void AddGMPscalePatternState(Instance instance, ItemPattern ip, int prev_iter, GMPint new_intLength, GMPint new_intProfit,
                                 int updated_location, vector<int> stage);
    void ReplaceGMPscalePatternState(Instance instance, ItemPattern ip, int prev_iter, int updated_location, GMPint new_intProfit, vector<int> stage);
    Instance GMPscaleData(Instance instance, int scale_factor);
    GMPscaleResult GetMaximalGMPscalePattern();
    void WriteGMPscaleResults(string name, double computation_time, GMPscaleResult sr);
    int DPgmpScalingMethod(Instance instance, GMPscaleResult sr);


    void AddNEptternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit,
                              FPinterval new_fpiLength, FPinterval new_fpiProfit,  int updated_location, vector<int> stage);
    void UpdateNEpatternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit,
                                    FPinterval new_fpiLength, FPinterval new_fpiProfit);
    void WriteNumerExactResults(string name, double computation_time, ScaleResult sr, Result result, int flag);
    int GetMaximalNumerExactPattern(ScaleResult& sr, Result& result);


        int DPfloatingMethod(Instance instance, FloatResult sr);
    int DPintervalMehod(Instance instance, Result& result);
    int DPintervalMehod2(Instance instance, Result& result);
    int DPrationalMethod(Instance instance, RResult rr);
    int DPScalingMethod(Instance instance, ScaleResult sr);
    int DPnumerExactMethod(Instance instance,ScaleResult sr, Result result);
    int DPepsilonMethod(Instance, FloatResult fr);
    int DP(Instance instance, Result result);

};
#endif //KNAPSACKPROBLEM_NEDP_DYNAMIC_PROGRAMMING_H
