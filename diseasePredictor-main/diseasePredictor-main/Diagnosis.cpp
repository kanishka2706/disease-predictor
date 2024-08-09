#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<string>> symptoms;
vector<string> diseases;

void printvec(vector<string> s)
{
    for(int i = 0; i < s.size(); i++) cout<<s[i]<<" ";
    cout<<"\n";
}

void init()
{
    FILE* fp = fopen("symptoms.csv","r");

    if(!fp) printf("Error reading file");
    else 
    {
        char buffer[1024];
        int column = 0;
  
        while (fgets(buffer, 1024, fp)) 
        {
            column = 0;
            char* value = strtok(buffer, ",");
            vector<string> temp;

            while (value) 
            {
                
                if(column == 0) diseases.push_back(value);

                temp.push_back(value);
                value = strtok(NULL, ",");
                column++;
            }
            symptoms.push_back(temp);
        }
        fclose(fp);
    }
    
    for(string &s : diseases)
    {
        transform(s.begin(), s.end(), s.begin(), [](char c){ return tolower(c); });
    }

    for(vector<string> &temp : symptoms)
    {
        for(string &s : temp)
        {
            transform(s.begin(), s.end(), s.begin(), [](char c){ return tolower(c); });
        }
    }

    // for(int i = 0; i < symptoms.size(); i++)
    // {
    //    for(int j = 0; j < symptoms[i].size(); j++)
    //    {  
    //        cout<<symptoms[i][j]<<" ";
    //    }
    //    cout<<"\n";
    // }

}


void finddiagnosis(vector<string> symp)
{
    vector<string> c;
    cout<<"Possible Diagnostics: \n";
    for(int i = 0; i < symptoms.size(); i++)
    {   
        int count = 0;
        for(int j = 0; j < symp.size(); j++)
        {
            if(find(symptoms[i].begin(), symptoms[i].end(), symp[i]) != symptoms[i].end())
            {
                count++;
            }
        }
        if(count>=3)
        {
            c.push_back(symptoms[i][0]);
        }
    }
    printvec(c);
    cout<<"\n";
}

int main()
{
    init();

    vector<string> symp;
    string temp;
    cout<<"Enter symptoms(When you want to search press s and enter): \n";
    cout<<"Press enter after giving each symptom\n";
    for(int i = 0; i < 10 ; i++)
    {
        cin>>temp;
        if(temp == "s") break;
        symp.push_back(temp);
    }
    cout<<"Your symptoms are: ";
    printvec(symp);
    finddiagnosis(symp);

    return 0;
}