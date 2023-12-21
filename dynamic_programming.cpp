//
// Created by baiyanghe on 03/11/23.
//
#include "dynamic_programming.h"

FPDP::FPDP() {
    fp_decimal_digit = 0;
    dp_flag = 0;
    fp_type_name = "";
    integer_scale_range = 0;
    max_integer_over_fp = 0;
    max_scale_factor = 0;
    max_decimal_digit = 0;
}

FPDP::~FPDP() {}

FloatPatternStatePool FPDP::InitialFloatPatternStatePool(Instance instance){
    //initial length state includes two length state, which are the floating-point interval of 0 and the stock's length.
    FP_TYPE fpiLength1 = 0;
    //initialize the set that stores the location of the length state in the set of length state.
    map<FP_TYPE,int> lengthState_map_location={{fpiLength1,0}};
    //initialize the set of length state
    vector<FP_TYPE> length_state_set={fpiLength1};
    //initialize the set of profits of the length states
    FP_TYPE fpiProfit = 0;
    vector<FP_TYPE> profit_set = {fpiProfit};
    //initialize the set of generated cutting patterns
    ItemPattern ip = {-1,-1};
    FloatCuttingPattern cp = {0,fpiProfit,fpiLength1,{ip},{0,0}};
    vector<FloatCuttingPattern> cp_set = {cp};

    return {lengthState_map_location,length_state_set,profit_set,cp_set};
}

PatternStatePool FPDP::InitialPatternStatePool(Instance instance){
    //initial length state includes two length state, which are the floating-point interval of 0 and the stock's length.
    FPinterval fpiLength1 = {0,0};
    //initialize the set that stores the location of the length state in the set of length state.
    map<FPinterval,int> lengthState_map_location={{fpiLength1,0}};
    //initialize the set of length state
    vector<FPinterval> length_state_set={fpiLength1};
    //initialize the set of profits of the length states
    FPinterval fpiProfit = {0.0,0.0};
    vector<FPinterval> profit_set = {fpiProfit};
    //initialize the set of generated cutting patterns
    ItemPattern ip = {-1,-1};
    CuttingPattern cp = {0,fpiProfit,fpiLength1,{ip},{0,0}};
    vector<CuttingPattern> cp_set = {cp};

    return {lengthState_map_location,length_state_set,profit_set,cp_set};

//    //initial length state includes two length state, which are the floating-point interval of 0 and the stock's length.
//    FPinterval fpiLength1 = {0,0};
//    FPinterval fpiLength2 = instance.stock_length_interval;
//    LengthState ls = {fpiLength1,fpiLength2};
//    //initialize the set that stores the location of the length state in the set of length state.
//    map<LengthState,int> lengthState_map_location={{ls,0}};
//    //initialize the set of length state
//    vector<LengthState> length_state_set={ls};
//    //initialize the set of profits of the length states
//    FPinterval fpiProfit = {0.0,0.0};
//    vector<FPinterval> profit_set = {fpiProfit};
//    //initialize the set of generated cutting patterns
//    ItemPattern ip = {-1,-1};
//    CuttingPattern cp = {0,fpiProfit,fpiLength1,{ip},{0,0}};
//    vector<CuttingPattern> cp_set = {cp};
//
//    return {lengthState_map_location,length_state_set,profit_set,cp_set};
}

ScalePatternStatePool FPDP::InitialScalePatternStatePool(Instance instance){
    //initial length state includes two length state, which are the floating-point interval of 0 and the stock's length.
    INT_TYPE intLength1 = 0;
    INT_TYPE intLength2 = instance.scale_stock_length;
    ScaleLengthState ls1 = {intLength1,intLength2};
    //caleLengthState ls2 = {intLength2,intLength2};
    //initialize the set that stores the location of the length state in the set of length state.
    //ap<ScaleLengthState,int> lengthState_map_location={{ls1,0},{ls2,1}};
    map<ScaleLengthState,int> lengthState_map_location={{ls1,0}};
    //initialize the set of length state
    //vector<ScaleLengthState> length_state_set={ls1,ls2};
    vector<ScaleLengthState> length_state_set={ls1};
    //initialize the set of profits of the length states
    INT_TYPE intProfit = 0;
    //vector<INT_TYPE> profit_set = {intProfit, intProfit};
    vector<INT_TYPE> profit_set = {intProfit};

//initialize the set of generated cutting patterns
    ItemPattern ip = {-1,-1};
    ScaleCuttingPattern cp = {0,intProfit,intLength1,{ip},{0,0}};
    //vector<ScaleCuttingPattern> cp_set = {cp,cp};
    vector<ScaleCuttingPattern> cp_set = {cp};


    return {lengthState_map_location,length_state_set,profit_set,cp_set};

}

GMPscalePatternStatePool FPDP::InitialGMPscalePatternStatePool(Instance instance){
    //initial length state includes two length state, which are the floating-point interval of 0 and the stock's length.
    GMPint intLength1;
    GMPint intLength2;
    mpz_set_ui(intLength1.value,0);
    mpz_set(intLength2.value,instance.gmp_scale_stock_length.value);
    GMPscaleLengthState ls1;
    mpz_set(ls1.length_lb.value,intLength1.value);
    mpz_set(ls1.length_ub.value,intLength2.value);

    //caleLengthState ls2 = {intLength2,intLength2};
    //initialize the set that stores the location of the length state in the set of length state.
    //ap<ScaleLengthState,int> lengthState_map_location={{ls1,0},{ls2,1}};
    map<GMPscaleLengthState,int> lengthState_map_location={{ls1,0}};
    //initialize the set of length state
    //vector<ScaleLengthState> length_state_set={ls1,ls2};
    vector<GMPscaleLengthState> length_state_set={ls1};
    //initialize the set of profits of the length states
    GMPint intProfit;
    mpz_set_ui(intProfit.value,0);
    //vector<INT_TYPE> profit_set = {intProfit, intProfit};
    vector<GMPint> profit_set;
    profit_set.push_back(intProfit);

//initialize the set of generated cutting patterns
    ItemPattern ip = {-1,-1};
    GMPscaleCuttingPattern cp = {0,intProfit,intLength1,{ip},{0,0}};

    //vector<ScaleCuttingPattern> cp_set = {cp,cp};
    vector<GMPscaleCuttingPattern> cp_set = {cp};

    return {lengthState_map_location,length_state_set,profit_set,cp_set};
}

RPatternStatePool FPDP::InitialRationalPatternStatePool(Instance instance){
    //initial length state includes two length state, which are the floating-point interval of 0 and the stock's length.
    R_TYPE intLength1;
    R_TYPE intLength2(instance.r_stock_length);
    RLengthState ls1 = {intLength1,intLength2};
    //initialize the set that stores the location of the length state in the set of length state.
    map<RLengthState,int> lengthState_map_location={{ls1,0}};
    //initialize the set of length state
    vector<RLengthState> length_state_set={ls1};
    //initialize the set of profits of the length states
    R_TYPE intProfit;
    vector<R_TYPE> profit_set = {intProfit};
    //initialize the set of generated cutting patterns
    ItemPattern ip = {-1,-1};
    RCuttingPattern cp = {0,intProfit,intLength1,{ip},{0,0}};
    vector<RCuttingPattern> cp_set = {cp};

    return {lengthState_map_location,length_state_set,profit_set,cp_set};
}

vector<FP_TYPE > FPDP::InitialFloatPatternLengthList(Instance instance){
    return {0};
}

vector<FPinterval> FPDP::InitialPatternLengthList(Instance instance){
    return {{0,0}};
}

vector<INT_TYPE> FPDP::InitialScalePatternLengthList(Instance instance){
    return {0,instance.scale_stock_length};//The repeated scale_stock_length are used to construct the length_state [scale_stock_length,scale_stock_length]
}

vector<GMPint> FPDP::InitialGMPscalePatternLengthList(Instance instance){
    vector<GMPint> pattern_list;
    GMPint gi;
    mpz_set_ui(gi.value,0);
    pattern_list.push_back(gi);
    mpz_set(gi.value,instance.gmp_scale_stock_length.value);
    pattern_list.push_back(gi);
    return pattern_list;
}

vector<R_TYPE> FPDP::InitialRationalPatternLengthList(Instance instance){
    return {0,instance.r_stock_length};
}

string FPDP::QueryEpsilonFloatLength(FP_TYPE queried_fpiLength, vector<FP_TYPE> fpiLength_list){
    vector<FP_TYPE>::iterator it = std::find_if(fpiLength_list.begin(), fpiLength_list.end(), [queried_fpiLength](const FP_TYPE &fpi) {return queried_fpiLength-fpi>-EPSILON && queried_fpiLength - fpi<EPSILON;});
    if(it !=fpiLength_list.end()){
        return "Equal_"+ to_string(distance(fpiLength_list.begin(),it));
    }
    else{
        return "New_-1";
    }
}



string FPDP::QueryFloatLength(FP_TYPE queried_fpiLength, vector<FP_TYPE> fpiLength_list){
    vector<FP_TYPE>::iterator it = std::find_if(fpiLength_list.begin(), fpiLength_list.end(), [queried_fpiLength](const FP_TYPE &fpi) {return queried_fpiLength==fpi;});
    if(it !=fpiLength_list.end()){
        return "Equal_"+ to_string(distance(fpiLength_list.begin(),it));
    }
    else{
        return "New_-1";
    }
}

//Check if the target length is in the length list (denoted by the string "A" or "B")
// and get the index of the maximum length in the length list that does not exceed the target length.
string FPDP::QueryLengthFPi(FPinterval queried_fpiLength, vector<FPinterval> fpiLength_list){
    vector<FPinterval>::iterator it = std::find_if(fpiLength_list.begin(), fpiLength_list.end(), [queried_fpiLength](const FPinterval &fpi) {return queried_fpiLength==fpi;});
    if(it !=fpiLength_list.end()){
        return "Equal_"+ to_string(distance(fpiLength_list.begin(),it));
    }
    else{
        return "New_-1";
    }

////    for(unsigned int i=0;i<fpiLength_list.size();i++){
////        if(queried_fpiLength == fpiLength_list[i] && i!= fpiLength_list.size()-1){
////            return "Equal_"+ to_string(i);
////        }
////        else if(queried_fpiLength < fpiLength_list[i]){
////            return "New_"+ to_string(i);
////        }
////        else if(queried_fpiLength == fpiLength_list[i] && i== fpiLength_list.size()-1){
////            return "New_"+ to_string(i);
////        }
////    }
//
//    return "Error_"+ to_string(-1);
}

