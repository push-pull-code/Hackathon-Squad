#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "greedy.h"
#include "P&L.h"
typedef long long ll;
using namespace std;
//checking answer
// for(auto &x:indics_skill){
//     for(auto &y:x)cout<<y<<" ";
//     cout<<endl;
// }
int main(){
    ll n,m;cin>>n>>m;
    vector<pair<ll,ll>> skill; // it is zero index but person 1 to n;
    vector<vector<ll>> conflict(n+1,vector<ll> ());
    vector<vector<ll>> indics_skill;
    for(ll i=1;i<=n;i++){
        ll x;cin>>x;
        skill.push_back({x,i});
    }
    for(ll i=1;i<=m;i++){ // take care of empty vector
        ll x,y;cin>>x>>y;
        conflict[x].push_back(y);
        conflict[y].push_back(x);
    } 
    //greedy approach section
    indics_skill.push_back(greedy(skill,conflict)); // skill is sort in decreased
    // indics_skill last position is total skill and others are person indics
    //P&L approach
    unordered_map <ll,ll> mpskill;
    for(auto &x:skill){
        mpskill[x.second]=x.first;
    }
    indics_skill.push_back(pl(skill,conflict,mpskill));

}