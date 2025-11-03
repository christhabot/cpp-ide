#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll outputs[200005];
pair<ll,int> gapArray[200005];

int main()
{
    ll amounts, amountw;
    scanf("%lld %lld", &amounts, &amountw);

    ll temp = 0;
    for (int i = 0; i < amounts; i++)
    {
        ll currentValue;
        scanf("%lld", &currentValue);
        if (i > 0)
        {
            ll difference = currentValue - temp;
            gapArray[i - 1] = make_pair(difference, i - 1);
        }
        temp = currentValue;
    }
    sort(gapArray, gapArray + amounts - 1);
    gapArray[amounts - 1] = make_pair((ll)0, 0);

    ll processedGaps = 0;
    ll cumulativeSum = 0;
    ll minpref = 0;
    ll maxpref = 0;

    for (int qi = 0; qi < amountw; qi++)
    {
        ll wind;
        scanf("%lld", &wind);
        if (wind == 0) continue;

        cumulativeSum += wind;
        ll newMin = min(minpref, cumulativeSum);
        ll newMax = max(maxpref, cumulativeSum);
        ll span   = newMax - newMin;

        while (processedGaps < amounts - 1
               && gapArray[processedGaps].first <= span)
        {
            int pos = gapArray[processedGaps].second;
            outputs[pos] += maxpref;
            outputs[pos + 1] += llabs(minpref);
            ll overlap = gapArray[processedGaps].first - (maxpref - minpref);
            if (newMin == minpref)
                outputs[pos]     += overlap;
            else
                outputs[pos + 1] += overlap;

            processedGaps++;
        }

        minpref = newMin;
        maxpref = newMax;
    }
    while (processedGaps < amounts - 1)
    {
        int pos = gapArray[processedGaps].second;
        outputs[pos] += maxpref;
        outputs[pos + 1] += llabs(minpref);
        processedGaps++;
    }
    outputs[0] += llabs(minpref);
    outputs[amounts - 1] += maxpref;

    for (int i = 0; i < amounts; i++)
    {
        printf("%lld\n", outputs[i]);
    }

    return 0;
}