string FPDP::QueryScaleLength(INT_TYPE queried_intLength, vector<INT_TYPE> scale_length_list){
    for(unsigned int i=0;i<scale_length_list.size();i++){
        if(queried_intLength == scale_length_list[i] && i!=scale_length_list.size()-1){
            return "Equal_"+ to_string(i);
        }
        else if(queried_intLength<scale_length_list[i]){
            return "New_"+ to_string(i);
        }
        else if(queried_intLength == scale_length_list[i]  && i==scale_length_list.size()-1){
            return "New_"+ to_string(scale_length_list.size()-1);
        }
    }

    return "Error_"+ to_string(-1);
}

string FPDP::QueryGMPscaleLength(GMPint queried_intLength, vector<GMPint> scale_length_list){
    for(unsigned int i=0;i<scale_length_list.size();i++){
        if(queried_intLength == scale_length_list[i] && i!=scale_length_list.size()-1){
            return "Equal_"+ to_string(i);
        }
        else if(queried_intLength<scale_length_list[i]){
            return "New_"+ to_string(i);
        }
        else if(queried_intLength == scale_length_list[i]  && i==scale_length_list.size()-1){
            return "New_"+ to_string(scale_length_list.size()-1);
        }
    }

    return "Error_"+ to_string(-1);
}

string FPDP::QueryRLength(R_TYPE queried_intLength, vector<R_TYPE> r_length_list){
    for(unsigned int i=0;i<r_length_list.size();i++){
        if(queried_intLength == r_length_list[i] && i!=r_length_list.size()-1){
            return "Equal_"+ to_string(i);
        }
        else if(queried_intLength<r_length_list[i]){
            return "New_"+ to_string(i);
        }
        else if(queried_intLength == r_length_list[i] && i==r_length_list.size()-1){
            return "New_"+ to_string(i);
        }
    }

    return "Error_"+ to_string(-1);
}

//Gets information about whether the target length is to be inserted into the length list from the
// resulting string of the check for the target length. If inserted, returns the position of the
// previous element of the target length in the length list to previous_index.
bool FPDP::ParseQuerInfo(string quried_result, int& updated_location){
    vector<string> string_elements= split(quried_result,"_");
    updated_location= atoi(string_elements[1].c_str());

    if(string_elements[0]=="New"){
        return true;
    }
    else{
        return false;
    }
}

bool FPDP::CheckFinishedScalePattern(Instance instance, INT_TYPE length){
    INT_TYPE length_temp = length + instance.item_set[instance.items_number-1].scale_length;
    return length_temp > instance.scale_stock_length;
}

void FPDP::AddFloatPatternState(Instance instance, ItemPattern ip, int prev_iter, FP_TYPE new_fpiLength, FP_TYPE new_fpiProfit, int updated_location, vector<int> stage){
    int state_number = fpsp_next.profit_set.size();

    //remove the previous state and insert two new states
    fpsp_next.lengthState_map_location.insert(pair<FP_TYPE,int>(new_fpiLength,state_number));

    fpsp_next.length_state_set.push_back(new_fpiLength);

    fpsp_next.profit_set.push_back(new_fpiProfit);

    FP_TYPE origin_state_prev = f_length_list_prev[prev_iter];
    int state_index_prev = fpsp_prev.lengthState_map_location[origin_state_prev];
    vector<ItemPattern> ip_list = fpsp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);

    FloatCuttingPattern cp = {0,new_fpiProfit,new_fpiLength,ip_list, stage};
    fpsp_next.cp_set.push_back(cp);

}

void FPDP::AddPatternState(Instance instance, ItemPattern ip, int prev_iter, FPinterval new_fpiLength, FPinterval new_fpiProfit, int updated_location, vector<int> stage){
    int state_number = psp_next.profit_set.size();

    //remove the previous state and insert two new states
    psp_next.lengthState_map_location.insert(pair<FPinterval,int>(new_fpiLength,state_number));

    psp_next.length_state_set.push_back(new_fpiLength);

    psp_next.profit_set.push_back(new_fpiProfit);

    FPinterval origin_state_prev = fpiLength_list_prev[prev_iter];
    int state_index_prev = psp_prev.lengthState_map_location[origin_state_prev];
    vector<ItemPattern> ip_list = psp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);

    CuttingPattern cp = {0,new_fpiProfit,new_fpiLength,ip_list, stage};
    psp_next.cp_set.push_back(cp);

//    LengthState origin_state = {fpiLength_list_next[updated_location-1],fpiLength_list_next[updated_location]};
//    int state_index = psp_next.lengthState_map_location[origin_state];
//    int state_number = psp_next.profit_set.size();
//    FPinterval origin_profit = psp_next.profit_set[state_index];
//
//    //remove the previous state and insert two new states
//    LengthState ls1 = {fpiLength_list_next[updated_location-1],new_fpiLength};
//    psp_next.lengthState_map_location.erase(origin_state);
//    psp_next.lengthState_map_location.insert(pair<LengthState,int>(ls1,state_index));
//    LengthState ls2 = {new_fpiLength,fpiLength_list_next[updated_location]};
//    psp_next.lengthState_map_location.insert(pair<LengthState,int>(ls2,state_number));
//
//    psp_next.length_state_set.erase(psp_next.length_state_set.begin()+state_index);
//    psp_next.length_state_set.insert(psp_next.length_state_set.begin()+state_index,ls1);
//    psp_next.length_state_set.push_back(ls2);
//
//    psp_next.profit_set.push_back(new_fpiProfit);
//
//    LengthState origin_state_prev = {fpiLength_list_prev[prev_iter],fpiLength_list_prev[prev_iter+1]};
//    int state_index_prev = psp_prev.lengthState_map_location[origin_state_prev];
//    vector<ItemPattern> ip_list = psp_prev.cp_set[state_index_prev].ip_list;
//    ip_list.push_back(ip);
//
//    CuttingPattern cp = {0,new_fpiProfit,new_fpiLength,ip_list, stage};
//    psp_next.cp_set.push_back(cp);

}

void FPDP::AddScalePatternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit,
                                int updated_location, vector<int> stage){
    ScaleLengthState origin_state = {scale_length_list_next[updated_location-1],scale_length_list_next[updated_location]};
    int state_index_next = spsp_next.lengthState_map_location[origin_state];
    int state_number_next = spsp_next.length_state_set.size();
    INT_TYPE origin_profit = spsp_next.profit_set[state_index_next];

    //remove the previous state and insert two new states
    ScaleLengthState ls1 = {scale_length_list_next[updated_location-1],new_intLength};
    spsp_next.lengthState_map_location.erase(origin_state);
    spsp_next.lengthState_map_location.insert(pair<ScaleLengthState,int>(ls1,state_index_next));
    ScaleLengthState ls2 = {new_intLength,scale_length_list_next[updated_location]};
    spsp_next.lengthState_map_location.insert(pair<ScaleLengthState,int>(ls2,state_number_next));

    spsp_next.length_state_set.erase(spsp_next.length_state_set.begin()+state_index_next);
    spsp_next.length_state_set.insert(spsp_next.length_state_set.begin()+state_index_next,ls1);
    spsp_next.length_state_set.push_back(ls2);


//    spsp_next.profit_set.erase(spsp_next.profit_set.begin()+state_index);
//    spsp_next.profit_set.insert(spsp_next.profit_set.begin()+state_index,origin_profit);
    spsp_next.profit_set.push_back(new_intProfit);

    ScaleLengthState origin_state_prev = {scale_length_list_prev[prev_iter],scale_length_list_prev[prev_iter+1]};
    int state_index_prev = spsp_prev.lengthState_map_location[origin_state_prev];
    vector<ItemPattern> ip_list = spsp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);

    ScaleCuttingPattern cp = {0,new_intProfit,new_intLength,ip_list, stage};
    spsp_next.cp_set.push_back(cp);


}

void FPDP::AddNEptternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit,
                            FPinterval new_fpiLength, FPinterval new_fpiProfit, int updated_location, vector<int> stage){
    ScaleLengthState origin_state = {scale_length_list_next[updated_location-1],scale_length_list_next[updated_location]};
    int state_index_next = spsp_next.lengthState_map_location[origin_state];
    int state_number_next = spsp_next.length_state_set.size();
    INT_TYPE origin_profit = spsp_next.profit_set[state_index_next];

    //remove the previous state and insert two new states
    ScaleLengthState ls1 = {scale_length_list_next[updated_location-1],new_intLength};
    spsp_next.lengthState_map_location.erase(origin_state);
    spsp_next.lengthState_map_location.insert(pair<ScaleLengthState,int>(ls1,state_index_next));

    ScaleLengthState ls2 = {new_intLength,scale_length_list_next[updated_location]};
    spsp_next.lengthState_map_location.insert(pair<ScaleLengthState,int>(ls2,state_number_next));

    spsp_next.length_state_set.erase(spsp_next.length_state_set.begin()+state_index_next);
    spsp_next.length_state_set.insert(spsp_next.length_state_set.begin()+state_index_next,ls1);
    spsp_next.length_state_set.push_back(ls2);

    spsp_next.profit_set.push_back(new_intProfit);

    ScaleLengthState origin_state_prev = {scale_length_list_prev[prev_iter],scale_length_list_prev[prev_iter+1]};
    int state_index_prev = spsp_prev.lengthState_map_location[origin_state_prev];
    vector<ItemPattern> ip_list = spsp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);

    ScaleCuttingPattern cp = {0,new_intProfit,new_intLength,ip_list, stage};
    spsp_next.cp_set.push_back(cp);

    int interval_state_number = psp_next.profit_set.size();

    //remove the previous state and insert two new states
    psp_next.lengthState_map_location.insert(pair<FPinterval,int>(new_fpiLength,interval_state_number));

    psp_next.length_state_set.push_back(new_fpiLength);

    psp_next.profit_set.push_back(new_fpiProfit);

    FPinterval interval_origin_state_prev = fpiLength_list_prev[prev_iter];
    int interval_state_index_prev = psp_prev.lengthState_map_location[interval_origin_state_prev];
    vector<ItemPattern> interval_ip_list = psp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);

    CuttingPattern interval_cp = {0,new_fpiProfit,new_fpiLength,ip_list, stage};
    psp_next.cp_set.push_back(interval_cp);
}

