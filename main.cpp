#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;

struct Candidate {
    ll total_skill;
    vector<ll> selected_indices;
};

Candidate local_search(const vector<ll>& initial_set, const vector<pair<ll, ll>>& skill, const vector<vector<ll>>& conflict, ll n) {
    vector<bool> in_set(n + 1, false);
    ll current_sum = 0;
    for (ll u : initial_set) {
        in_set[u] = true;
        current_sum += skill[u - 1].first;
    }

    bool improved = true;
    int max_passes = 10;
    while (improved && max_passes--) {
        improved = false;
        
        for (ll u = 1; u <= n; ++u) {
            if (!in_set[u]) {
                bool has_neighbor = false;
                for (ll v : conflict[u]) {
                    if (in_set[v]) {
                        has_neighbor = true;
                        break;
                    }
                }
                if (!has_neighbor) {
                    in_set[u] = true;
                    current_sum += skill[u - 1].first;
                    improved = true;
                }
            }
        }

        for (ll u = 1; u <= n; ++u) {
            if (!in_set[u]) {
                ll neighbor_in_set = 0;
                ll count = 0;
                for (ll v : conflict[u]) {
                    if (in_set[v]) {
                        count++;
                        neighbor_in_set = v;
                        if (count > 1) break;
                    }
                }
                if (count == 1) {
                    ll u_weight = skill[u - 1].first;
                    ll v_weight = skill[neighbor_in_set - 1].first;
                    if (u_weight > v_weight) {
                        in_set[neighbor_in_set] = false;
                        in_set[u] = true;
                        current_sum += (u_weight - v_weight);
                        improved = true;
                    }
                }
            }
        }

        for (ll u = 1; u <= n; ++u) {
            if (!in_set[u]) {
                ll n1 = 0, n2 = 0;
                ll count = 0;
                for (ll v : conflict[u]) {
                    if (in_set[v]) {
                        count++;
                        if (count == 1) n1 = v;
                        else if (count == 2) n2 = v;
                        else break;
                    }
                }
                if (count == 2) {
                    ll u_weight = skill[u - 1].first;
                    ll w1 = skill[n1 - 1].first;
                    ll w2 = skill[n2 - 1].first;
                    if (u_weight > w1 + w2) {
                        in_set[n1] = false;
                        in_set[n2] = false;
                        in_set[u] = true;
                        current_sum += (u_weight - w1 - w2);
                        improved = true;
                    }
                }
            }
        }
    }

    vector<ll> final_indices;
    for (ll u = 1; u <= n; ++u) {
        if (in_set[u]) {
            final_indices.push_back(u);
        }
    }
    return {current_sum, final_indices};
}

vector<ll> run_greedy_skill(vector<pair<ll, ll>> skill_list, const vector<vector<ll>>& conflict, ll n) {
    sort(skill_list.rbegin(), skill_list.rend());
    vector<bool> visited(n + 1, false);
    vector<ll> selected;
    for (auto& p : skill_list) {
        ll u = p.second;
        if (!visited[u]) {
            selected.push_back(u);
            visited[u] = true;
            for (ll v : conflict[u]) visited[v] = true;
        }
    }
    return selected;
}

vector<ll> run_greedy_ratio(const vector<pair<ll, ll>>& skill_list, const vector<vector<ll>>& conflict, ll n, double alpha) {
    vector<pair<double, ll>> score_list;
    for (auto& p : skill_list) {
        ll weight = p.first;
        ll u = p.second;
        double score = (double)weight / (1.0 + alpha * conflict[u].size());
        score_list.push_back({score, u});
    }
    sort(score_list.rbegin(), score_list.rend());
    vector<bool> visited(n + 1, false);
    vector<ll> selected;
    for (auto& p : score_list) {
        ll u = p.second;
        if (!visited[u]) {
            selected.push_back(u);
            visited[u] = true;
            for (ll v : conflict[u]) visited[v] = true;
        }
    }
    return selected;
}

vector<ll> run_dynamic_greedy(const vector<pair<ll, ll>>& skill_list, const vector<vector<ll>>& conflict, ll n) {
    vector<ll> deg(n + 1);
    for (ll i = 1; i <= n; ++i) deg[i] = conflict[i].size();
    vector<bool> deleted(n + 1, false);
    
    priority_queue<pair<double, ll>> pq;
    vector<ll> weights(n + 1);
    for (auto& p : skill_list) {
        weights[p.second] = p.first;
        pq.push({(double)p.first / (1.0 + deg[p.second]), p.second});
    }
    
    vector<ll> selected;
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        double score = top.first;
        ll u = top.second;
        
        if (deleted[u]) continue;
        
        double current_score = (double)weights[u] / (1.0 + deg[u]);
        if (score < current_score - 1e-9) {
            pq.push({current_score, u});
            continue;
        }
        
        selected.push_back(u);
        deleted[u] = true;
        for (ll v : conflict[u]) {
            if (!deleted[v]) {
                deleted[v] = true;
                for (ll w : conflict[v]) {
                    if (!deleted[w]) {
                        deg[w]--;
                        pq.push({(double)weights[w] / (1.0 + deg[w]), w});
                    }
                }
            }
        }
    }
    return selected;
}

vector<ll> run_pl(const vector<pair<ll, ll>>& skill_list, const vector<vector<ll>>& conflict, ll n) {
    vector<ll> weights(n + 1);
    for (auto& p : skill_list) weights[p.second] = p.first;
    
    vector<pair<ll, ll>> plskill;
    for (auto& p : skill_list) {
        ll s = p.first;
        ll u = p.second;
        for (ll v : conflict[u]) {
            s -= weights[v];
        }
        plskill.push_back({s, u});
    }
    sort(plskill.rbegin(), plskill.rend());
    vector<bool> visited(n + 1, false);
    vector<ll> selected;
    for (auto& p : plskill) {
        ll u = p.second;
        if (!visited[u]) {
            selected.push_back(u);
            visited[u] = true;
            for (ll v : conflict[u]) visited[v] = true;
        }
    }
    return selected;
}

void solve() {
    ll n, m;
    if (!(cin >> n >> m)) return;
    vector<pair<ll, ll>> skill(n);
    vector<vector<ll>> conflict(n + 1, vector<ll>());
    for (ll i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        skill[i - 1] = {x, i};
    }
    for (ll i = 1; i <= m; ++i) {
        ll u, v;
        cin >> u >> v;
        conflict[u].push_back(v);
        conflict[v].push_back(u);
    }

    Candidate best_candidate = {-1, {}};

    auto update_best = [&](const vector<ll>& initial_set) {
        Candidate cand = local_search(initial_set, skill, conflict, n);
        if (cand.total_skill > best_candidate.total_skill) {
            best_candidate = cand;
        }
    };

    update_best(run_greedy_skill(skill, conflict, n));
    update_best(run_greedy_ratio(skill, conflict, n, 0.5));
    update_best(run_greedy_ratio(skill, conflict, n, 1.0));
    update_best(run_greedy_ratio(skill, conflict, n, 2.0));
    update_best(run_dynamic_greedy(skill, conflict, n));
    update_best(run_pl(skill, conflict, n));

    cout << best_candidate.total_skill << "\n";
    for (size_t i = 0; i < best_candidate.selected_indices.size(); ++i) {
        cout << best_candidate.selected_indices[i] << (i + 1 == best_candidate.selected_indices.size() ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}