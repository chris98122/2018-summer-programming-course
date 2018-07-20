#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;
map<string,int> ham_word;
map<string,int> spam_word;
vector<string> ham_words;
vector<string> spam_words;
map<string,double> ham_probability;
map<string,double> spam_probability;


class Email
{
    public:
    vector<string> words;
    double ham_p;
    double spam_p;
    int number_count=0;
    bool property;//1 means spam 0 means ham
};
vector<Email> test_mail;

void split_blank(const string& str,vector<string> &ret);
void split_blank_v2(const string& str,vector<string> &ret);
void split_w(const string& str,const char& w,vector<string> &ret);
void word_wash(vector<string>& words);
string trim(string &s);
void read_training_mail()
{   vector<string> temp;
    vector<string> ::iterator iter;
    string str;
    ifstream fin("TrainingSet");
    while(getline(fin,str))
    {
            split_blank(str,temp);
            iter=temp.begin();
            if(*iter=="ham"){
                iter++;
                while(iter!=temp.end()){
                string s=*iter;
                trim(s);
                split_w(s,'.',ham_words);
                iter++;
                    }
            }
            if(*iter=="spam"){
                     iter++;
                while(iter!=temp.end()){
                string s=*iter;
                trim(s);
                split_w(s,'.',spam_words);
                iter++;}
            }
            temp.clear();
    }
}

void read_test_mail()
{   ifstream fin("TestingSet");
    string str;
    Email test;
    while(getline(fin,str))
        { split_w(str,'.',test.words);
            word_wash(test.words);
        test_mail.push_back(test);
        test.words.clear();
        }
}

void number_count()
{
     vector<Email> ::iterator iter;
      vector<string> ::iterator iter_s;
    for(iter=test_mail.begin();iter!=test_mail.end();iter++)
    {
        for(iter_s=(*iter).words.begin();iter_s!=(*iter).words.end();iter_s++)
        if(*iter_s>="0"&&*iter_s<="9")
        {
            (*iter).number_count++;
        }
    }
}


string trim(string &s)
{
    string temp=s;
    if (temp.empty())
    {
        return temp;
    }
    temp.erase(0,temp.find_first_not_of(" "));
    temp.erase(temp.find_last_not_of(" ") + 1);
    return temp;
}




void word_wash(vector<string>& words)
{  vector<string> addition;

     vector<string> ::iterator iter;
     for(iter=words.begin();iter!=words.end();iter++)
            {
                  string::iterator it;
                for(it=(*iter).begin();it!=(*iter).end();it++)
                {
                    (*it)=tolower(*it);
                    }
                }
    for(iter=words.begin();iter!=words.end();iter++)
        {  string::iterator it;
            bool is_normal_word=1;
         *iter=trim(*iter);
          for(int i=0;i<(*iter).length();i++)
                {
                 //   if((*iter)[i]=='?'||(*iter)[i]=='!'||(*iter)[i]==','||(*iter)[i]=='/'||(*iter)[i]=='"'||(*iter)[i]==')'||(*iter)[i]==':'||(*iter)[i]=='('||(*iter)[i]=='+'||(*iter)[i]=='*'||(*iter)[i]=='@')
                  //  {(*iter)[i]='\0';}

                    if((*iter)[i]<'a'||(*iter)[i]>'z')
                        {

                    if((*iter)[i]=='0')addition.push_back("0");
                    if((*iter)[i]=='1')addition.push_back("1");
                    if((*iter)[i]=='2')addition.push_back("2");
                    if((*iter)[i]=='3')addition.push_back("3");
                    if((*iter)[i]=='4')addition.push_back("4");
                    if((*iter)[i]=='5')addition.push_back("5");
                    if((*iter)[i]=='6')addition.push_back("6");
                    if((*iter)[i]=='7')addition.push_back("7");
                    if((*iter)[i]=='8')addition.push_back("8");
                    if((*iter)[i]=='9')addition.push_back("9");

                        is_normal_word=0;
                        }
                }
                if(is_normal_word)
                addition.push_back(*iter);

            split_blank_v2(*iter,addition);
        }

        words.clear();
        for(iter=addition.begin();iter!=addition.end();iter++)
        words.push_back(*iter);
}

map<string,double> cal_probability(vector <string>& words,map<string,int> word_num)
{   map<string,double> ret;
    vector<string>::iterator word_iter_1;
    map<string,int>::iterator word_num_iter;
    word_num.insert( pair<string, int>(*words.begin(),0));
    for(word_iter_1=words.begin();word_iter_1!=words.end();word_iter_1++)
    {   //cout<<*word_iter_1;
        if(*word_iter_1!="\0"&&*word_iter_1!=" "&&*word_iter_1!="  "&&*word_iter_1!="   "){
        for(word_num_iter=word_num.begin();word_num_iter!=word_num.end();word_num_iter++){
         if(*word_iter_1==(*word_num_iter).first)
            {   (*word_num_iter).second++;
            // cout<<"matched!!"<<endl;
             break;
            }
        else if(*word_iter_1==((*word_num_iter).first+"\0")||(*word_iter_1+" ")==(*word_num_iter).first||(*word_iter_1+"\0\0")==(*word_num_iter).first)
            {   (*word_num_iter).second++;
          //  cout<<"a blank!"<<endl;
            break;
            }
        }
        if(word_num_iter==word_num.end()){
                word_num.insert( pair<string, int>(*word_iter_1,1));
              //  cout<<"inserted!!"<<endl;
            }
        }
    }

    double num= word_num.size()+0.0;
    for(word_num_iter=word_num.begin();word_num_iter!=word_num.end();word_num_iter++)
 {
        ret.insert( pair<string, double>((*word_num_iter).first,(*word_num_iter).second/num));
 }
    return ret;
}