void FPDP::AddGMPscalePatternState(Instance instance, ItemPattern ip, int prev_iter, GMPint new_intLength, GMPint new_intProfit,
                                   int updated_location, vector<int> stage){
    GMPscaleLengthState origin_state = {gs_length_list_next[updated_location-1],gs_length_list_next[updated_location]};
    int state_index_next = gspsp_next.lengthState_map_location[origin_state];
    int state_number_next = gspsp_next.length_state_set.size();
    GMPint origin_profit = gspsp_next.profit_set[state_index_next];

    //remove the previous state and insert two new states
    GMPscaleLengthState ls1 = {gs_length_list_next[updated_location-1],new_intLength};
    gspsp_next.lengthState_map_location.erase(origin_state);
    gspsp_next.lengthState_map_location.insert(pair<GMPscaleLengthState,int>(ls1,state_index_next));
    GMPscaleLengthState ls2 = {new_intLength,gs_length_list_next[updated_location]};
    gspsp_next.lengthState_map_location.insert(pair<GMPscaleLengthState,int>(ls2,state_number_next));

    gspsp_next.length_state_set.erase(gspsp_next.length_state_set.begin()+state_index_next);
    gspsp_next.length_state_set.insert(gspsp_next.length_state_set.begin()+state_index_next,ls1);
    gspsp_next.length_state_set.push_back(ls2);


//    spsp_next.profit_set.erase(spsp_next.profit_set.begin()+state_index);
//    spsp_next.profit_set.insert(spsp_next.profit_set.begin()+state_index,origin_profit);
    gspsp_next.profit_set.push_back(new_intProfit);

    GMPscaleLengthState origin_state_prev = {gs_length_list_prev[prev_iter],gs_length_list_prev[prev_iter+1]};
    int state_index_prev = gspsp_prev.lengthState_map_location[origin_state_prev];
    vector<ItemPattern> ip_list = gspsp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);

    GMPscaleCuttingPattern cp = {0,new_intProfit,new_intLength,ip_list, stage};
    gspsp_next.cp_set.push_back(cp);

//    GMPint length_temp;
//    mpz_set_ui(length_temp.value,0);
//    GMPint numb_temp;
//    for(unsigned int i=1;i<ip_list.size();i++){
//        mpz_mul_ui(numb_temp.value,instance.item_set[ip_list[i].included_item].gmp_scale_length.value,ip_list[i].included_item_number);
//        mpz_add(length_temp.value,length_temp.value,numb_temp.value);
//    }
//    if(length_temp != new_intLength){
//        cout<<"stop here"<<endl;
//    }
}

void FPDP::AddRationalPatternState(Instance instance, ItemPattern ip, int prev_iter, R_TYPE new_rLength, R_TYPE new_rProfit, int updated_location, vector<int> stage){
    RLengthState origin_state = {r_length_list_next[updated_location-1],r_length_list_next[updated_location]};
    int state_index = rpsp_next.lengthState_map_location[origin_state];
    int state_number = rpsp_next.profit_set.size();
    R_TYPE origin_profit = rpsp_next.profit_set[state_index];

    //remove the previous state and insert two new states
    RLengthState ls1 = {r_length_list_next[updated_location-1],new_rLength};
    rpsp_next.lengthState_map_location.erase(origin_state);
    rpsp_next.lengthState_map_location.insert(pair<RLengthState,int>(ls1,state_index));
    RLengthState ls2 = {new_rLength,r_length_list_next[updated_location]};
    rpsp_next.lengthState_map_location.insert(pair<RLengthState,int>(ls2,state_number));

    rpsp_next.length_state_set.erase(rpsp_next.length_state_set.begin()+state_index);
    rpsp_next.length_state_set.insert(rpsp_next.length_state_set.begin()+state_index,ls1);
    rpsp_next.length_state_set.push_back(ls2);


    rpsp_next.profit_set.push_back(new_rProfit);

    RLengthState origin_state_prev = {r_length_list_prev[prev_iter],r_length_list_prev[prev_iter+1]};
    int state_index_prev = rpsp_prev.lengthState_map_location[origin_state_prev];
    vector<ItemPattern> ip_list = rpsp_prev.cp_set[state_index_prev].ip_list;
    ip_list.push_back(ip);


    RCuttingPattern cp = {0,new_rProfit,new_rLength,ip_list, stage};
    rpsp_next.cp_set.push_back(cp);

}

void FPDP::ReplaceFloatPatternState(Instance instance, ItemPattern ip, int prev_iter, FP_TYPE new_fpiProfit, int updated_location, vector<int> stage){
    FP_TYPE origin_state = f_length_list_next[updated_location];
    int state_index = fpsp_next.lengthState_map_location[origin_state];
    int state_number=fpsp_next.profit_set.size();
    FP_TYPE origin_profit = fpsp_next.profit_set[state_index];

    if(origin_profit<new_fpiProfit){
        fpsp_next.profit_set[state_index] = new_fpiProfit;

        FP_TYPE origin_state_prev = f_length_list_prev[prev_iter];
        int state_index_prev = fpsp_prev.lengthState_map_location[origin_state_prev];
        vector<ItemPattern> ip_list = fpsp_prev.cp_set[state_index_prev].ip_list;
        ip_list.push_back(ip);

        FloatCuttingPattern cp = {0,new_fpiProfit,fpsp_next.cp_set[state_index].length,ip_list,stage};
        fpsp_next.cp_set[state_index]=cp;
    }

}

void FPDP::ReplacePatternState(Instance instance, ItemPattern ip, int prev_iter, FPinterval new_fpiProfit, int updated_location, vector<int> stage){
    FPinterval origin_state = fpiLength_list_next[updated_location];
    int state_index = psp_next.lengthState_map_location[origin_state];
    int state_number=psp_next.profit_set.size();
    FPinterval origin_profit = psp_next.profit_set[state_index];

    if(origin_profit<new_fpiProfit){
        psp_next.profit_set[state_index] = new_fpiProfit;

        FPinterval origin_state_prev = fpiLength_list_prev[prev_iter];
        int state_index_prev = psp_prev.lengthState_map_location[origin_state_prev];
        vector<ItemPattern> ip_list = psp_prev.cp_set[state_index_prev].ip_list;
        ip_list.push_back(ip);

        CuttingPattern cp = {0,new_fpiProfit,psp_next.cp_set[state_index].length,ip_list,stage};
        psp_next.cp_set[state_index]=cp;
    }

}

void FPDP::ReplaceScalePatternState(Instance instance, ItemPattern ip, int prev_iter, int updated_location, INT_TYPE new_intProfit, vector<int> stage){
    ScaleLengthState origin_state = {scale_length_list_next[updated_location],scale_length_list_next[updated_location+1]};
    int state_index = spsp_next.lengthState_map_location[origin_state];
    int state_number=spsp_next.profit_set.size();
    INT_TYPE origin_profit = spsp_next.profit_set[state_index];


//    INT_TYPE new_intProfit;
//    new_intProfit = spsp_prev.profit_set[prev_iter] + ip.included_item_number*instance.item_set[ip.included_item].scale_profit;

    if(origin_profit<new_intProfit){
        spsp_next.profit_set[state_index] = new_intProfit;

        ScaleLengthState origin_state_prev = {scale_length_list_prev[prev_iter],scale_length_list_prev[prev_iter+1]};
        int state_index_prev = spsp_prev.lengthState_map_location[origin_state_prev];
        vector<ItemPattern> ip_list = spsp_prev.cp_set[state_index_prev].ip_list;
        ip_list.push_back(ip);

        INT_TYPE length_temp = 0;
        for(unsigned int i=1;i<ip_list.size();i++){
            length_temp+=ip_list[i].included_item_number*instance.item_set[ip_list[i].included_item].scale_length;
        }
        if(length_temp != spsp_next.cp_set[state_index].length){
            int mm = spsp_next.cp_set.size();
            int nn = spsp_next.profit_set.size();
            cout<<"stop here"<<endl;

        }


        ScaleCuttingPattern cp = {0,new_intProfit,spsp_next.cp_set[state_index].length,ip_list,stage};
        spsp_next.cp_set[state_index]=cp;

    }

}


void FPDP::ReplaceGMPscalePatternState(Instance instance, ItemPattern ip, int prev_iter, int updated_location, GMPint new_intProfit, vector<int> stage){
    GMPscaleLengthState origin_state = {gs_length_list_next[updated_location],gs_length_list_next[updated_location+1]};
    int state_index = gspsp_next.lengthState_map_location[origin_state];
    int state_number=gspsp_next.profit_set.size();
    GMPint origin_profit = gspsp_next.profit_set[state_index];


//    INT_TYPE new_intProfit;
//    new_intProfit = spsp_prev.profit_set[prev_iter] + ip.included_item_number*instance.item_set[ip.included_item].scale_profit;

    if(origin_profit<new_intProfit){
        gspsp_next.profit_set[state_index] = new_intProfit;

        GMPscaleLengthState origin_state_prev = {gs_length_list_prev[prev_iter],gs_length_list_prev[prev_iter+1]};
        int state_index_prev = gspsp_prev.lengthState_map_location[origin_state_prev];
        vector<ItemPattern> ip_list = gspsp_prev.cp_set[state_index_prev].ip_list;
        ip_list.push_back(ip);

//        INT_TYPE length_temp = 0;
//        for(unsigned int i=1;i<ip_list.size();i++){
//            length_temp+=ip_list[i].included_item_number*instance.item_set[ip_list[i].included_item].scale_length;
//        }
//        if(length_temp != spsp_next.cp_set[state_index].length){
//            int mm = spsp_next.cp_set.size();
//            int nn = spsp_next.profit_set.size();
//            cout<<"stop here"<<endl;
//
//        }


        GMPscaleCuttingPattern cp = {0,new_intProfit,gspsp_next.cp_set[state_index].length,ip_list,stage};
        gspsp_next.cp_set[state_index]=cp;

    }

}
void FPDP::ReplaceRationalPatternState(Instance instance, ItemPattern ip, int prev_iter, int updated_location, R_TYPE new_rProfit, vector<int> stage){
    RLengthState origin_state = {r_length_list_next[updated_location],r_length_list_next[updated_location+1]};
    int state_index = rpsp_next.lengthState_map_location[origin_state];
    int state_number=rpsp_next.profit_set.size();
    R_TYPE origin_profit = rpsp_next.profit_set[state_index];

    //R_TYPE new_rProfit = spsp_prev.profit_set[prev_iter] + ip.included_item_number*instance.item_set[ip.included_item].scale_profit;

    if(origin_profit<new_rProfit){
        rpsp_next.profit_set[state_index] = new_rProfit;

        RLengthState origin_state_prev = {r_length_list_prev[prev_iter],r_length_list_prev[prev_iter+1]};
        int state_index_prev = rpsp_prev.lengthState_map_location[origin_state_prev];
        vector<ItemPattern> ip_list = rpsp_prev.cp_set[state_index_prev].ip_list;
        ip_list.push_back(ip);

        RCuttingPattern cp = {0,new_rProfit,rpsp_next.cp_set[state_index].length,ip_list,stage};
        rpsp_next.cp_set[state_index]=cp;
    }

}



