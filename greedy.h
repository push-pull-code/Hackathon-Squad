#include <vector>
typedef long long ll;
using namespace std;
vector<bool> visited;
void visit(ll person,vector<vector<ll>> &conflict){
    visited[person]=1;
    for(auto x:conflict[person]){
        visited[x]=1;
    }
}
vector<ll> greedy(vector<pair<ll,ll>> &skill,vector<vector<ll>> &conflict){
    sort(skill.rbegin(),skill.rend());
    ll n=skill.size();
    visited.assign(n+1,0);
    ll ans=0;
    vector<ll> ans_skill;
    for(ll i=0;i<n;i++){ // 
        ll s=skill[i].first;
        ll person=skill[i].second;
        if(!visited[person]){
            ans+=s;
            ans_skill.push_back(person);
            visit(person,conflict);
        }
    }
    sort(ans_skill.begin(),ans_skill.end());//sorting of indics in incresing order 
    ans_skill.push_back(ans);
    return ans_skill;
}