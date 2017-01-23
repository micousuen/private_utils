/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on January 19, 2017, 7:20 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <chrono>
#define PUNC ' '

using namespace std;


template<typename iord>
class util {
public:
    util(std::string input){util::analysis(input);}
    ~util(){delete[] output_array;}
    
    // Sort the array
    void Sort(iord* output_a,int size){
        for(int i=0;i<size;i++)
            for(int j=i+1;j<size;j++){
                if(output_a[i] > output_a[j]){
                    iord temp;
                    temp=output_a[i];
                    output_a[i]=output_a[j];
                    output_a[j]=temp;
                }
            }
    }
    
    // Sort the array and group the array by its sign
    void signGroup(iord* output_a, int size){
        Sort(output_a,size);
        int pos_num=0,neg_num=0;
        for(int i=0;i<size;i++){
            if(output_a[i]>=0)
                ++pos_num;
            else
                ++neg_num;
        }
        for(int i=0;i<size;i++){
            if(output_a[i]>=0)
                pos_array.push_back(output_a[i]);
            else
                neg_array.push_back(output_a[i]);
        }
    }
    
    // The output vector
    std::vector<iord> output;
    iord* output_array;
    std::vector<iord> pos_array;
    std::vector<iord> neg_array;
    
    // Use this to analysis input string
    void analysis(std::string input){
        cutString(input);
        output_array = new iord[input_temp.size()];
        std::vector<std::string>::iterator str_vector_it;
        int i=0;
        for(str_vector_it=input_temp.begin();str_vector_it!=input_temp.end();str_vector_it++){
            output.push_back(typeconvert<iord>((*str_vector_it).c_str()));
            output_array[i]=typeconvert<iord>((*str_vector_it).c_str());
            i++;
        }
    }
    
private:
    // Convert data type
    template<class out_type, class in_type>
    out_type typeconvert(const in_type input) {
        std::stringstream ss;
        out_type output;
        ss.clear();
        ss << input;
        ss >> output;
        ss.clear();
        ss.str();
        return static_cast<out_type>(output);
    }
    
    //Cut string input to pieces
    void cutString(std::string input){
        input_temp.clear();
        std::size_t str_it,str_temp;
        for(str_temp=str_it=0;str_it<input.size()+1;str_it++){
            if(input[str_it] == PUNC || str_it ==input.size()){
                std::string temp=input.substr(str_temp,str_it-str_temp);
                Trim(temp);
                if(temp.size()!=0){
                    input_temp.push_back(temp);
                }
                str_temp=str_it+1;
            }
        }
    }
    
    //If this is a space char
    bool IsSpace(char c){
        if(' '==c||'\t'==c)
            return true;
        return false;
    }

    //Get rid of space at the begin and at the end of a string
    void Trim(std::string &str){
        if(str.empty()){
            return;
        }
        int i, start_pos,end_pos;
        for (i=0;i<str.size();i++){
            if(!IsSpace(str[i])){
                break;
            }
        }
        if(i==str.size()){
            str="";
            return;
        }
        start_pos=i;
        for(i=str.size()-1;i>=0;i--){
            if(!IsSpace(str[i])){
                break;
            }
        }
        end_pos=i;
        str=str.substr(start_pos,end_pos-start_pos+1);
        return;
    }
    std::vector<std::string> input_temp;
};

template<typename iord>
void output_result(std::deque<vector <iord> > & result,std::chrono::steady_clock::time_point time_p1,std::chrono::steady_clock::time_point time_p2){
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(time_p2-time_p1);
    if (result.size() != 0){
        cout<<"sets exist. There are "<<result.size()<<" of them"<<endl;
        std::deque< vector<int> >::iterator result_it;
        for(result_it=result.begin();result_it!=result.end();result_it++){
            cout<<"Set: "<<(*result_it)[0]<<","<<(*result_it)[1]<<","<<(*result_it)[2]<<endl;
        }
    }
    else
        cout<<"No"<<endl;
    cout<<"Cost "<<time_span.count()<<" seconds."<<endl;
}

