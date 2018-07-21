#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;
map<string,int> occupation;
map<string,int> genre;
//us.size();
//occupation.size()
void printvector(vector<string> &ret);

class user
{
    friend  void count_occupation(vector<user> &us,map<string,int>& occupation);
    friend void print_user(vector<user> &us);
 public:
    int user_id;
    string occupation;
    void  read_user(user& u);
};
vector<user> us;
class movie
{   friend void print_movie(vector<movie> &mov);
public:
    int movie_id;
    map<string,int> points;//points by occupation
    vector<string> genre;
    string movie_name;

     void  read_movie(movie& m,map<string,int>& gen);
};



class Rate:public user,public movie{
public:
    int rate;
    void  read_rate(Rate& r,vector<Rate>& rate);
};


vector<movie> mov;
void split_blank(const string& str,vector<string> &ret);
void split_w(const string& str,const char& w,vector<string> &ret);
vector<Rate> rate;
void user::read_user(user& a)
{
    string s;
    vector<string> ret;
    ifstream fin("u.user");
    while(getline(fin,s))
    {
        split_w(s,'|',ret);
        ret.pop_back();
       // cout<<ret.size();
        a.occupation=*(ret.end()-1);
        ret.pop_back();
        ret.pop_back();
        ret.pop_back();
        string temp=*(ret.end()-1);
        a.user_id=atoi(temp.c_str());
        ret.clear();
        us.push_back(a);
    }
}

void print_user(vector<user> &us)
{   vector<user>::iterator iter;
    for (iter =us.begin();iter != us.end();++iter)
         {
            cout << (*iter).user_id<< endl;
             cout << (*iter).occupation<< endl;
         }
}

void read_occupation(map<string,int>&readin)
{   string s;
    ifstream fin("u.occupation");
    while( getline(fin,s))
    {
    readin.insert( pair<string, int>(s, 0) );
    }
}


void read_genre(map<string,int>&readin)
{   string s;
    ifstream fin("u.genre");
    int i=0;
    vector<string> ret;
     while(getline(fin,s))
    {
        split_w(s,'|',ret);
        ret.pop_back();
        readin.insert( pair<string, int>(*(ret.end()-1),0) );
        i++;
    }
}


void movie::read_movie(movie& m,map<string,int>& gen)
{   int k=0;
    string s;
    vector<string> ret;
    ifstream fin("u.item");
    int i=0;
    while(getline(fin,s))
    {   map<string,int>::iterator iter;
        split_w(s,'|',ret);
       for(int i=19;i>0;i--)
           { if(*(ret.end()-1)=="1")
                {iter=gen.begin();
                for (int j=1;j<i-1;j++)++iter;
                    m.genre.push_back((*iter).first);
                }
                ret.pop_back();
        }
        ret.pop_back();
        ret.pop_back();
        ret.pop_back();
        m.movie_name=*(ret.end()-1);
        ret.pop_back();
        string temp=*(ret.end()-1);
        m.movie_id=atoi(temp.c_str());
        ret.clear();
        mov.push_back(m);
        m.genre.clear();
    }
}

void  Rate::read_rate(Rate& r,vector<Rate>& rate)
{
    string s;
    ifstream fin("u.data");
    int i=0;
    vector<string> ret;
     while(getline(fin,s))
    {
        split_blank(s,ret);
        ret.pop_back();
        string temp=*(ret.end()-1);
        r.rate=atoi(temp.c_str());
        ret.pop_back();
        temp=*(ret.end()-1);
        r.user_id=atoi(temp.c_str());
         ret.pop_back();
         temp=*(ret.end()-1);
        r.movie_id=atoi(temp.c_str());
         ret.clear();
        rate.push_back(r);
    }
}
void print_movie(vector<movie> &mov)
{   vector<movie>::iterator iter;
    for (iter =mov.begin();iter != mov.end();++iter)
         {
            cout << (*iter).movie_id<< " " << (*iter).movie_name<<" ";
            printvector((*iter).genre);
            cout<<endl;
         }
}

void print_rate(vector<Rate> &rate)
{   vector<Rate>::iterator iter;
    for (iter =rate.begin();iter != rate.end();++iter)
         {
            cout << (*iter).user_id<< " " << (*iter).movie_id<<" "<<(*iter).rate<<endl;
         }
}


void split_blank(const string& str,vector<string> &ret){
    int i=0;
    string t;
    istringstream in(str);
    while (in >> t) {

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
            cout << *iter <<" ";
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
            cout << (*iter).first<< " "<<(*iter).second<< endl;
         }
}


 void count_occupation(vector<user> &us,map<string,int>& oc)
 {   map<string,int>::iterator iter_map;
      vector<user>::iterator iter;
        for (iter =us.begin();iter != us.end();++iter)
         {   for (iter_map =oc.begin();iter_map != oc.end();++iter_map)
            if((*iter).occupation==(*iter_map).first)
            (*iter_map).second++;
        }
 }

