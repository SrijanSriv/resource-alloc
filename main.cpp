#include <bits/stdc++.h>
#define ll long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
#include "fcfs.h"
#include "minmin.h"
#include "maxmin.h"


int main() {
    IOS;
    auto fcfsrunner = new scheduler::fcfs();
    fcfsrunner->allocateTasks();

    delete fcfsrunner;

    return 0;
}