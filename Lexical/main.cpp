#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

class lexical
{
    private:
        vector<string>tokens;
    public:

        void checkType(string tok)
        {
            string keywords[]={"bool","real","decimal","if","elif","else"};
            string arithmetic[]={"=","+","-","*","/","%"};
            string relational[]={">","<",">=","<=","==","!="};
            string unary[]={"++","--"};
            string logical[]={"||","&&"};
            string parentheses[]={"(",")","{","}"};
            string digit="0123456789.";
            bool l[]={0,0,0,0,0,0,0};

            for(int i=0;i<11;i++)
            {

                if(tok[0]==digit[i])
                   {l[0]=1; cout<<tok<<" : Digit"<<endl; break;}

            }
            for(int i=0;i<6;i++)
            {
                if(tok==keywords[i])
                    {l[1]=1;cout<<tok<<" : Keyword"<<endl; break;}
                if(tok==arithmetic[i])
                    {l[2]=1;cout<<tok<<" : Arithmetic Operator"<<endl; break;}
                if(tok==relational[i])
                    {l[3]=1;cout<<tok<<" : Relational Operator"<<endl; break;}
            }
            for(int i=0;i<2;i++)
            {
                if(tok==unary[i])
                    {l[4]=1;cout<<tok<<" : Unary Operator"<<endl; break;}
                if(tok==logical[i])
                    {l[5]=1;cout<<tok<<" : Logical Operator"<<endl; break;}
            }
            for(int i=0;i<4;i++)
            {
                    if(tok==parentheses[i])
                        {
                            l[6]=1;
                            if(i%2)
                                cout<<tok<<" : Closed Par"<<endl;
                            else
                                cout<<tok<<" : OPen Par"<<endl;
                            break;
                        }
            }
            if(!l[0]&&!l[1]&&!l[2]&&!l[3]&&!l[4]&&!l[5]&&!l[6])
            {
                cout<<tok<<" : Identifier"<<endl;
            }
        }

        void getTokens(string input)
        {
            char spacer = ' ';
            tokens.clear();
            stringstream inputStream(input);
            string intermediateToken;
            while(getline(inputStream, intermediateToken, spacer))
              {
                  //remove not-needed '\n'
                  intermediateToken.erase(std::remove(intermediateToken.begin(),intermediateToken.end(), '\n'), intermediateToken.end());
                  tokens.push_back(intermediateToken);
              }
        }
        void getLexeme()
        {
            for(int i=0;i<tokens.size();i++)
                checkType(tokens[i]);
        }

};

int main()
{
      ifstream input;
      string line;
      input.open("input.txt");
      while(getline(input, line, ';')){
            lexical x = lexical();
         char tokline[line.length()];
         for(int i=0;i<=line.length();i++)
            tokline[i]=line[i];

        cout<<tokline<<endl;
        x.getTokens(tokline);
        x.getLexeme();
        cout<<"\n-------------------\n";
      }

    return 0;
}