vector<map <string,double> > cal_rate_by_oc(vector<user> &us,map<string,int>& oc,vector<Rate>& rate,vector<movie> &mov)
 {  vector<map <string,double> > ret;
     map <string,int> ratings;
     map <string,int> num;
    vector<user>::iterator finda_user;
    vector<Rate>::iterator finda_rate;
    vector<movie>::iterator finda_movie;
    map <string,int> ::iterator finda_ret;
    map <string,int> ::iterator finda_ratings;
    map <string,int> ::iterator finda_occupation;
    map <string,int> ::iterator finda_num;
    finda_rate=rate.begin();
    for(finda_occupation=oc.begin();finda_occupation!=oc.end();finda_occupation++)
        {
            //cout<<"a new occupation"<<endl;
        for(finda_user=us.begin();finda_user!=us.end();finda_user++){

            if((*finda_user).occupation==(*finda_occupation).first)
                {

               // cout<<"a new user"<<endl;

                for(finda_rate=rate.begin();finda_rate!=rate.end();finda_rate++)
                    {if((*finda_rate).user_id==(*finda_user).user_id)

                   // cout<<"a new rate"<<endl;

                        for(finda_movie=mov.begin();finda_movie!=mov.end();finda_movie++){
                        if((*finda_rate).movie_id==(*finda_movie).movie_id)
                           {    ratings.insert( pair<string, int>("test",0));
                                num.insert( pair<string, int>("test",0));

                              // cout<<(*finda_movie).movie_name<<endl;
                        for(finda_ratings=ratings.begin();finda_ratings!=ratings.end();finda_ratings++){
                                if((*finda_ratings).first==(*finda_movie).movie_name){
                                (*finda_ratings).second+=(*finda_rate).rate;
                                for(finda_num=num.begin();finda_num!=num.end();finda_num++)
                                {
                                        if((*finda_num).first==(*finda_ratings).first)
                                         {
                                                (*finda_num).second++;

                                      //      if((*finda_num).second>2)
                                        //   cout<<(*finda_num).first<<" "<<(*finda_num).second<<endl;
                                             }
                                }
                                //cout<<(*finda_ratings).first<<" "<<(*finda_ratings).second<<endl;
                                break;
                                }
                               }
                                if(finda_ratings==ratings.end()){
                                ratings.insert( pair<string, int>((*finda_movie).movie_name,(*finda_rate).rate));
                                num.insert( pair<string, int>((*finda_movie).movie_name,1));
                             //   cout<<(*finda_movie).movie_name<<"add to list"<<endl;
                                }
                              }
                           }
                        }
                    }
                }

    map <string,double> average;
    map <string,double> ::iterator iter_average=average.begin();

    double ave=0.0;
   // cout<<endl<<"a new occupation"<<endl;
   // cout<<endl<<"ratings"<<endl;
   // printmap(ratings);

   // cout<<endl<<"num"<<endl;
   // printmap(num);
    finda_num=num.begin();
    for(finda_ratings=ratings.begin();finda_ratings!=ratings.end();finda_ratings++)
    {      if((*finda_num).second>2)
        {ave=((*finda_ratings).second+0.0)/((*finda_num).second+0.0);
         average.insert(pair<string, double>((*finda_ratings).first,ave));
        }
        finda_num++;
    }
    ret.push_back(average);
   // cout<<endl<<"average"<<endl;
    // printmap(average);
    ratings.clear();
    num.clear();
    average.clear();
    }


    return ret;
 }


 map<string,double> top_rating(map<string,double> mov)
 {
    map<string,double> ret;
    map <string,double> ::iterator iter;
    double toprate=0.0;
    for(iter=mov.begin();iter!=mov.end();iter++)
    {   if(toprate<(*iter).second)
        {
            toprate=(*iter).second;
       // cout<<" "<<temp<<endl;
        }
    }
    for(iter=mov.begin();iter!=mov.end();iter++)
    {
        if(toprate==(*iter).second)
          ret.insert( pair<string, double>((*iter).first,toprate));
    }
    return ret;
 }

void print_movie_name_genre(map<string,double>  top_mov)
  {
      map <string,double> ::iterator iter;
      vector<movie>::iterator class_iter;
      vector<string>::iterator genre_iter;
      for(iter=top_mov.begin();iter!=top_mov.end();iter++)
      {
        for(class_iter=mov.begin();class_iter!=mov.end();class_iter++)
          if((*iter).first==(*class_iter).movie_name)
            {
           cout<<(*iter).first<<" "<<(*iter).second<<" ";
            printvector((*class_iter).genre);
            cout<<endl;
            break;
            }
      }

  }

 int main()
 {  user u;
    u.read_user(u);
    movie m;
    read_genre(genre);
    m.read_movie(m,genre);
    //read and print occupation in a map
    read_occupation(occupation);
    count_occupation(us,occupation);

    Rate r;
    r.read_rate(r,rate);

    vector<map<string,double> > test;
    test=cal_rate_by_oc(us,occupation,rate,mov);
    vector<map<string,double> > ::iterator iter_test;

    map<string,int>::iterator oc_iter;
    map<string,double> top_rating_mov;
    oc_iter=occupation.begin();


    for(iter_test=test.begin(); iter_test!=test.end(); iter_test++)
        {
        cout<<(*oc_iter).first<<endl;
        top_rating_mov=top_rating(*iter_test);

        cout<<"top movies:"<<endl;
        print_movie_name_genre(top_rating_mov);
       // printmap(top_rating_mov);

        oc_iter++;
        cout<<endl;
        }
 }