Result FPDP::GetMaximalPattern(){
    Result result;
    FPinterval max_profit = {0,0};
    int maximal_pattern_index=-1;
    int aa = psp_next.profit_set.size();
    for(unsigned int i=0;i<psp_next.profit_set.size();i++){
        if(max_profit.ub<psp_next.profit_set[i].lb){
            max_profit=psp_next.profit_set[i];
            maximal_pattern_index=i;
        }
    }
    result.cp=psp_next.cp_set[maximal_pattern_index];

    return result;
}

ScaleResult FPDP::GetMaximalScalePattern(){
    ScaleResult sr;
    INT_TYPE max_profit=0;
    int maximal_pattern_index=-1;
    int aa = spsp_next.profit_set.size();
    for(unsigned int i=0;i<spsp_next.profit_set.size();i++){
        if(max_profit<spsp_next.profit_set[i]){
            max_profit=spsp_next.profit_set[i];
            maximal_pattern_index=i;
        }
    }
    sr.cp=spsp_next.cp_set[maximal_pattern_index];

    return sr;
}

int FPDP::GetMaximalNumerExactPattern(int digit, ScaleResult& sr, Result& result){
    INT_TYPE scale_max_profit=0;
    int maximal_pattern_index=-1;
    int aa = spsp_next.profit_set.size();
    for(unsigned int i=0;i<spsp_next.profit_set.size();i++){
        if(scale_max_profit<spsp_next.profit_set[i]){
            scale_max_profit=spsp_next.profit_set[i];
            maximal_pattern_index=i;
        }
    }
    sr.cp=spsp_next.cp_set[maximal_pattern_index];

    if(psp_next.profit_set.size()>1){
        FPinterval fpi_max_profit;
        fesetround(FE_DOWNWARD);
        fpi_max_profit.lb=spsp_next.profit_set[maximal_pattern_index]/pow(10,digit);
        fesetround(FE_UPWARD);
        fpi_max_profit.ub=spsp_next.profit_set[maximal_pattern_index]/pow(10,digit);
        fesetround(FE_TONEAREST);
        bool flag = false;
        for(unsigned int i=0;i<psp_next.profit_set.size();i++){
            if(fpi_max_profit<psp_next.profit_set[i]){
                flag=true;
                fpi_max_profit=psp_next.profit_set[i];
                maximal_pattern_index=i;
            }
        }
        result.cp=psp_next.cp_set[maximal_pattern_index];
        if(flag==true){
            return 1;
        }
    }

    return 0;
}

GMPscaleResult FPDP::GetMaximalGMPscalePattern(){
    GMPscaleResult sr;
    GMPint max_profit;
    mpz_set_ui(max_profit.value,0);
    int maximal_pattern_index=-1;
    int aa = gspsp_next.profit_set.size();
    for(unsigned int i=0;i<gspsp_next.profit_set.size();i++){
        if(max_profit<gspsp_next.profit_set[i]){
            max_profit=gspsp_next.profit_set[i];
            maximal_pattern_index=i;
        }
    }
    sr.cp=gspsp_next.cp_set[maximal_pattern_index];

    return sr;
}

void FPDP::WriteFloatResults(string name, double computation_time, FloatResult sr){
    ofstream ofs;
    string file_path = "../result/r_"+name;
    ofs.open(file_path.c_str(),ios::out | ios::trunc);
    ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<sr.cp.profit<<endl;
    ofs<<endl<<"include items:"<<endl;
    for(unsigned int i=0;i<sr.cp.ip_list.size();i++){
        ofs<<sr.cp.ip_list[i].included_item<<"_"<<sr.cp.ip_list[i].included_item_number<<endl;
    }
    ofs.close();
}

void FPDP::WriteScaleResults(string file_path,double computation_time, ScaleResult sr){
    ofstream ofs;
    ofs.open(file_path.c_str(),ios::out | ios::trunc);
    ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<sr.cp.profit<<endl;
    ofs<<endl<<"include items:"<<endl;
    for(unsigned int i=0;i<sr.cp.ip_list.size();i++){
        ofs<<sr.cp.ip_list[i].included_item<<"_"<<sr.cp.ip_list[i].included_item_number<<endl;
    }
    ofs.close();
}

void FPDP::WriteNumerExactResults(string name, double computation_time, ScaleResult sr, Result result, int flag){
    ofstream ofs;
    string file_path = "../result/r_"+name;
    ofs.open(file_path.c_str(),ios::out | ios::trunc);
    if(flag==0){
        ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<sr.cp.profit<<endl;
        ofs<<endl<<"include items:"<<endl;
        for(unsigned int i=0;i<sr.cp.ip_list.size();i++){
            ofs<<sr.cp.ip_list[i].included_item<<"_"<<sr.cp.ip_list[i].included_item_number<<endl;
        }
    }
    else{
        ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<result.cp.profit.ub<<endl;
        ofs<<endl<<"include items:"<<endl;
        for(unsigned int i=0;i<result.cp.ip_list.size();i++){
            ofs<<result.cp.ip_list[i].included_item<<"_"<<result.cp.ip_list[i].included_item_number<<endl;
        }
    }

    ofs.close();
}

void FPDP::WriteGMPscaleResults(string name, double computation_time, GMPscaleResult sr){
    ofstream ofs;
    string file_path = "../result/scale_analysis/gmp_scale/r_"+name;
    ofs.open(file_path.c_str(),ios::out | ios::trunc);
    ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<sr.cp.profit.value<<endl;
    ofs<<endl<<"include items:"<<endl;
    for(unsigned int i=0;i<sr.cp.ip_list.size();i++){
        ofs<<sr.cp.ip_list[i].included_item<<"_"<<sr.cp.ip_list[i].included_item_number<<endl;
    }
    ofs.close();
}

void FPDP::WriteRationalResults(string name, double computation_time, RResult rr){
    ofstream ofs;
    string file_path = "../result/scale_analysis/rational/r_"+name;
    ofs.open(file_path.c_str(),ios::out | ios::trunc);
    ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<rr.cp.profit<<endl;
    ofs<<endl<<"include items:"<<endl;
    for(unsigned int i=0;i<rr.cp.ip_list.size();i++){
        ofs<<rr.cp.ip_list[i].included_item<<"_"<<rr.cp.ip_list[i].included_item_number<<endl;
    }
    ofs.close();
}

void FPDP::WriteIntervalResults(string name, double computation_time, Result result){
    ofstream ofs;
    string file_path = "../result/interval/r_"+name;
    ofs.open(file_path.c_str(),ios::out | ios::trunc);
    ofs<<"computation_time: "<<computation_time<<"\t"<<"total_benefit: "<<result.cp.profit.ub<<endl;
    ofs<<endl<<"include items:"<<endl;
    for(unsigned int i=0;i<result.cp.ip_list.size();i++){
        ofs<<result.cp.ip_list[i].included_item<<"_"<<result.cp.ip_list[i].included_item_number<<endl;
    }
    ofs.close();
}

FloatResult FPDP::GetMaximalFloatPattern(){
    FloatResult fr;
    INT_TYPE max_profit = 0;
    int maximal_pattern_index=-1;
    int aa = fpsp_next.profit_set.size();
    for(unsigned int i=0;i<fpsp_next.profit_set.size();i++){
        if(max_profit<fpsp_next.profit_set[i]){
            max_profit=fpsp_next.profit_set[i];
            maximal_pattern_index=i;
        }
    }
    fr.cp=fpsp_next.cp_set[maximal_pattern_index];

    return fr;
}

RResult FPDP::GetMaximalRationalPattern(){
    RResult rr;
    R_TYPE max_profit = 0;
    int maximal_pattern_index=-1;
    int aa = rpsp_next.profit_set.size();
    for(unsigned int i=0;i<rpsp_next.profit_set.size();i++){
        if(max_profit<rpsp_next.profit_set[i]){
            max_profit=rpsp_next.profit_set[i];
            maximal_pattern_index=i;
        }
    }
    rr.cp=rpsp_next.cp_set[maximal_pattern_index];

    return rr;
}


int FPDP::GetDecimalDigit(FPinterval fpi, int& scale_factor){
    int decimal_digit=0;
    if(fpi.lb==fpi.ub){
        //This situation shows that all rational numbers in the knapsack problem can be represented exactly by floating-point number.
        scale_factor=0;
        for(int a=0;a<1000;a++){
            //
            double value=fpi.lb*pow(10,a);
            double integer_part;
            double fraction =modf(value,&integer_part);
            if(fraction==0){
                for(int b=0;b<1000;b++){
                    if(value/pow(10,b)<=1){
                        decimal_digit=b;
                        return decimal_digit;
                    }
                }
            }
        }
    }
    else{
        for(int a=0;a<1000;a++){
            double value1 = ceil(fpi.lb*pow(10,a));
            double value2 = floor(fpi.ub*pow(10,a));
            if(value1==value2){
                scale_factor=a;
                for(int b=0;b<1000;b++){
                    if(value1/pow(10,b)<=1){
                        decimal_digit=b;
                        return decimal_digit;
                    }
                }
            }
        }
    }
    return decimal_digit;
}


