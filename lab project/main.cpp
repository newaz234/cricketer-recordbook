#include <iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;
int search_player(string name,string);
class Player

{
    protected:
    string name,country;
    int hs=0,matches=0,run=0,wicket=0,ball_faced=0,bowled=0,six=0,four=0;
    public:

        Player(){}
        Player(string n,string c):name(n),country(c){}
        Player(string n,string c,int r,int b,int w,int f,int s):name(n),country(c),run(r),ball_faced(b),wicket(w),four(f),six(s){}
        //friend function
        friend search_player(string,string);
        friend class Team;
        friend add_player();
        friend player_individual_status();
        details()
        {
            cout<<"Name         : "<<name<<endl;
            cout<<"Team         : "<<country<<endl;
            cout<<"Matches      : "<<matches<<endl;
            cout<<"runs         : "<<run<<endl;
            cout<<"wicket       : "<<wicket<<endl;
            if(matches==0)
            cout<<"average      : -"<<endl;
            else
            cout<<"average      : "<<run/matches<<endl;
            if(ball_faced==0)
            cout<<"strike rate  : -"<<endl;
            else
            cout<<"strike rate  : "<<run*100/ball_faced<<endl;
            cout<<"highest score: "<<hs<<endl;
            cout<<"Total Sixs   : "<<six<<endl;
            cout<<"Total fours  : "<<four<<endl;
        }
        //operator overloading
        Player operator+(Player obj)
        {
            Player o;
             o.hs=obj.hs>run? obj.hs:run;
             o.run=obj.run+run;
             o.wicket=obj.wicket+wicket;
             o.six=obj.six+six;
             o.four=obj.four+four;
             o.name=obj.name;
             o.country=obj.country;
             o.matches=obj.matches+1;
             o.ball_faced=obj.ball_faced+ball_faced;
             return o;

        }

};
//inheritance
class Team:public Player
{
    string team_name;
    string name[11];
   public:
       Team( string n):team_name(n){}
      void playing_xi()
         {

             int flag;

             cout<<team_name<<" Playing XI"<<endl;
             for(int i=0;i<11;i++)
             {
                 cout<<i+1<<".";
                 getline(cin,name[i]);
             }
              ofstream ouf("name.txt",ios::app);
             for(int i=0;i<11;i++)
             {

                 flag=search_player(name[i],team_name);
                 if(flag==0)
                 {
                     Player pl(name[i],team_name);
                     ouf<<pl.name<<endl;
                     ouf<<pl.country<<endl;
                     ouf<<pl.run<<" "<<pl.ball_faced<<" "<<wicket<<" "<<pl.six<<" "<<pl.four<<" "<<pl.matches<<" "<<pl.hs<<endl;
                 }
             }
         }

