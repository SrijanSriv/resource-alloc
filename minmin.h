#pragma once
#include<bits/stdc++.h>
using namespace std;
#define ll long long

namespace scheduler {
    class minmin {
        private:
            bool taskLeft(vector<pair<vector<ll>, ll>>& matrix);
            bool canPerformTask(vector<ll>& task, vector<ll>& pro);
            void performTask(vector<ll>& task, vector<ll>& pro);
            ll bestProcessor(ll t);
        public:
            ll n, m, r, allocs;
            vector<ll> alloc_time;
            vector<vector<ll>> estimated_time;
            vector<pair<vector<ll>, ll>> task_resource;
            vector<vector<ll>> pro_resource;
            minmin();
            minmin(vector<vector<ll>> et, vector<vector<ll>> tr, vector<vector<ll>> pr);
            void allocateTasks();
    };

    bool taskFinishedMinMin(vector<ll> v) {
        bool flag = true;
        for (auto& e : v) if (e == 1) {
            flag = false;
            break;
        }
        return flag;
    }

    const bool avgTimeComparator(pair<vector<ll>, ll>& a, pair<vector<ll>, ll>& b) {
        return a.second <= b.second;
    }

    minmin::minmin() {
        // n = 4; m = 3; r = 5; allocs = 0;
        srand(time(NULL));
        n = rand()%20 + 1;
        m = rand()%20 + 1;
        r = rand()%20 + 1;
        estimated_time.resize(n, vector<ll> (m, 0));
        task_resource.resize(n, {vector<ll> (r, 0), 0});
        pro_resource.resize(m, vector<ll> (r, 0));
        alloc_time.resize(m, 0);

        for (ll row = 0; row < n; row++) {
            for (ll col = 0; col < m; col++) {
                estimated_time[row][col] = rand()%20 + 1;
                task_resource[row].second += estimated_time[row][col];
            }
        }
        for (ll row = 0; row < n; row++) {
            for (ll col = 0; col < r; col++) {
                task_resource[row].first[col] = rand()%2;
            }
        }
        for (ll row = 0; row < m; row++) {
            for (ll col = 0; col < r; col++) {
                pro_resource[row][col] = rand()%2;
            }
        }

        // estimated_time = {{10, 21, 12},
        //                 {19, 12, 16},
        //                 {14, 4, 7},
        //                 {18, 16, 5}};

        // task_resource[0].first = {0, 1, 1, 0, 1};
        // task_resource[1].first = {1, 1, 1, 0, 1};
        // task_resource[2].first = {1, 0, 0, 1, 1};
        // task_resource[3].first = {1, 1, 0, 1, 0};
        // task_resource[0].second = 43;
        // task_resource[1].second = 47;
        // task_resource[2].second = 25;
        // task_resource[3].second = 39;
            
        // pro_resource = {{1, 0, 1, 1, 0},
        //                 {0, 1, 1, 0, 1},
        //                 {1, 1, 0, 1, 0}};
    }

    minmin::minmin(vector<vector<ll>> et, vector<vector<ll>> tr, vector<vector<ll>> pr) {
        n = et.size(); m = pr.size(); r = tr[0].size();

        allocs = 0;
        estimated_time = et;
        pro_resource = pr;
        alloc_time.resize(m, 0);
        task_resource.resize(n, {vector<ll> (r, 0), 0});

        for (ll row = 0; row < n; row++) {
            for (ll col = 0; col < r; col++) {
                task_resource[row].first[col] = tr[row][col];
            }
        }
        for (ll row = 0; row < n; row++) {
            for (ll col = 0; col < m; col++) {
                cin >> estimated_time[row][col];
                task_resource[row].second += et[row][col];
            }
        }
    }

    bool minmin::taskLeft(vector<pair<vector<ll>, ll>>& matrix) {
        for (auto& row : matrix) {
        for (auto& value : row.first) {
            if (value != 0) return true;
        }
    }
    return false;
    }

    bool minmin::canPerformTask(vector<ll>& task, vector<ll>& pro) {
        bool flag = false;
        for (ll itr = 0; itr < r; itr++) {
            if (pro[itr] == 1 && task[itr] == 1) flag = true; 
        }
        return flag;
    }

    ll minmin::bestProcessor(ll t) {
        ll pos = 0, pos_time = INT_MAX;
        for (ll itr = 0; itr < m; itr++) {
            if (estimated_time[t][itr] < pos_time
                && canPerformTask(task_resource[t].first, pro_resource[itr])) {
                pos_time = estimated_time[t][itr];
                pos = itr;
            }
        }
        return pos;
    }

    void minmin::performTask(vector<ll>& task, vector<ll>& pro) {
        allocs++;
        for (ll itr = 0; itr < r; itr++) {
            if (task[itr] == 1 && pro[itr] == 1) task[itr] = 0;
        }
    }

    void minmin::allocateTasks() {
        cout << "Initial Matrix:\n";
        for (ll row = 0; row < n; row++) {
                for (ll col = 0; col < r; col++) {
                    cout << task_resource[row].first[col] << ' ';
                }
                cout << '\n';
        }
        cout << '\n';
        sort(task_resource.begin(), task_resource.end(), avgTimeComparator);
        cout << "Matrix after avg time sorting:\n";
        for (ll row = 0; row < n; row++) {
                for (ll col = 0; col < r; col++) {
                    cout << task_resource[row].first[col] << ' ';
                }
                cout << '\n';
        }
        cout << '\n';

        ll p_itr = 0, counter = 0;
        allocs = 0;
        // for (ll i = 0; i < 5; i++) {
        while (taskLeft(task_resource)) {
            if (counter > 100) {
                cout << "\nThe processor matrix might not have all the resources required. Please check";
                break;
            }
            // allocating task
            for (ll t_itr = 0; t_itr < n; t_itr++) {
            if (taskFinishedMinMin(task_resource[t_itr].first)) continue;
                p_itr = bestProcessor(t_itr);
                cout << "Allocating task " << t_itr + 1 << " to processor " << p_itr + 1 << '\n';
                performTask(task_resource[t_itr].first, pro_resource[p_itr]);
                alloc_time[p_itr] += estimated_time[t_itr][p_itr];
            }

            counter++;
            cout << "Matrix after " << counter << " number(s) of iteration:\n";
            for (ll row = 0; row < n; row++) {
                for (ll col = 0; col < r; col++) {
                    cout << task_resource[row].first[col] << ' ';
                }
                cout << '\n';
            }
            cout << "Time assigned to each processor:\n";
            for (auto& val : alloc_time) cout << val << ' ';
            cout << "\n\n";
        }
        cout << "Number of allocations:\n" << allocs << "\n\n";
    }
}