void FPDP::GetMaxDecimalDigit(vector<FPinterval> fp_intervals){
    max_decimal_digit=0;
    int scale_factor=0;
    max_scale_factor = 0;
    for(unsigned int i=0;i<fp_intervals.size();i++){
        //Get the decimal digit of each rational number.
        //The maximal decimal digit among the decimal digits of these rational numbers is set as the decimal digit of the knapsack problem
        int decimal_digit = GetDecimalDigit(fp_intervals[i],scale_factor);
        if(max_scale_factor<scale_factor){
            max_scale_factor=scale_factor;
        }
        if(max_decimal_digit<decimal_digit){
            max_decimal_digit=decimal_digit;
        }
    }
}

void FPDP::GetMaxDecimalDigit(Instance instance){
    max_decimal_digit = instance.digit;
    max_scale_factor = instance.digit;
}

void FPDP::GetFPdecimalDigit(Instance instance) {
    fp_type_name = typeid(instance.stock_length_interval.lb).name();
    if(fp_type_name=="f") {
        fp_decimal_digit = 6;
    }
    else if(fp_type_name=="d"){
        fp_decimal_digit = 15;
    }
    else if(fp_type_name=="e"){
        fp_decimal_digit = 18;
    }

}
int FPDP::GlobalCheckIntervalAssumption(Instance instance) {
    GetFPdecimalDigit(instance);
    //calculate the maximal possible stages during recursion
    int max_stages = 0;
    FP_TYPE total_length=0;
    for(unsigned int i=instance.items_number-1;i>=0;i--){
        total_length+=instance.item_set[i].length;
        if(total_length>instance.stock_length){
            max_stages=i-1;
            break;
        }
    }

    if((fp_decimal_digit-max_decimal_digit)>(log10(max_stages+(max_stages-1)+2))){
        return 3;
    }
    else if((fp_decimal_digit-max_decimal_digit)>log10(3)){
        return 4;
    }
    else{
        return -1;
    }
}

bool FPDP::StageCheckIntervalAssumption(int max_decimal_digit, int fp_decimal_digit, int iter_step1, int iter_step2){
    return ((fp_decimal_digit-max_decimal_digit)>log10(iter_step1+iter_step2+2));
}

void FPDP::GetScaleRange(int scale_factor){
    integer_scale_range = 0;
    if(fp_type_name=="f"){
        max_integer_over_fp=16777216;
        integer_scale_range = floor(max_integer_over_fp/pow(10,scale_factor));
    }
    else if(fp_type_name=="d"){
        max_integer_over_fp= 9007199254740992;
        integer_scale_range = floor(max_integer_over_fp/pow(10,scale_factor));
    }

}

int FPDP::GlobalCheckScaleAssumption(Instance instance, int scale_factor){
    GetScaleRange(scale_factor);

    //Get the maximal profit of single item. If it is less than the integer_scale_range, this means that we can use scaling way at least once during fp
    FP_TYPE max_single_profit = 0;
    for(int i=0;i<instance.items_number;i++){
        if(instance.item_set[i].profit_interval.ub > max_single_profit){
            max_single_profit = instance.item_set[i].profit_interval.ub;
        }
    }

    //Get the upper bound of the all profits. If it is less than the integer_scale_range, we can solve the problem by just scaling way
    Instance instance_temp = instance;
    sort(instance_temp.item_set.begin(),instance_temp.item_set.end(),CompUnitProf);
    FP_TYPE max_profits=0;
    FPinterval length_interval={0,0};
    fesetround(FE_DOWNWARD);

    for(unsigned int i=0;i<instance_temp.item_set.size();i++){
        length_interval.lb+=instance_temp.item_set[i].demand*instance_temp.item_set[i].length_interval.lb;
        if(length_interval.lb<=instance_temp.stock_length_interval.ub){
            max_profits+=instance_temp.item_set[i].demand*instance_temp.item_set[i].profit_interval.ub;
        }
        else{
            length_interval.lb-=instance_temp.item_set[i].demand*instance_temp.item_set[i].length_interval.lb;
            FP_TYPE numb = (instance_temp.stock_length_interval.ub-length_interval.lb)/instance_temp.item_set[i].length_interval.lb;
            max_profits += numb*instance_temp.item_set[i].profit_interval.ub;
            break;
        }
    }
    fesetround(FE_TONEAREST);
    if((instance.stock_length_interval.ub<=integer_scale_range && max_profits <= integer_scale_range)){
        return 1;
    }
    else if(max_single_profit<=integer_scale_range){
        return 2;
    }
    else {
        return -1;
    }
}


bool FPDP::StageCheckScaleAssumption(INT_TYPE number1, INT_TYPE number2){
    if(number1>max_integer_over_fp || number2>max_integer_over_fp){
        return false;
    }
    return true;
}


Instance FPDP::ScaleData(Instance instance, int scale_factor){
    Instance scale_instance=instance;
    scale_instance.scale_stock_length = ceil(instance.stock_length_interval.lb*pow(10,scale_factor));
    for(int i=0;i<instance.items_number;i++){
        scale_instance.item_set[i].scale_length=ceil(instance.item_set[i].length_interval.lb*pow(10,scale_factor));
        scale_instance.item_set[i].scale_profit=ceil(instance.item_set[i].profit_interval.lb*pow(10,scale_factor));
    }

    return scale_instance;
}

Instance FPDP::GMPscaleData(Instance instance, int scale_factor){
    Instance scale_instance=instance;

    mpf_t numb_temp;
    mpf_init(numb_temp);
    mpf_mul_ui(numb_temp,instance.gmp_stock_length_interval.lb,pow(10,scale_factor));
    mpf_ceil(numb_temp,numb_temp);
    mpz_set_f(scale_instance.gmp_scale_stock_length.value,numb_temp);
    for(int i=0;i<instance.items_number;i++){
        mpf_mul_ui(numb_temp,instance.item_set[i].gmp_length_interval.lb,pow(10,scale_factor));
        mpf_ceil(numb_temp,numb_temp);
        mpz_set_f(scale_instance.item_set[i].gmp_scale_length.value,numb_temp);

        mpf_mul_ui(numb_temp,instance.item_set[i].gmp_profit_interval.lb,pow(10,scale_factor));
        mpf_ceil(numb_temp,numb_temp);
        mpz_set_f(scale_instance.item_set[i].gmp_scale_profit.value,numb_temp);

    }

    return scale_instance;
}

void FPDP::UpdateFloatPatternState(Instance instance, ItemPattern ip, int prev_iter, FP_TYPE new_fpiLength, FP_TYPE new_fpiProfit){
    string quried_result_next = QueryEpsilonFloatLength(new_fpiLength,f_length_list_next);
    int updated_location=-1;
    bool insert= ParseQuerInfo(quried_result_next,updated_location);
    if(insert==true){
        AddFloatPatternState(instance,ip, prev_iter, new_fpiLength, new_fpiProfit, updated_location, {ip.included_item+1,ip.included_item_number});
        f_length_list_next.push_back(new_fpiLength);
    }
    else{
        ReplaceFloatPatternState(instance, ip, prev_iter, new_fpiProfit,updated_location,{ip.included_item+1,ip.included_item_number});
    }
}

void FPDP::UpdatePatternState(Instance instance, ItemPattern ip, int prev_iter, FPinterval new_fpiLength, FPinterval new_fpiProfit){
    string quried_result_next = QueryLengthFPi(new_fpiLength,fpiLength_list_next);
    int updated_location=-1;
    bool insert= ParseQuerInfo(quried_result_next,updated_location);
    if(insert == true){
        AddPatternState(instance,ip, prev_iter, new_fpiLength, new_fpiProfit, updated_location, {ip.included_item+1,ip.included_item_number});
        fpiLength_list_next.push_back(new_fpiLength);
    }
    else{
        ReplacePatternState(instance, ip, prev_iter, new_fpiProfit,updated_location,{ip.included_item+1,ip.included_item_number});
    }
//    int updated_location=-1;
//    bool insert= ParseQuerInfo(quried_result_next,updated_location);
//    if(insert==true){
//        //AddPatternState(instance,ip, prev_iter, new_fpiLength, new_fpiProfit, updated_location, {ip.included_item+1,ip.included_item_number});
//        fpiLength_list_next.insert(fpiLength_list_next.begin()+updated_location,new_fpiLength);
//    }
//    else{
//        //ReplacePatternState(instance, ip, prev_iter, new_fpiProfit,updated_location,{ip.included_item+1,ip.included_item_number});
//    }
}

void FPDP::UpdateScalePatternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit){
    string quried_result_next = QueryScaleLength(new_intLength,scale_length_list_next);
    int updated_location=-1;
    bool insert= ParseQuerInfo(quried_result_next,updated_location);
    if(insert==true){
        AddScalePatternState(instance,ip, prev_iter, new_intLength,new_intProfit, updated_location, {ip.included_item+1,ip.included_item_number});
        scale_length_list_next.insert(scale_length_list_next.begin()+updated_location,new_intLength);
    }
    else{
        ReplaceScalePatternState(instance, ip,prev_iter,updated_location,new_intProfit,{ip.included_item+1,ip.included_item_number});
    }
}

void FPDP::UpdateNEpatternState(Instance instance, ItemPattern ip, int prev_iter, INT_TYPE new_intLength, INT_TYPE new_intProfit,
                                FPinterval new_fpiLength, FPinterval new_fpiProfit){
    string quried_result_next = QueryScaleLength(new_intLength,scale_length_list_next);
    int updated_location=-1;
    bool insert= ParseQuerInfo(quried_result_next,updated_location);
    if(insert==true){
        AddNEptternState(instance,ip, prev_iter, new_intLength,new_intProfit, new_fpiLength, new_fpiProfit,updated_location, {ip.included_item+1,ip.included_item_number});
        scale_length_list_next.insert(scale_length_list_next.begin()+updated_location,new_intLength);
        fpiLength_list_next.insert(fpiLength_list_next.begin()+updated_location,new_fpiLength);
    }
    else{
        ReplaceScalePatternState(instance, ip,prev_iter,updated_location,new_intProfit,{ip.included_item+1,ip.included_item_number});
    }
}

