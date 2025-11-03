#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> nums;
priority_queue<int> pq;
vector<ll> answers;
vector<bool> answered;

int main() {
    bool first;
    int amount, amountsiz, size, temp, idx;
    scanf("%d %d", &amount, &amountsiz);
    nums.resize(amount);
    answers.assign(amount+1, -1);
    answered.assign(amount+1, false);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &nums[i]);
    }
    for(int j = 0; j < amountsiz; j++)
    {
        scanf("%d", &size);
        if(answered[size])
        {
            printf("%lld\n", answers[size]);
            continue;
        }
        while(!pq.empty()) pq.pop();
        first = false;
        for(int i = 0; i < size && i < amount; i++)
        {
            pq.push(nums[i]);
        }
        ll alice_score = 0, bob_score = 0;
        int next_idx = size;
        bool alice_turn = true;
        
        while(!pq.empty()) {
            int taken = pq.top();
            pq.pop();
            
            if(alice_turn) {
                alice_score += taken;
            } else {
                bob_score += taken;
            }
            
            if(next_idx < amount) {
                pq.push(nums[next_idx]);
                next_idx++;
            }
            
            alice_turn = !alice_turn;
        }
        answered[size] = true;
        answers[size] = alice_score-bob_score;
        printf("%lld\n", alice_score-bob_score);
    }
}