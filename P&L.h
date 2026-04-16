#pragma once 
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "greedy.h"
typedef long long ll;
using namespace std;
// vector<bool> visited;
// void visit(ll person,vector<vector<ll>> &conflict){
//     visited[person]=1;
//     for(auto x:conflict[person]){
//         visited[x]=1;
//     }
// }
vector<ll> pl(vector<pair<ll,ll>> &skill,vector<vector<ll>> &conflict,unordered_map<ll,ll> &mpskill){
    ll n=skill.size();
    vector<pair<ll,ll>> plskill;
    vector<ll> ans_skill;
    visited.assign(n+1,0);
    for(auto &x:skill){
        ll s=x.first;
        ll t=x.second;
        for(auto &y:conflict[t]){
            s-=mpskill[y];
        }
        plskill.push_back({s,t});
    }// plskill p&l skill and indics
    sort(plskill.rbegin(),plskill.rend());
    ll ans=0;
    for(auto &x:plskill){
        ll person=x.second;
        ll s=mpskill[person];
        if(!visited[person]){
            ans+=s;
            ans_skill.push_back(person);
            visit(person,conflict);
        }
    }
    sort(ans_skill.begin(),ans_skill.end());
    ans_skill.push_back(ans);
    return ans_skill;
}