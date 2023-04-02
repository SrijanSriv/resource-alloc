#pragma once
#include<bits/stdc++.h>
using namespace std;
#define ll long long

namespace scheduler {
    class fcfs {
        private:
            bool taskLeft(vector<vector<ll>>& matrix);
            bool canPerformTask(vector<ll>& task, vector<ll>& pro);
            void performTask(vector<ll>& task, vector<ll>& pro);
        public:
            ll n, m, r, allocs;
            vector<ll> alloc_time;
            vector<vector<ll>> estimated_time;
            vector<vector<ll>> task_resource;
            vector<vector<ll>> pro_resource;
            fcfs();
            fcfs(vector<vector<ll>> et, vector<vector<ll>> tr, vector<vector<ll>> pr);
            void allocateTasks();
    };
}