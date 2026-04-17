#pragma once 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "greedy.h"
typedef long long ll;
using namespace std;

vector<ll> block(vector<pair<ll,ll>> &skill,vector<vector<ll>> &conflict,unordered_map<ll,ll> &mpskill){
    ll n=skill.size();
    vector<pair<ll,ll>> plskill;
    vector<ll> ans_skill;
    visited.assign(n+1,0);
    for(auto &x:skill){
        ll s=x.first;
        ll person=x.second;
        s/=(1+2*conflict[person].size());
        plskill.push_back({s,person});
    }
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