//
// Created by baiyanghe on 02/11/23.
//
#include "read_problem.h"

Item::Item(){
    mpf_init(gmp_length);
    mpf_init(gmp_profit);
    mpz_init(gmp_scale_length.value);
    mpz_init(gmp_scale_profit.value);
    mpq_init(gmp_r_length);
    mpq_init(gmp_r_profit);
    mpf_init(gmp_length_interval.lb);
    mpf_init(gmp_length_interval.ub);
    mpf_init(gmp_profit_interval.lb);
    mpf_init(gmp_profit_interval.ub);
}
Item::Item(const Item& other_item){
    this->index=other_item.index;
    this->length=other_item.length;
    this->length_interval=other_item.length_interval;
    this->scale_length=other_item.scale_length;
    this->r_length=other_item.r_length;
    this->demand=other_item.demand;
    this->profit_interval=other_item.profit_interval;
    this->scale_profit=other_item.scale_profit;
    this->r_profit=other_item.r_profit;
    this->unit_prof_interval=other_item.unit_prof_interval;
    this->profit=other_item.profit;

    mpf_init(this->gmp_length);
    mpf_init(this->gmp_profit);
    mpz_init(this->gmp_scale_length.value);
    mpz_init(this->gmp_scale_profit.value);
    mpq_init(this->gmp_r_length);
    mpq_init(this->gmp_r_profit);
    mpf_init(this->gmp_length_interval.lb);
    mpf_init(this->gmp_length_interval.ub);
    mpf_init(this->gmp_profit_interval.lb);
    mpf_init(this->gmp_profit_interval.ub);

    mpf_set(this->gmp_length,other_item.gmp_length);
    mpf_set(this->gmp_profit,other_item.gmp_profit);
    this->gmp_scale_length=other_item.gmp_scale_length;
    this->gmp_scale_profit=other_item.gmp_scale_profit;
    mpq_set(this->gmp_r_length,other_item.gmp_r_length);
    mpq_set(this->gmp_r_profit,other_item.gmp_r_profit);
    this->gmp_length_interval=other_item.gmp_length_interval;
    this->gmp_profit_interval=other_item.gmp_profit_interval;
}

bool CompLength(const Item& a, const Item& b){
    return a.length>b.length;
}

bool CompUnitProf(const Item& a, const Item& b){
    return a.unit_prof_interval.lb>b.unit_prof_interval.lb;
}

int scanFiles(vector<string> &fileList, string inputDirectory)
{
    inputDirectory = inputDirectory.append("/");

    DIR *p_dir=NULL;
    const char* str = inputDirectory.c_str();

    p_dir = opendir(str);
    if( p_dir == NULL)
    {
        cout<< "can't open :" << inputDirectory << endl;
    }

    struct dirent *p_dirent=NULL;

    while ( p_dirent == readdir(p_dir))
    {
        string tmpFileName = p_dirent->d_name;
        if( tmpFileName == "." || tmpFileName == "..")
        {
            continue;
        }
        else
        {
            fileList.push_back(tmpFileName);
        }
    }
    closedir(p_dir);
    return fileList.size();
}

int GetFiles(const string& path, vector<string> &files, vector<string> suffixs)
{
    int FileCnt = 0;
    DIR *dirp;
    struct dirent *dp;

    dirp = opendir(path.c_str());
    if (dirp == NULL) {
        printf("opendir %s failed\n",path.c_str());
        return 0;
    }

    while ((dp = readdir(dirp)) != NULL) {
        string curpath(path);
        if (path.back() != '/') {
            curpath += string("/") += dp->d_name;
        } else {
            curpath += dp->d_name;
        }
        //如果是目录，递归查找
        if(dp->d_type == DT_DIR) {
            if(0 != strcmp(dp->d_name,".") && 0 != strcmp(dp->d_name,"..")){
                FileCnt += GetFiles(curpath, files, suffixs);
            }
        }
            //判断是否为文件以及文件后缀名
        else if (dp->d_type == DT_REG) {
            if (suffixs.size() <=0 ) {
                files.push_back(curpath);
                FileCnt++;
            } else {
                for (auto suffix : suffixs) {
                    if (string(strrchr(dp->d_name,'.')) == suffix) {
                        files.push_back(curpath);
                        FileCnt++;
                        break;
                    }
                }
            }
        }
    }

    closedir(dirp);
    return FileCnt;
}

//
vector<string> split(string target_str, string split_symbol)
{
    string::size_type pos;
    vector<string> result;
    target_str += split_symbol;//扩展字符串以方便操作
    unsigned int size = target_str.size();
    for (unsigned i = 0; i < size; i++)
    {
        pos = target_str.find(split_symbol, i);
        if (pos < size)
        {
            string s = target_str.substr(i, pos - i);
            result.push_back(s);
            i = pos + split_symbol.size() - 1;
        }
    }
    return result;
}