void FPDP::UpdateGMPscalePatternState(Instance instance, ItemPattern ip, int prev_iter, GMPint new_intLength, GMPint new_intProfit){
    string quried_result_next = QueryGMPscaleLength(new_intLength,gs_length_list_next);
    int updated_location=-1;
    bool insert= ParseQuerInfo(quried_result_next,updated_location);
    if(insert==true){
        AddGMPscalePatternState(instance,ip, prev_iter, new_intLength,new_intProfit, updated_location, {ip.included_item+1,ip.included_item_number});
        gs_length_list_next.insert(gs_length_list_next.begin()+updated_location,new_intLength);
        //add the index of the new pattern state to the unfinished index set
//        for(unsigned int i=0;i<unfinished_index_set_next.size();i++){
//            if(unfinished_index_set_next[i]>=updated_location){
//                unfinished_index_set_next[i]+=1;
//            }
//        }
//        if(!CheckFinishedScalePattern(instance,new_intLength)){
//            unfinished_index_set_next.push_back(updated_location);
//        }
    }
    else{
        ReplaceGMPscalePatternState(instance, ip,prev_iter,updated_location,new_intProfit,{ip.included_item+1,ip.included_item_number});
//        if(CheckFinishedScalePattern(instance,new_intLength)){
//            remove(unfinished_index_set_next.begin(),unfinished_index_set_next.end(),updated_location);
//        }
//        else if((find(unfinished_index_set_next.begin(),unfinished_index_set_next.end(),updated_location)!=unfinished_index_set_next.end())
//        && (!CheckFinishedScalePattern(instance,new_intLength))){
//            unfinished_index_set_next.push_back(updated_location);
//        }
    }
}

void FPDP::UpdateRationalPatternState(Instance instance, ItemPattern ip, int prev_iter, R_TYPE new_rLength, R_TYPE new_rProfit){
    string quried_result = QueryRLength(new_rLength,r_length_list_next);
    int updated_location=-1;
    bool insert= ParseQuerInfo(quried_result,updated_location);
    if(insert==true){
        AddRationalPatternState(instance,ip, prev_iter, new_rLength, new_rProfit,updated_location, {ip.included_item+1,ip.included_item_number});
        r_length_list_next.insert(r_length_list_next.begin()+updated_location,new_rLength);
    }
    else{
        ReplaceRationalPatternState(instance, ip,prev_iter,updated_location,new_rProfit, {ip.included_item+1,ip.included_item_number});
    }
}


void FPDP::TransformScaleToInterval(){
//    FPinterval fpiValue;
//    CuttingPattern cp;
//    LengthState ls;
//
//    fesetround(FE_UPWARD);
//    for(unsigned int i=0;i<spsp_next.profit_set.size();i++){
//        fpiValue.ub=spsp_next.profit_set[i]/pow(10,max_scale_factor);
//        psp_next.profit_set.push_back(fpiValue);
//    }
//    for(unsigned int i=0;i<spsp_next.cp_set.size();i++){
//        cp.profit.ub = spsp_next.cp_set[i].profit/pow(10,max_scale_factor);
//        cp.length.ub = spsp_next.cp_set[i].length/pow(10,max_scale_factor);
//        cp.ip_list=spsp_next.cp_set[i].ip_list;
//        cp.stage=spsp_next.cp_set[i].stage;
//        psp_next.cp_set.push_back(cp);
//    }
//    for(unsigned int i=0;i<spsp_next.length_state_set.size();i++){
//        ls.length_ub.ub=spsp_next.length_state_set[i].length_ub/pow(10,max_scale_factor);
//        ls.length_lb.ub=spsp_next.length_state_set[i].length_lb/pow(10,max_scale_factor);
//        psp_next.length_state_set.push_back(ls);
//    }
//
//    fesetround(FE_DOWNWARD);
//    for(unsigned int i=0;i<spsp_next.profit_set.size();i++){
//        psp_next.profit_set[i].lb=spsp_next.profit_set[i]/pow(10,max_scale_factor);
//    }
//    for(unsigned int i=0;i<spsp_next.cp_set.size();i++){
//        psp_next.cp_set[i].profit.lb = spsp_next.cp_set[i].profit/pow(10,max_scale_factor);
//        psp_next.cp_set[i].length.lb = spsp_next.cp_set[i].length/pow(10,max_scale_factor);
//
//    }
//    for(unsigned int i=0;i<spsp_next.length_state_set.size();i++){
//        psp_next.length_state_set[i].length_ub.lb=spsp_next.length_state_set[i].length_ub/pow(10,max_scale_factor);
//        psp_next.length_state_set[i].length_lb.lb=spsp_next.length_state_set[i].length_lb/pow(10,max_scale_factor);
//    }
//
//    for(map<ScaleLengthState,int>::iterator iter =spsp_next.lengthState_map_location.begin(); iter!=spsp_next.lengthState_map_location.end();++iter){
//        fesetround(FE_UPWARD);
//        ls.length_lb.ub = iter->first.length_lb/pow(10,max_scale_factor);
//        ls.length_ub.ub = iter->first.length_ub/pow(10,max_scale_factor);
//        fesetround(FE_DOWNWARD);
//        ls.length_lb.lb = iter->first.length_lb/pow(10,max_scale_factor);
//        ls.length_ub.lb = iter->first.length_ub/pow(10,max_scale_factor);
//
//        psp_next.lengthState_map_location.insert(pair<LengthState,int>(ls,iter->second));
//    }
//
//    //transform spsp_prev to psp_prev
//    fesetround(FE_UPWARD);
//    for(unsigned int i=0;i<spsp_prev.profit_set.size();i++){
//        fpiValue.ub=spsp_prev.profit_set[i]/pow(10,max_scale_factor);
//        psp_prev.profit_set.push_back(fpiValue);
//    }
//    for(unsigned int i=0;i<spsp_prev.cp_set.size();i++){
//        cp.profit.ub = spsp_prev.cp_set[i].profit/pow(10,max_scale_factor);
//        cp.length.ub = spsp_prev.cp_set[i].length/pow(10,max_scale_factor);
//        cp.ip_list=spsp_prev.cp_set[i].ip_list;
//        cp.stage=spsp_prev.cp_set[i].stage;
//        psp_prev.cp_set.push_back(cp);
//    }
//    for(unsigned int i=0;i<spsp_prev.length_state_set.size();i++){
//        ls.length_ub.ub=spsp_prev.length_state_set[i].length_ub/pow(10,max_scale_factor);
//        ls.length_lb.ub=spsp_prev.length_state_set[i].length_lb/pow(10,max_scale_factor);
//        psp_prev.length_state_set.push_back(ls);
//    }
//
//    fesetround(FE_DOWNWARD);
//    for(unsigned int i=0;i<spsp_prev.profit_set.size();i++){
//        psp_prev.profit_set[i].lb=spsp_prev.profit_set[i]/pow(10,max_scale_factor);
//    }
//    for(unsigned int i=0;i<spsp_prev.cp_set.size();i++){
//        psp_prev.cp_set[i].profit.lb = spsp_prev.cp_set[i].profit/pow(10,max_scale_factor);
//        psp_prev.cp_set[i].length.lb = spsp_prev.cp_set[i].length/pow(10,max_scale_factor);
//
//    }
//    for(unsigned int i=0;i<spsp_prev.length_state_set.size();i++){
//        psp_prev.length_state_set[i].length_ub.lb=spsp_prev.length_state_set[i].length_ub/pow(10,max_scale_factor);
//        psp_prev.length_state_set[i].length_lb.lb=spsp_prev.length_state_set[i].length_lb/pow(10,max_scale_factor);
//    }
//
//    for(map<ScaleLengthState,int>::iterator iter =spsp_prev.lengthState_map_location.begin(); iter!=spsp_prev.lengthState_map_location.end();++iter){
//        fesetround(FE_UPWARD);
//        ls.length_lb.ub = iter->first.length_lb/pow(10,max_scale_factor);
//        ls.length_ub.ub = iter->first.length_ub/pow(10,max_scale_factor);
//        fesetround(FE_DOWNWARD);
//        ls.length_lb.lb = iter->first.length_lb/pow(10,max_scale_factor);
//        ls.length_ub.lb = iter->first.length_ub/pow(10,max_scale_factor);
//
//        psp_prev.lengthState_map_location.insert(pair<LengthState,int>(ls,iter->second));
//    }
//
//    //transform scale_length_list_next into fpiLength_list_next
//    fesetround(FE_UPWARD);
//    for(unsigned int i=0;i<scale_length_list_next.size();i++){
//        fpiValue.ub=scale_length_list_next[i]/pow(10,max_scale_factor);
//        fpiLength_list_next.push_back(fpiValue);
//    }
//    for(unsigned int i=0;i<scale_length_list_prev.size();i++){
//        fpiValue.ub=scale_length_list_prev[i]/pow(10,max_scale_factor);
//        fpiLength_list_prev.push_back(fpiValue);
//    }
//    fesetround(FE_DOWNWARD);
//    for(unsigned int i=0;i<scale_length_list_next.size();i++){
//        fpiLength_list_next[i].lb=scale_length_list_next[i]/pow(10,max_scale_factor);
//    }
//    for(unsigned int i=0;i<scale_length_list_prev.size();i++){
//        fpiLength_list_prev[i].lb=scale_length_list_prev[i]/pow(10,max_scale_factor);
//    }
//    fesetround(FE_TONEAREST);
}