         update_status()
         {
            string n,teamname;
             Player p[11];

            for(int i=0;i<11;i++)
            {
                cout<<"batter: "<<name[i]<<endl;
                cout<<"run   : ";
                cin>>run;
                cout<<"ball  : ";
                cin>>ball_faced;
                cout<<"wicket:";
                cin>>wicket;
                cout<<"fours  : ";
                cin>>four;
                cout<<"six    : ";
                cin>>six;
                Player obj(name[i],team_name,run,ball_faced,wicket,four,six);
                p[i]=obj;
                system("cls");
            }
            ifstream inf("name.txt");
            ofstream ouf("temp.txt");
            while(inf)
            {
                char c;
                int flag=0;
                inf>>n;
                inf>>teamname;
                inf>>run>>ball_faced>>wicket>>six>>four>>matches>>hs;
                for(int i=0;i<11;i++)
                {
                    if(n==name[i]&&teamname==team_name)
                    {
                        Player obj(name[i],country,run,ball_faced,wicket,four,six);
                        p[i]=p[i]+obj;
                        //hs=hs>p[i].run? hs:p[i].run;
                        ouf<<n<<endl;
                        ouf<<teamname<<endl;
                        ouf<<p[i].run<<" "<<p[i].ball_faced<<" "<<p[i].wicket<<" ";
                        ouf<<p[i].six<<" "<<p[i].four<<" "<<p[i].matches<<" "<<p[i].hs<<endl;
                        flag=1;
                        }
                }
                if(flag==0)
                {
                    ouf<<n<<endl;
                    ouf<<teamname<<endl;
                    ouf<<run<<" "<<ball_faced<<" "<<wicket<<" "<<six<<" "<<four<<" "<<matches+1<<" "<<hs<<endl;
                }
            }
            inf.close();
            ouf.close();
            remove("name.txt");
            rename("temp.txt","name.txt");

         }

};
 int search_player(string name,string team_name)
 {
     string n,c;
     int r,w,s,f,b,m,h;
     ifstream ouf("name.txt");
     while(ouf)
     {
         ouf>>n;
         ouf>>c;
         ouf>>r>>w>>b>>f>>s>>m>>h;
         if(n==name&&c==team_name)
            return 1;

     }

     return 0;

 }
 create_team()
 {
     int flag=0;
     string s,st;
     cout<<"Enter team name: ";
     cin>>s;
     getchar();
     ifstream inf("team.txt");
     while(inf)
     {
         inf>>st;
         if(s==st)
         {
             cout<<"This team is already exist"<<endl;
             flag=1;
             break;
         }
     }
     inf.close();
     if(flag==0)
     {

         ofstream ouf("team.txt",ios::app);
         ouf<<s<<endl;
         Team t(s);
         t.playing_xi();
         cout<<"team created sucessfully ";
     }
      system("pause");
     system("cls");

 }
 player_individual_status()
 {
      int flag=0;
  string n,c,st;
  int r,w,b,f,s,m,h;
  cout<<"Enter player name: ";
  cin>>st;
  ifstream inf("name.txt");
  while(inf)
  {
     inf>>n;
     inf>>c;
     inf>>r>>b>>w>>f>>s>>m>>h;
     if(st==n)
     {
         Player obj(n,c,r,b,w,f,s);
         obj.hs=h;
         obj.matches=m;
         obj.details();
         flag=1;
         break;
     }
  }
  if(flag==0)
    cout<<"No results"<<endl;
     system("pause");
     system("cls");
 }
 update_scorecard()
 {
          int flag1=0,flag=0;
     string s,st,str;
     cout<<"enter team1 name: ";
     cin>>s;
     cout<<"enter team2 name: ";
     cin>>st;
     getchar();
     ifstream inf("team.txt");
     while(inf)
     {
         inf>>str;
         if(st==str)
            flag1=1;
         if(s==str)
         {
             flag=1;
         }
     }
     inf.close();
     if(flag==0&&flag1==0)
     {
         ofstream ouf("team.txt",ios::app);
         ouf<<s<<endl;
         ouf<<st<<endl;
     }
     else if(flag==0)
     {
         ofstream ouf("team.txt",ios::app);
         ouf<<s<<endl;
     }
     else if(flag1==0)
     {
         ofstream ouf("team.txt",ios::app);
         ouf<<st<<endl;
     }
     Team t1(s),t2(st);
     t1.playing_xi();
      system("pause");
     system("cls");
     t2.playing_xi();
      system("pause");
     system("cls");
     t1.update_status();
      system("pause");
     system("cls");
     t2.update_status();
      system("pause");
     system("cls");
 }
 add_player()
 {
     int flag;
     string name,country,n,c;
     int r,w,b,f,s;
     cout<<"Enter name: ";
     cin>>name;
     cout<<"Enter country: ";
     cin>>country;
     flag=search_player(name,country);
     if(flag==1)
        cout<<"This player already exist";
     else{
     Player pl(name,country);
     ofstream ouf("name.txt",ios::app);
     ouf<<pl.name<<endl;
     ouf<<pl.country<<endl;
     ouf<<pl.run<<" "<<pl.ball_faced<<" "<<pl.wicket<<" "<<pl.six<<" "<<pl.four<<" "<<pl.hs<<endl;
     cout<<"The player successfully added to our recordbook"<<endl;
     }
     system("pause");
     system("cls");

 }

int main()
{
    while(1)
        {
    int a;
 cout<<"1.add a player"<<endl;
 cout<<"2.add a national team"<<endl;
 cout<<"3.player individual status"<<endl;
 cout<<"4.update a match scorecard"<<endl;
 cout<<"0.exit"<<endl;
 cout<<"please enter a key: ";
 cin>>a;
 system("cls");
 if(a==1)
 {
     add_player();
 }
 else if(a==2)
 {
     create_team();
 }
 else if(a==3)
 {
   player_individual_status();
 }
 else if(a==4)
 {
   update_scorecard();
 }
 else if(a==0)
    break;
    else
        cout<<"wrong keyword"<<endl;
    }


    return 0;
}
