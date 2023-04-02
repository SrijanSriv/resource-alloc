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
}