void Stringsplit(string str, const char split,vector<string>& res)
{
    istringstream iss(str);	//
    string token;			//
    while (getline(iss, token, split))	//
    {
        res.push_back(token);
    }
}

vector<Instance> read_instance(const string path){
    vector<string> files_paths;
    GetFiles(path,files_paths,vector<string>());
    sort(files_paths.begin(),files_paths.end());
    vector<Instance> instance_set;

    char sep_symb = '\t';
    for (unsigned int i = 0; i < files_paths.size(); i++) {
        Instance instance;
        string file_path = files_paths[i];
        vector<string> str_temp;
        Stringsplit(file_path,'/',str_temp);
        instance.instance_name=str_temp[str_temp.size()-1];
        ifstream ifs;
        ifs.open(file_path, ios::in);
        if (!ifs.is_open()) {
            cout << "fail to open the file" << endl;
            continue;
        }

        string line;
        //if data_flag==1, then the next data is the number of items;
        //else if data_flag==2, then the next data is the number of stocks;
        //else if data_flag==3, then the next data are items;
        //else if data_flag==4, then the next data are stocks;
        //else data_flag==0, then the type of the next data is the same as the last one.
        int data_flag = 0;
        int digit = 0;
        while (getline(ifs, line)) {
            if (line == "items_number") {
                data_flag = 1;
                continue;
            }
            else if (line == "stocks_number") {
                data_flag = 2;
                continue;
            }
            else if(line == "digit"){
                data_flag = 3;
                continue;
            }
            else if (line == "items") {
                data_flag = 4;
                continue;
            }
            else if (line == "stocks") {
                data_flag = 5;
                continue;
            }

            vector<double> data_from_single_line;
            stringstream ssline(line);
            string splited_line;
            if (data_flag == 1) {
                sep_symb='\r';
                getline(ssline, splited_line, sep_symb);
                splited_line.erase(std::remove_if(splited_line.begin(), splited_line.end(), ::isspace), splited_line.end());
                instance.items_number = atoi(splited_line.c_str());
            }
            else if (data_flag == 2) {
                sep_symb='\r';
                getline(ssline, splited_line, sep_symb);
                splited_line.erase(std::remove_if(splited_line.begin(), splited_line.end(), ::isspace), splited_line.end());
                instance.stocks_number = atoi(splited_line.c_str());
            }
            else if(data_flag == 3){
                sep_symb='\r';
                getline(ssline, splited_line, sep_symb);
                splited_line.erase(std::remove_if(splited_line.begin(), splited_line.end(), ::isspace), splited_line.end());
                instance.digit = atoi(splited_line.c_str());
            }
            else if (data_flag == 4) {
                int count_data = 0;
                sep_symb='\t';
                Item item;
                vector<INT_TYPE> r_values;
//                mpq_t gmp_r_values[2];
//                mpq_init(gmp_r_values[0]);
//                mpq_init(gmp_r_values[1]);
                while (getline(ssline, splited_line, sep_symb)) {
                    if (count_data == 0) {
                        item.length = stod(splited_line.c_str());
                        fesetround(FE_DOWNWARD);
                        item.length_interval.lb = stod(splited_line.c_str());
                        fesetround(FE_UPWARD);
                        item.length_interval.ub = stod(splited_line.c_str());

//                        mpf_set_d(item.gmp_length,stod(splited_line.c_str()));
//                        fesetround(FE_DOWNWARD);
//                        mpf_set_d(item.gmp_length_interval.lb,stod(splited_line.c_str()));
//                        fesetround(FE_UPWARD);
//                        mpf_set_d(item.gmp_length_interval.ub,stod(splited_line.c_str()));
                        count_data++;
                    }
                    else if(count_data==1 || count_data==2){
                        r_values.push_back(atoi(splited_line.c_str()));
                        //mpq_set_ui(gmp_r_values[count_data-1],atoi(splited_line.c_str()),1);
                        count_data++;
                    }
                    else if(count_data==3){
                        r_values[0]=r_values[0]*pow(10,instance.digit)+r_values[1];
                        r_values[1]=pow(10,instance.digit);
                        item.r_length=R_TYPE(r_values[0],r_values[1]);
                        vector<INT_TYPE>().swap(r_values);

                        item.profit = stod(splited_line.c_str());
                        fesetround(FE_DOWNWARD);
                        item.profit_interval.lb = stod(splited_line.c_str());
                        fesetround(FE_UPWARD);
                        item.profit_interval.ub = stod(splited_line.c_str());
//                        mpq_t numb_temp;
//                        mpq_init(numb_temp);
//                        mpq_set_ui(numb_temp,pow(10,instance.digit),1);
//                        mpq_mul(gmp_r_values[0],gmp_r_values[0],numb_temp);
//                        mpq_add(gmp_r_values[0],gmp_r_values[0],gmp_r_values[1]);
//                        mpq_div(item.gmp_r_length,gmp_r_values[0],numb_temp);
//
//                        mpf_set_d(item.gmp_profit,stod(splited_line.c_str()));
//                        fesetround(FE_DOWNWARD);
//                        mpf_set_d(item.gmp_profit_interval.lb,stod(splited_line.c_str()));
//                        fesetround(FE_UPWARD);
//                        mpf_set_d(item.gmp_profit_interval.ub,stod(splited_line.c_str()));

                        count_data++;
                    }
                    else if(count_data ==4 || count_data==5){
                        r_values.push_back(atoi(splited_line.c_str()));
                        //mpq_set_ui(gmp_r_values[count_data-4],atoi(splited_line.c_str()),1);
                        count_data++;
                    }
                    else{
                        r_values[0]=r_values[0]*pow(10,instance.digit)+r_values[1];
                        r_values[1]=pow(10,instance.digit);
                        item.r_profit=R_TYPE(r_values[0],r_values[1]);
                        vector<INT_TYPE>().swap(r_values);

                        item.demand=atoi(splited_line.c_str());

//                        mpq_t numb_temp;
//                        mpq_init(numb_temp);
//                        mpq_set_ui(numb_temp,pow(10,instance.digit),1);
//                        mpq_mul(gmp_r_values[0],gmp_r_values[0],numb_temp);
//                        mpq_add(gmp_r_values[0],gmp_r_values[0],gmp_r_values[1]);
//                        mpq_div(item.gmp_r_profit,gmp_r_values[0],numb_temp);
//
//                        item.demand=atoi(splited_line.c_str());
                    }
                }
                //cout<<"item_length:"<<item.gmp_length<<" | "<<item.gmp_scale_length.value<<endl;
                instance.item_set.push_back(item);
            }
            else if (data_flag == 5) {
                int count_data = 0;
                sep_symb='\t';
                vector<INT_TYPE> r_values;
//                mpq_t gmp_r_values[2];
//                mpq_init(gmp_r_values[0]);
//                mpq_init(gmp_r_values[1]);
                while (getline(ssline, splited_line, sep_symb)) {
                    if (count_data == 0) {
                        instance.stock_length=stod(splited_line.c_str());
                        fesetround(FE_DOWNWARD);
                        instance.stock_length_interval.lb=stod(splited_line.c_str());
                        fesetround(FE_UPWARD);
                        instance.stock_length_interval.ub =stod(splited_line.c_str());
                        fesetround(FE_TONEAREST);
//                        mpf_set_d(instance.gmp_stock_length,stod(splited_line.c_str()));
//                        fesetround(FE_DOWNWARD);
//                        mpf_set_d(instance.gmp_stock_length_interval.lb,stod(splited_line.c_str()));
//                        fesetround(FE_UPWARD);
//                        mpf_set_d(instance.gmp_stock_length_interval.ub,stod(splited_line.c_str()));
                        count_data++;
                    }
                    else if(count_data==1 || count_data==2){
                        r_values.push_back(atoi(splited_line.c_str()));
                        //mpq_set_ui(gmp_r_values[count_data-1],atoi(splited_line.c_str()),1);
                        count_data++;
                    }
                    else{
                        r_values[0]=r_values[0]*pow(10,instance.digit)+r_values[1];
                        r_values[1]=pow(10,instance.digit);
                        instance.r_stock_length=R_TYPE(r_values[0],r_values[1]);
                        vector<INT_TYPE>().swap(r_values);
//                        mpq_t numb_temp;
//                        mpq_init(numb_temp);
//                        mpq_set_ui(numb_temp,pow(10,instance.digit),1);
//                        mpq_mul(gmp_r_values[0],gmp_r_values[0],numb_temp);
//                        mpq_add(gmp_r_values[0],gmp_r_values[0],gmp_r_values[1]);
//                        mpq_div(instance.gmp_r_stock_length,gmp_r_values[0],numb_temp);
                    }
                }
            }

        }
        ifs.close();

        sort(instance.item_set.begin(),instance.item_set.end(), CompLength);
        instance_set.push_back(instance);
    }

    return instance_set;
}

void RemoveDuplicate(vector<int>& vec){
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}