template<typename iord>
void pack_result(std::deque<vector <iord> > & result, iord a1, iord a2, iord a3){
    std::vector<iord> vec_temp;
    vec_temp.clear();
    vec_temp.push_back(a1);
    vec_temp.push_back(a2);
    vec_temp.push_back(a3);
    result.push_back(vec_temp);
    return;
}

/*
 * 
 */
int main(int argc, char** argv) {
    // To get input from terminal
    char t[500];
    cout<<"Input the number line:"<<endl;
    cin.getline(t, 500);
    // To analysis the input in an int vector
    std::string test(t);
    util<int> body(test);
    // Safe check. Make sure there are enough parameters for analysis
    if(body.output.size() < 3){
        cout<<"Error: Not enough numbers input"<<endl;
    }
    cout<<"There are "<<body.output.size()<<" numbers in array to be calculated"<<endl;
    // Prepare for output result
    std::deque< vector<int> > result;
    std::vector<int> vec_temp;
    std::chrono::steady_clock::time_point time_p1;
    std::chrono::steady_clock::time_point time_p2;

/*******************************************************************************************/
    cout<<"**************************"<<endl;
    cout<<"Algorithm 1: n3 Brutal solution"<<endl;
    //Start time counting
    time_p1=std::chrono::steady_clock::now();
    // Algorithm 1: n3 brutal 
    for(int i=0;i<body.output.size();i++)
        for(int j=i+1;j<body.output.size();j++)
            for(int k=j+1;k<body.output.size();k++){
                if((body.output[i]+body.output[j]+body.output[k]) == 0){
                    ::pack_result(result,body.output[i],body.output[j],body.output[k]);
                }
            }
    // Stop time counting
    time_p2=std::chrono::steady_clock::now();
    //Output the result and duration time this algorithm took
    ::output_result(result,time_p1,time_p2);
    
    
/*******************************************************************************************/
    cout<<"**************************"<<endl;
    cout<<"Algorithm 2: n2log(n) A little faster solution"<<endl;
    result.clear();
    vec_temp.clear();
    //Sort the array at first
    body.Sort(body.output_array,body.output.size());
    //Start time counting
    time_p1=std::chrono::steady_clock::now();
    // Algorithm 2: n2log n
    for(int i=0;i<body.output.size();i++)
        for(int j=i+1;j<body.output.size();j++){
            int array_it = body.output.size(),array_it_temp=0;
            int cal_temp=0;
            array_it = (int)((j+body.output.size())/2);
            while(true){
                if(array_it<=j)
                    break;
                cal_temp=body.output_array[i]+body.output_array[array_it]+body.output_array[j];
                //cout<<body.output_array[i]<<"  "<<body.output_array[array_it]<<"  "<<body.output_array[j]<<endl;
                if(cal_temp==0){
                    //Find an available one, push to vector
                    ::pack_result(result,body.output_array[i],body.output_array[j],body.output_array[array_it]);
                    break;
                }
                else if(cal_temp>0){
                    array_it_temp=(int)((j+array_it)/2);
                    if(array_it_temp==array_it)
                        //This means there is no more number can be used on left
                        break;
                    else
                        //There are numbers on the left, keep finding
                        array_it=array_it_temp;
                }
                else if(cal_temp<0){
                    array_it_temp=(int)((array_it+body.output.size())/2);
                    if(array_it_temp==array_it)
                        //This means there is no more number can be used on the right
                        break;
                    else
                        //There are numbers on the right, keep finding
                        array_it=array_it_temp;
                }
                
            }
        }
    // Stop time counting
    time_p2=std::chrono::steady_clock::now();
    //Output the result and duration time this algorithm took1 
    ::output_result(result,time_p1,time_p2);
    
/*******************************************************************************************/    
    
    
//    for(int i=0;i<body.output.size()-1;i++){
//        cout<<body.output_array[i]<<",";
//    }
//    cout<<body.output_array[body.output.size()-1]<<endl;
    
    return 0;
}

