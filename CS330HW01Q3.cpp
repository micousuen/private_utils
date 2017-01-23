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
#include <vector>
#include <deque>
#define PUNC ' '

using namespace std;

class util {
public:
    util(std::string input){util::analysis(input);}
    
    // The output int vector
    std::vector<int> output;
    
    // Use this to analysis input string
    void analysis(std::string input){
        cutString(input);
        std::vector<std::string>::iterator str_vector_it;
        for(str_vector_it=input_temp.begin();str_vector_it!=input_temp.end();str_vector_it++){
            output.push_back(std::atoi((*str_vector_it).c_str()));
        }
    }
    
private:
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

/*
 * 
 */
int main(int argc, char** argv) {
    char t[500];
    cout<<"Input the number line:"<<endl;
    cin.getline(t, 500);
    std::string test(t);
    util body(test);
    
    if(body.output.size() < 3){
        cout<<"Error: Not enough numbers input"<<endl;
    }
    std::deque< vector<int> > result;
    std::vector<int> vec_temp;
    for(int i=0;i<body.output.size();i++)
        for(int j=1;j<body.output.size();j++)
            for(int k=2;k<body.output.size();k++){
                if((body.output[i]+body.output[j]+body.output[k]) == 0){
                    vec_temp.push_back(body.output[i]);
                    vec_temp.push_back(body.output[j]);
                    vec_temp.push_back(body.output[k]);
                    result.push_back(vec_temp);
                }
            }
    if (result.size() != 0)
        cout<<"A set exist."<<endl;
    else
        cout<<"No"<<endl;
            
    return 0;
}

