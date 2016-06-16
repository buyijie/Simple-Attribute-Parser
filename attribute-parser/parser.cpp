/*hackerrank.com/challenges/attribute-parser
example:
    <tag1 value="HelloWorld">
    <tag2 name="Name1">
    </tag2>
    </tag1>
    query:
    tag1~value
    tag1.tag2~name
*/
#include<iostream>
#include<sstream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<vector>
#include<map>
#include<algorithm>
#include<regex>
using namespace std;

int N, Q;
map<string, string> attribute;

void add_attribute(string prefix, string line)
{
    string name, value, span;
    stringstream ss(line);
    while(ss>>name>>span>>value)
    {
        value.erase(0, 1);
        value.erase(value.length()-1);
        attribute[prefix+"~"+name]=value;
    }
}

void parse_attribute(int line_num)
{
    string prefix, current_line, current_tag_name,
           current_attribute_name, current_attribute_value;
    regex match("<(?!/)([^ ]+)(?: ([^>]+))?>");
    smatch result;
    vector<string> prefix_vector;
    prefix_vector.clear();
    while(line_num--)
    {
        getline(cin, current_line);
        if(regex_match(current_line, result, match))
        {
            prefix_vector.push_back(result[1].str());
            prefix=prefix+'.'+result[1].str();
            if(result[2].matched)
            {
                add_attribute(prefix.substr(1), result[2].str());
            }
        }
        else
        {
            prefix.erase(prefix.length()-prefix_vector.back().length()-1,
                    prefix_vector.back().length()+1);
            prefix_vector.pop_back();
        }
    }
}

void query(int line_num)
{
    string s;
    while(line_num--)
    {
        cin>>s;
        if(attribute.find(s)!=attribute.end())
        {
            cout<<attribute[s]<<endl;
        }
        else cout<<"Not Found!"<<endl;
    }
}

int main()
{
    cin>>N>>Q>>ws;
    parse_attribute(N);
//    cout<<"parse input complete"<<endl;
    query(Q);
//    for(map<string, string>:: iterator it=attribute.begin(); it!=attribute.end(); ++it)
//    {
//        cout<<it->first<<" "<<it->second<<endl;
//    }
    return 0;
}