int FPDP::DPScalingMethod(Instance instance, ScaleResult sr){
    //initialize the sets
    try {
        spsp_prev = InitialScalePatternStatePool(instance);
        scale_length_list_prev = InitialScalePatternLengthList(instance);
        // unfinished_index_set_prev.push_back(0);
        //initialize the sets for the next stage
        spsp_next = spsp_prev;
        scale_length_list_next = scale_length_list_prev;
        int aaa = spsp_next.cp_set.size();

        auto start_time = std::chrono::system_clock::now();

        //unfinished_index_set_next=unfinished_index_set_prev;
        //try item types one by one
        for (int j = 0; j < instance.items_number; j++) {
            //generate new states based on existing states
            aaa = scale_length_list_prev.size();
            for (unsigned int b = 0; b < scale_length_list_prev.size() - 1; b++) {
                //try possible numbers pf used items
                int he = 0;
                for (int a = 1; a <= instance.item_set[j].demand; a++) {
                    cout<<j<<" | " <<instance.items_number<<", "<< b << " | "<<aaa<<", "<< a <<endl;
                    INT_TYPE new_intLength = scale_length_list_prev[b] + a * instance.item_set[j].scale_length;
                    if (new_intLength > instance.scale_stock_length) {
                        break;
                    }
                    INT_TYPE new_intProfit = spsp_prev.profit_set[b] + a * instance.item_set[j].scale_profit;
                    UpdateScalePatternState(instance, {j, a}, b, new_intLength, new_intProfit);

                }
            }
            spsp_prev = spsp_next;
            scale_length_list_prev = scale_length_list_next;
            // unfinished_index_set_prev=unfinished_index_set_next;
        }
        auto end_time = std::chrono::system_clock::now();


        std::chrono::duration<double> computation_time = end_time-start_time;
        sr = GetMaximalScalePattern();
        string folder_path = "../result/dataset1/"+instance.instance_name+".txt";
        WriteScaleResults(instance.instance_name,computation_time.count(),sr);
    }
    catch (const std::exception &exc){
        std::cerr<<exc.what();
    }
    if(sr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}

int FPDP::DPnumerExactMethod(Instance instance, ScaleResult sr, Result result){
    auto start_time = std::chrono::system_clock::now();
    vector<vector<long int>> overflow_list;
    //initialize the sets
    spsp_prev= InitialScalePatternStatePool(instance);
    scale_length_list_prev= InitialScalePatternLengthList(instance);
    // unfinished_index_set_prev.push_back(0);
    //initialize the sets for the next stage
    spsp_next = spsp_prev;
    scale_length_list_next=scale_length_list_prev;
    int aaa = spsp_next.cp_set.size();


    //unfinished_index_set_next=unfinished_index_set_prev;
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        //generate new states based on existing states
        for(unsigned int b =0;b<scale_length_list_prev.size()-1;b++){
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                INT_TYPE added_length = a*instance.item_set[j].scale_length;
                if(LONG_MAX - added_length>scale_length_list_prev[b]){
                    INT_TYPE new_intLength = scale_length_list_prev[b]+a*instance.item_set[j].scale_length;
                    if(new_intLength>instance.scale_stock_length){
                        break;
                    }
                    INT_TYPE new_intProfit = spsp_prev.profit_set[b] + a*instance.item_set[j].scale_profit;
                    UpdateScalePatternState(instance,{j,a},b,new_intLength,new_intProfit);
                }
                else{
                    overflow_list.push_back({scale_length_list_prev[b],j,a});
                    break;
                }
            }
        }
        spsp_prev = spsp_next;
        scale_length_list_prev=scale_length_list_next;
    }

    psp_prev= InitialPatternStatePool(instance);
    fpiLength_list_prev= InitialPatternLengthList(instance);
    psp_next = psp_prev;
    fpiLength_list_next=fpiLength_list_prev;
    for(unsigned int i=0;i<overflow_list.size();i++){
        INT_TYPE intLength_temp =overflow_list[i][0];
        FPinterval fpiLength_temp;
        fesetround(FE_DOWNWARD);
        fpiLength_temp.lb=intLength_temp/pow(10,instance.digit);
        fesetround(FE_UPWARD);
        fpiLength_temp.ub = intLength_temp/pow(10,instance.digit);
        fesetround(FE_TONEAREST);
        int j = overflow_list[i][1];
        for(int a=overflow_list[i][2];a<=instance.item_set[j].demand;a++){
            FPinterval new_fpiLength;
            fesetround(FE_DOWNWARD);
            new_fpiLength.lb=fpiLength_temp.lb+a*instance.item_set[overflow_list[i][1]].length_interval.lb;
            fesetround(FE_UPWARD);
            new_fpiLength.ub=fpiLength_temp.ub+a*instance.item_set[overflow_list[i][1]].length_interval.ub;
            fesetround(FE_TONEAREST);
            if(new_fpiLength>instance.stock_length_interval){
                break;
            }
            //Search the profit corresponding to the weight
            int index = 0;
            vector<INT_TYPE>::iterator it = std::find(scale_length_list_next.begin(), scale_length_list_next.end(), intLength_temp);
            if(it !=scale_length_list_next.end()){
                index = distance(scale_length_list_next.begin(),it);
            }
            ScaleLengthState origin_state = {scale_length_list_next[index],scale_length_list_next[index+1]};
            int state_index = spsp_next.lengthState_map_location[origin_state];
            INT_TYPE intProfit_temp = spsp_next.profit_set[state_index];

            FPinterval new_fpiProfit;
            fesetround(FE_DOWNWARD);
            new_fpiProfit.lb = intProfit_temp/pow(10,instance.digit) + a*instance.item_set[overflow_list[i][1]].profit_interval.lb;
            fesetround(FE_UPWARD);
            new_fpiProfit.ub=intProfit_temp/pow(10,instance.digit) + a*instance.item_set[overflow_list[i][1]].profit_interval.ub;
            fesetround(FE_TONEAREST);
            UpdatePatternState(instance, {j,a}, 0, new_fpiLength, new_fpiProfit);

        }

        for(int k=j+1;j<instance.items_number;j++){
            for(unsigned int b =1;b<fpiLength_list_prev.size();b++){
                //try possible numbers pf used items
                for(int a=1;a<=instance.item_set[k].demand;a++){
                    FPinterval new_fpiLength;
                    fesetround(FE_DOWNWARD);
                    new_fpiLength.lb=fpiLength_list_prev[b].lb+a*instance.item_set[k].length_interval.lb;
                    fesetround(FE_UPWARD);
                    new_fpiLength.ub=fpiLength_list_prev[b].ub+a*instance.item_set[k].length_interval.ub;
                    fesetround(FE_TONEAREST);
                    if(new_fpiLength>instance.stock_length_interval){
                        break;
                    }
                    FPinterval new_fpiProfit;
                    fesetround(FE_DOWNWARD);
                    new_fpiProfit.lb = psp_prev.profit_set[b].lb + a*instance.item_set[k].profit_interval.lb;
                    fesetround(FE_UPWARD);
                    new_fpiProfit.ub=psp_prev.profit_set[b].ub+a*instance.item_set[k].profit_interval.ub;
                    fesetround(FE_TONEAREST);
                    UpdatePatternState(instance, {k,a}, b, new_fpiLength, new_fpiProfit);
                }
            }
            psp_prev = psp_next;
            fpiLength_list_prev=fpiLength_list_next;
        }

    }
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> computation_time = end_time-start_time;
    int  flag = GetMaximalNumerExactPattern(instance.digit,sr,result);
    WriteNumerExactResults(instance.instance_name,computation_time.count(),sr,result,flag);
    if(sr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}


int FPDP::DPgmpScalingMethod(Instance instance, GMPscaleResult sr){
    //initialize the sets
    gspsp_prev= InitialGMPscalePatternStatePool(instance);
    gs_length_list_prev= InitialGMPscalePatternLengthList(instance);
    // unfinished_index_set_prev.push_back(0);
    //initialize the sets for the next stage
    gspsp_next = gspsp_prev;
    gs_length_list_next=gs_length_list_prev;
    int aaa = gspsp_next.cp_set.size();

    auto start_time = std::chrono::system_clock::now();

    //unfinished_index_set_next=unfinished_index_set_prev;
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        if(j==81){
            //cout<<"stop"<<endl;
        }
        aaa = gs_length_list_prev.size()-1;
        //generate new states based on existing states
        for(unsigned int b =0;b<gs_length_list_prev.size()-1;b++){
            if(b==0){
                //cout<<"stop"<<endl;
            }
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                GMPint new_intLength;
                mpz_mul_ui(new_intLength.value,instance.item_set[j].gmp_scale_length.value,a);
                mpz_add(new_intLength.value,new_intLength.value,gs_length_list_prev[b].value);
                //cout<<"new_intLength:"<<new_intLength.value<<" | " <<"stock_length:"<<instance.gmp_scale_stock_length.value<<endl;
                if(new_intLength>instance.gmp_scale_stock_length){
                    break;
                }
                GMPint new_intProfit;
                mpz_mul_ui(new_intProfit.value,instance.item_set[j].gmp_scale_profit.value,a);
                mpz_add(new_intProfit.value,new_intProfit.value,gspsp_prev.profit_set[b].value);
                UpdateGMPscalePatternState(instance,{j,a},b,new_intLength,new_intProfit);
            }
        }
        gspsp_prev = gspsp_next;
        gs_length_list_prev=gs_length_list_next;
        // unfinished_index_set_prev=unfinished_index_set_next;
    }
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> computation_time = end_time-start_time;
    sr = GetMaximalGMPscalePattern();
    WriteGMPscaleResults(instance.instance_name,computation_time.count(),sr);
    if(sr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}

int FPDP::DPfloatingMethod(Instance instance, FloatResult fr){
    auto start_time = std::chrono::system_clock::now();
    //initialize the set
    fpsp_prev= InitialFloatPatternStatePool(instance);
    f_length_list_prev= InitialFloatPatternLengthList(instance);
    // unfinished_index_set_prev.push_back(0);
    //initialize the sets for the next stage
    fpsp_next = fpsp_prev;
    f_length_list_next=f_length_list_prev;
    int aaa = fpsp_next.cp_set.size();

    //unfinished_index_set_next=unfinished_index_set_prev;
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        cout<<j<<"---"<<instance.items_number<<endl;
        //generate new states based on existing states
        for(unsigned int b =0;b<f_length_list_prev.size();b++){
            cout<<j<<"---"<<instance.items_number<<"---"<<b<<"---"<<f_length_list_prev.size()<<endl;
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                FP_TYPE new_intLength = f_length_list_prev[b]+a*instance.item_set[j].length;
                FP_TYPE new_intLength1 = f_length_list_prev[b]+a*instance.item_set[j].length;
                if(new_intLength>instance.stock_length){
                    break;
                }
                FP_TYPE new_intProfit = fpsp_prev.profit_set[b] + a*instance.item_set[j].profit;
                FP_TYPE new_intProfit1 = fpsp_prev.profit_set[b] + a*instance.item_set[j].profit;
                //if dp_flag == 1, we update the pattern states according to the scaling way
                UpdateFloatPatternState(instance,{j,a},b,new_intLength,new_intProfit);
            }
        }
        fpsp_prev = fpsp_next;
        f_length_list_prev=f_length_list_next;
        // unfinished_index_set_prev=unfinished_index_set_next;
    }
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> computation_time = end_time-start_time;
    fr = GetMaximalFloatPattern();
    WriteFloatResults(instance.instance_name,computation_time.count(),fr);
    if(fr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}

