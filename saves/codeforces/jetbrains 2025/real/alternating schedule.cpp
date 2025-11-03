#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() 
{
    ll days, amountc;
    scanf("%lld %lld", &days, &amountc);
    
    ll alice = 0, bob = 0;
    ll prev_day = 0;
    int prev_walker = 0;
    
    for(int i = 0; i < amountc; i++)
    {
        ll mistake_day;
        scanf("%lld", &mistake_day);
        
        ll segment_days = mistake_day - prev_day - 1;
        
        if(segment_days > 0) 
        {
            int starter = 1 - prev_walker;
            
            if(starter == 0) 
            {
                alice += (segment_days + 1) / 2;
                bob += segment_days / 2;
                prev_walker = (segment_days % 2 == 1) ? 0 : 1;
            } 
            else 
            {
                bob += (segment_days + 1) / 2;
                alice += segment_days / 2;
                prev_walker = (segment_days % 2 == 1) ? 1 : 0;
            }
        }
        
        if(prev_walker == 0) 
        {
            alice++;
        } 
        else 
        {
            bob++;
        }
        
        prev_day = mistake_day;
    }
    
    ll remaining_days = days - prev_day;
    if(remaining_days > 0) 
    {
        int starter = 1 - prev_walker;
        
        if(starter == 0) 
        {
            alice += (remaining_days + 1) / 2;
            bob += remaining_days / 2;
        } 
        else 
        {
            bob += (remaining_days + 1) / 2;
            alice += remaining_days / 2;
        }
    }
    
    printf("%lld %lld\n", bob, alice);
    
    return 0;
}