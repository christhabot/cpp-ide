#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<vector<int>>> vec;

int thing = 1018, thing2 = 98;

int main()
{
    int res, res2, res3, sizeprev = 0, big = 0;
    // for(thing = 990; thing <= 1100; thing++)
    // {
        bool good;
        good = true;
        vec.assign(750, vector<vector<int>>(750, vector<int>(750, -1)));
        for(int i = 1; i <= 30000; i++)
        {
            res = i / thing + (i % thing) / thing2 + ((i % thing) % thing2);
            res2 = i / (thing-thing2) + (i % (thing-thing2)) / thing2 + ((i % (thing-thing2)) % thing2);
            res3 = i / (thing-thing2-1) + (i % (thing-thing2-1)) / (thing2-1) + ((i % (thing-thing2-1)) % (thing2-1));
            big = max(big, res);
            big = max(big, res2);
            if(vec[res][res2][res3] == -1 || true)
            {
                vec[res][res2][res3] = i;
            }
            else
            {
                return -1;
                cout << "no " << vec[res][res2][res3] << " " << i << "\n";
                cout << res << " " << res2 << "\n";
                good = false;
            }
            if(i == 1202)
            {
                // cout << res << " " << res2 << " " << res3 << "\n";
            }
        }
    // }


    // cout << "big: " << big << "\n";
    printf("? 3 %d %d 1\n", thing, thing2);
    fflush(stdout);
    scanf("%d", &res);
    printf("? 3 %d %d 1\n", thing - thing2, thing2);
    fflush(stdout);
    scanf("%d", &res2);
    printf("? 3 %d %d 1\n", thing - thing2-1, thing2 - 1);
    fflush(stdout);
    scanf("%d", &res3);
    if(res > 400 || res2 > 400 || res3 > 400)
        return 10;
    printf("! %d\n", vec[res][res2][res3]);
}