int FPDP::DPrationalMethod(Instance instance, RResult rr){
    auto start_time = std::chrono::system_clock::now();
    //initialize the sets
    rpsp_prev= InitialRationalPatternStatePool(instance);
    r_length_list_prev= InitialRationalPatternLengthList(instance);
    //initialize the sets for the next stage
    rpsp_next = rpsp_prev;
    r_length_list_next=r_length_list_prev;
    int aaa = rpsp_next.cp_set.size();
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        //generate new states based on existing states
        for(unsigned int b =0;b<r_length_list_prev.size()-1;b++){
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                R_TYPE new_rLength = r_length_list_prev[b]+a*instance.item_set[j].r_length;
                if(new_rLength>instance.r_stock_length){
                    break;
                }
                R_TYPE new_rProfit = rpsp_prev.profit_set[b] + a*instance.item_set[j].r_profit;
                UpdateRationalPatternState(instance,{j,a},b,new_rLength,new_rProfit);

            }
        }
        rpsp_prev = rpsp_next;
        r_length_list_prev=r_length_list_next;
    }

    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> computation_time = end_time-start_time;
    rr = GetMaximalRationalPattern();
    WriteRationalResults(instance.instance_name,computation_time.count(),rr);
    if(rr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}

int FPDP::DPrationalMethod2(Instance instance, RResult rr){
    //initialize the sets
    rpsp_prev= InitialRationalPatternStatePool(instance);
    r_length_list_prev= InitialRationalPatternLengthList(instance);
    //initialize the sets for the next stage
    rpsp_next = rpsp_prev;
    r_length_list_next=r_length_list_prev;
    int aaa = rpsp_next.cp_set.size();
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        //generate new states based on existing states
        for(unsigned int b =0;b<r_length_list_prev.size()-1;b++){
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                R_TYPE new_rLength = r_length_list_prev[b]+a*instance.item_set[j].r_length;
                if(new_rLength>instance.r_stock_length){
                    break;
                }
                R_TYPE new_rProfit = rpsp_prev.profit_set[b] + a*instance.item_set[j].r_profit;
                UpdateRationalPatternState(instance,{j,a},b,new_rLength,new_rProfit);
            }
        }
        rpsp_prev = rpsp_next;
        r_length_list_prev=r_length_list_next;
    }



    rr = GetMaximalRationalPattern();
    //WriteRationalResults(instance.instance_name,computation_time.count(),rr);
    if(rr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}

int FPDP::DPintervalMehod(Instance instance, Result& result){
    //initialize the sets
    psp_prev= InitialPatternStatePool(instance);
    fpiLength_list_prev= InitialPatternLengthList(instance);
    //initialize the sets for the next stage
    psp_next = psp_prev;
    fpiLength_list_next=fpiLength_list_prev;

    int fpiLength_list_prev_used_range = fpiLength_list_prev.size();
    FPinterval unfinished_pattern_length_range;
    unfinished_pattern_length_range.lb=instance.stock_length_interval.lb-instance.item_set[instance.item_set.size()-1].length_interval.ub;
    unfinished_pattern_length_range.ub = instance.stock_length_interval.ub-instance.item_set[instance.item_set.size()-1].length_interval.lb;
    auto start_time = std::chrono::system_clock::now();
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        //generate new states based on existing states
        for(unsigned int b =0;b<fpiLength_list_prev_used_range;b++){
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                FPinterval new_fpiLength;
                fesetround(FE_DOWNWARD);
                new_fpiLength.lb=fpiLength_list_prev[b].lb+a*instance.item_set[j].length_interval.lb;
                fesetround(FE_UPWARD);
                new_fpiLength.ub=fpiLength_list_prev[b].ub+a*instance.item_set[j].length_interval.ub;
                fesetround(FE_TONEAREST);
                if(new_fpiLength>instance.stock_length_interval){
                    break;
                }
                FPinterval new_fpiProfit;
                fesetround(FE_DOWNWARD);
                new_fpiProfit.lb = psp_prev.profit_set[b].lb + a*instance.item_set[j].profit_interval.lb;
                fesetround(FE_UPWARD);
                new_fpiProfit.ub=psp_prev.profit_set[b].ub+a*instance.item_set[j].profit_interval.ub;
                fesetround(FE_TONEAREST);
                UpdatePatternState(instance, {j,a}, b, new_fpiLength, new_fpiProfit);
            }
        }
        psp_prev = psp_next;
        fpiLength_list_prev=fpiLength_list_next;
        for(unsigned int i=fpiLength_list_prev.size()-1;i>=0;i--){
            if(fpiLength_list_prev[i]<unfinished_pattern_length_range || fpiLength_list_prev[i]==unfinished_pattern_length_range){
                fpiLength_list_prev_used_range = i;
                break;
            }
        }
    }
    int zz = fpiLength_list_next.size();
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> computation_time = end_time-start_time;
    result = GetMaximalPattern();
    WriteIntervalResults(instance.instance_name,computation_time.count(),result);
    if(result.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}


int FPDP::DPintervalMehod2(Instance instance, Result& result){
    vector<int> initial_stage = psp_next.cp_set[psp_next.cp_set.size()-1].stage;
    //try item types one by one
    for(int j=initial_stage[0];j<instance.items_number;j++){
        //try possible numbers pf used items
        for(int a=0;a<instance.item_set[j].demand;a++){
            if(a<=initial_stage[1]){
                continue;
            }
            //generate new states based on existing states
            for(unsigned int b =0;b<fpiLength_list_prev.size()-1;b++){
                if(b<=initial_stage[2]){
                    continue;
                }
                FPinterval new_fpiLength;
                fesetround(FE_DOWNWARD);
                new_fpiLength.lb=fpiLength_list_prev[b].lb+a*instance.item_set[j].length_interval.lb;
                fesetround(FE_UPWARD);
                new_fpiLength.ub=fpiLength_list_prev[b].ub+a*instance.item_set[j].length_interval.ub;
                fesetround(FE_TONEAREST);
                if(new_fpiLength>instance.stock_length_interval){
                    break;
                }
                FPinterval new_fpiProfit;
                fesetround(FE_DOWNWARD);
                new_fpiProfit.lb = psp_prev.profit_set[b].lb + a*instance.item_set[j].profit_interval.lb;
                fesetround(FE_UPWARD);
                new_fpiProfit.ub=psp_prev.profit_set[b].ub+a*instance.item_set[j].profit_interval.ub;
                fesetround(FE_TONEAREST);
                UpdatePatternState(instance, {j,a}, b, new_fpiLength, new_fpiProfit);
            }
        }

    }

    result = GetMaximalPattern();
    if(result.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}


int FPDP::DPepsilonMethod(Instance instance, FloatResult fr){
    auto start_time = std::chrono::system_clock::now();
    //initialize the set
    fpsp_prev= InitialFloatPatternStatePool(instance);
    f_length_list_prev= InitialFloatPatternLengthList(instance);
    // unfinished_index_set_prev.push_back(0);
    //initialize the sets for the next stage
    fpsp_next = fpsp_prev;
    f_length_list_next=f_length_list_prev;
    int aaa = fpsp_next.cp_set.size();

    //unfinished_index_set_next=unfinished_index_set_prev;
    //try item types one by one
    for(int j=0;j<instance.items_number;j++){
        cout<<j<<"---"<<instance.items_number<<endl;
        //generate new states based on existing states
        for(unsigned int b =0;b<f_length_list_prev.size();b++){
            cout<<j<<"---"<<instance.items_number<<"---"<<b<<"---"<<f_length_list_prev.size()<<endl;
            //try possible numbers pf used items
            for(int a=1;a<=instance.item_set[j].demand;a++){
                FP_TYPE new_intLength = f_length_list_prev[b]+a*instance.item_set[j].length;
                if(new_intLength-instance.stock_length>EPSILON){
                    break;
                }
                FP_TYPE new_intProfit = fpsp_prev.profit_set[b] + a*instance.item_set[j].profit;
                //if dp_flag == 1, we update the pattern states according to the scaling way
                UpdateFloatPatternState(instance,{j,a},b,new_intLength,new_intProfit);
            }
        }
        fpsp_prev = fpsp_next;
        f_length_list_prev=f_length_list_next;
        // unfinished_index_set_prev=unfinished_index_set_next;
    }
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> computation_time = end_time-start_time;
    fr = GetMaximalFloatPattern();
    WriteFloatResults(instance.instance_name,computation_time.count(),fr);
    if(fr.cp.ip_list.size()==0){
        return 0;
    }
    return 1;
}



int FPDP::DP(Instance instance){
    GetMaxDecimalDigit(instance);
    GetFPdecimalDigit(instance);
//    FloatResult fr;
//    DPfloatingMethod(instance,fr);
    //Result res;
    //DPintervalMehod(instance,res);
//    RResult rr;
//    DPrationalMethod(instance,rr);
//    GMPscaleResult sr;
//    Instance scale_instance = GMPscaleData(instance,max_scale_factor);
//    DPgmpScalingMethod(scale_instance,sr);
//    ScaleResult sr;
//    Instance scale_instance = ScaleData(instance,max_scale_factor);
//    DPScalingMethod(scale_instance,sr);

    ScaleResult sr;
    Result result;
    Instance scale_instance = ScaleData(instance,max_scale_factor);
    DPnumerExactMethod(scale_instance,sr, result);
    int cc=0;

    return 1;
}
