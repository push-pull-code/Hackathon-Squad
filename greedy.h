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
ll greedy(vector<pair<ll,ll>> &skill,vector<vector<ll>> &conflict){
    sort(skill.rbegin(),skill.rend());
    ll n=skill.size();
    visited.assign(n+1,0);
    ll ans=0;
    for(ll i=0;i<n;i++){ // 
        ll s=skill[i].first;
        ll person=skill[i].second;
        if(!visited[person]){
            ans+=s;
            visit(person,conflict);
        }
    }
    return ans;
}