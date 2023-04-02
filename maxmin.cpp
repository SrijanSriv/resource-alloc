#include "maxmin.h"

namespace scheduler {
    bool taskFinishedMaxMin(vector<ll> v) {
        bool flag = true;
        for (auto& e : v) if (e == 1) {
            flag = false;
            break;
        }
        return flag;
    }

    const bool avgTimeComparatorReverse(pair<vector<ll>, ll>& a, pair<vector<ll>, ll>& b) {
        return a.second >= b.second;
    }

    maxmin::maxmin() {
        n = 4; m = 3; r = 5; allocs = 0;
        estimated_time.resize(n, vector<ll> (m, 0));
        task_resource.resize(n, {vector<ll> (r, 0), 0});
        pro_resource.resize(m, vector<ll> (r, 0));
        alloc_time.resize(m, 0);

        estimated_time = {{10, 21, 12},
                        {19, 12, 16},
                        {14, 4, 7},
                        {18, 16, 5}};

        task_resource[0].first = {0, 1, 1, 0, 1};
        task_resource[1].first = {1, 1, 1, 0, 1};
        task_resource[2].first = {1, 0, 0, 1, 1};
        task_resource[3].first = {1, 1, 0, 1, 0};
        task_resource[0].second = 43;
        task_resource[1].second = 47;
        task_resource[2].second = 25;
        task_resource[3].second = 39;
            
        pro_resource = {{1, 0, 1, 1, 0},
                        {0, 1, 1, 0, 1},
                        {1, 1, 0, 1, 0}};
    }

    maxmin::maxmin(vector<vector<ll>> et, vector<vector<ll>> tr, vector<vector<ll>> pr) {
        n = et.size(); m = pr.size(); r = tr[0].size();

        allocs = 0;
        estimated_time = et;
        pro_resource = pr;
        alloc_time.resize(m, 0);

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

    bool maxmin::taskLeft(vector<pair<vector<ll>, ll>>& matrix) {
        for (auto& row : matrix) {
        for (auto& value : row.first) {
            if (value != 0) return true;
        }
    }
    return false;
    }

    bool maxmin::canPerformTask(vector<ll>& task, vector<ll>& pro) {
        bool flag = false;
        for (ll itr = 0; itr < r; itr++) {
            if (pro[itr] == 1 && task[itr] == 1) flag = true; 
        }
        return flag;
    }

    ll maxmin::bestProcessor(ll t) {
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

    void maxmin::performTask(vector<ll>& task, vector<ll>& pro) {
        allocs++;
        for (ll itr = 0; itr < r; itr++) {
            if (task[itr] == 1 && pro[itr] == 1) task[itr] = 0;
        }
    }

    void maxmin::allocateTasks() {
        cout << "Initial Matrix:\n";
        for (ll row = 0; row < n; row++) {
                for (ll col = 0; col < r; col++) {
                    cout << task_resource[row].first[col] << ' ';
                }
                cout << '\n';
        }
        cout << '\n';
        sort(task_resource.begin(), task_resource.end(), avgTimeComparatorReverse);
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
            if (counter > 100) break;
            // allocating task
            for (ll t_itr = 0; t_itr < n; t_itr++) {
                if (taskFinishedMaxMin(task_resource[t_itr].first)) continue;
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