void split_blank(const string& str,vector<string> &ret){
    string t;
    istringstream in(str);
    while (in >> t) {
            ret.push_back(t);
    }
    }

void split_blank_v2(const string& str,vector<string> &ret){
    string t;
    istringstream in(str);
    for (int i=0;in >> t;i++) {
            if(i!=0)
            ret.push_back(t);
    }
}

void split_w(const string& str,const char& w,vector<string> &ret){
    int i=0;
    string t;
    stringstream ss(str);
    while(getline(ss, t, w))
{
    ret.push_back(t);
}
}

void printvector(vector<string> &ret)
{   vector<string>::iterator iter;
    for (iter =ret.begin();iter != ret.end();++iter)
         {
            cout << *iter<<" " ;
         }
}

void printEmail(vector<Email> &ret)
{   vector<Email>::iterator iter;
    for (iter =ret.begin();iter != ret.end();++iter)
         {
          printvector((*iter).words);

         }
}

void printEmailProbability(vector<Email> &ret)
{   vector<Email>::iterator iter;
    for (iter =ret.begin();iter != ret.end();++iter)
         {
         cout<<(*iter).ham_p<<endl<<(*iter).spam_p<<endl<<(*iter).number_count;
         cout<<endl;
         }
}
void printEmailProperty(vector<Email> &ret)
{   vector<Email>::iterator iter;
    for (iter =ret.begin();iter != ret.end();++iter)
         {   printvector((*iter).words);
             if((*iter).property)
                cout<<"spam"<<endl;
                else
                cout<<"ham"<<endl;
         }
}


void printmap(map<string,int>&map_to_print)
{   map<string,int>::iterator iter;
    for (iter =map_to_print.begin();iter != map_to_print.end();++iter)
         {
            cout << (*iter).first<< " "<<(*iter).second<< endl;
         }
}


void printmap(map<string,double>&map_to_print)
{   map<string,double>::iterator iter;
    for (iter =map_to_print.begin();iter != map_to_print.end();++iter)
         {
            cout << (*iter).first<<" "<<(*iter).second<< endl;
         }
}


double search_probability(string& test,map<string,double>& word_probability)
{
    map<string,double>::iterator map_iter;
    for( map_iter= word_probability.begin(); map_iter!=word_probability.end(); map_iter++)
    {
        if(test==(*map_iter).first)
        break;
    }
    if(map_iter==word_probability.end()||test=="a"||test=="the")
    return 0.01;
    else
    return (*map_iter).second;

}
void cal_test_probability(vector<Email>& test)
{   vector<Email>::iterator iter_mail;
    vector<string>::iterator iter_word;
    double ham_p=1;
    double spam_p=1;
    for (iter_mail =test.begin();iter_mail != test.end();++iter_mail){
            ham_p=1;
            for(iter_word=(*iter_mail).words.begin();iter_word!=(*iter_mail).words.end();iter_word++)
                {ham_p*=search_probability((*iter_word),ham_probability);
               //  cout<<ham_p<<endl;
                (*iter_mail).ham_p=ham_p;
                }
            }
    for (iter_mail =test.begin();iter_mail != test.end();++iter_mail){
            spam_p=1;
            for(iter_word=(*iter_mail).words.begin();iter_word!=(*iter_mail).words.end();iter_word++)
                {spam_p*=search_probability((*iter_word),spam_probability);}
                // cout<<spam_p<<endl;
                (*iter_mail).spam_p=spam_p;
        }
}

void ham_or_spam(vector<Email>& test)
{   vector<Email>::iterator iter_mail;
    for (iter_mail =test.begin();iter_mail != test.end();++iter_mail){
    if((*iter_mail).number_count>7)
         (*iter_mail).property=1;
    else if((*iter_mail).ham_p>(*iter_mail).spam_p/1000.0)
    {
        (*iter_mail).property=0;//0 means ham
    }
    else{
       (*iter_mail).property=1;//1 means spam
    }

}
}
 int main()
 {   read_training_mail();
        word_wash(ham_words);
        word_wash(spam_words);
     //  printvector(ham_words);
      //   printvector(spam_words);
       ham_probability=cal_probability(ham_words,ham_word);
      spam_probability=cal_probability(spam_words,spam_word);
      //   printmap(ham_probability);
       //   printmap(spam_probability);
        read_test_mail();
        number_count();
        string t="i";
       double test_one=search_probability(t,ham_probability);
       double test_two=search_probability(t,spam_probability);
     //   cout<<test_one<<endl;
       //  cout<<test_two<<endl;
        cal_test_probability(test_mail);
        //      printEmailProbability(test_mail);
        ham_or_spam(test_mail);
    //    printEmail(test_mail);
        printEmailProperty(test_mail);
        // cout<<test_mail.size();
      //   cal_correctness(test_mail);
     }
