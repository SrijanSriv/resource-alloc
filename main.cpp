#include <bits/stdc++.h>
#define ll long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
#include "fcfs.h"
#include "minmin.h"
#include "maxmin.h"


int main() {
    IOS;
    /* template to take input from user
    ll n, m, r;
    vector<vector<ll>> estimated_time;
    vector<vector<ll>> task_resource;
    vector<vector<ll>> pro_resource;
    vector<ll> alloc_time;
    cin >> n >> m >> r;
    srand(time(NULL));
    estimated_time.resize(n, vector<ll> (m, 0));
    task_resource.resize(n, vector<ll> (r, 0));
    pro_resource.resize(m, vector<ll> (r, 0));

    // taking matices input
    for (ll row = 0; row < n; row++) {
        for (ll col = 0; col < m; col++) {
            cin >> estimated_time[row][col];
        }
    }
    for (ll row = 0; row < n; row++) {
        for (ll col = 0; col < r; col++) {
            cin >> task_resource[row][col];
        }
    }
    for (ll row = 0; row < m; row++) {
        for (ll col = 0; col < r; col++) {
            cin >> pro_resource[row][col];
        }
    }
    */

    auto fcfsrunner = new scheduler::fcfs();
    fcfsrunner->allocateTasks();

    delete fcfsrunner;

    return 0;
}