// Done 9 Sep 2020
// Solves Hacker Rank Making Candies problem
//
// Difficulty Hard

// Fun problem, I thought of it as a question of the intersection of lines,
// where horizontal lines told me how high I had to get to either buy machines/workers,
// or when I reached the goal, and lines with slope m*w told me how many candies I
// would have after how many days.

long minimumPasses(long m, long w, long p, long n) {
    // Visualization: horizontal axis is days. Vertical axis is candies.
    // You have a horizontal line y=p and you're above it you can buy m or w.
    // You have another horizontal line y=n and if you're above it you're done.
    // Start with line y=(m*w)x, i.e. m*w is the slope of how many candies you can
    // make per day, i.e. y is candies and x is days. If n < p then you'll hit
    // your goal before being able to buy more m or w, so just compute the number of
    // days. Otherwise if p<n, every time you clear y=p you should buy as many of
    // m and w as you can, provided they pass the check below. Note you want to make
    // m and w as equal as possible in order to maximize their product.
    // The check is daysIfOld versus daysIfNew. The variable daysIfOld tells you how
    // many days it would take to finish if you didn't trade any candies for m and w.
    // The variable daysIfNew tells you how many days it would take if you did the max
    // trade. (If a trade is profitable at all, max trade is most profitable.) 
    // Visually you're comparing intersections with the line y=n: does getting a steeper
    // slope (m*w) pay off despite lowering y-intercept of your current line?
    long days = 0;
    long long candies = 0;
    while ( candies < n ) {
        // check for any overflow issues
        if ( w > LONG_MAX/m || m*w > n || m*w + candies > n ) { days++; break; }
        // if p>n then never in a position to buy m or w, so just calculate
        if (p > n) { if (n%(m*w)==0){return n/(m*w);} else {return n/(m*w)+1;}}
        // We know p<n. Accumulate candies until get p of them, then decide 
        // whether to buy or not. How many days until I can possibly buy? 
        long daysuntilcanbuy;
        if ((p-candies)%(m*w)==0) {daysuntilcanbuy=(p-candies)/(m*w);} else {daysuntilcanbuy=(p-candies)/(m*w)+1;} 
        // lets go forward daysuntilcanbuy days and figure if we trade candies for m,w
        // recall all these have to be integer calculations
        candies += daysuntilcanbuy * m * w;
        days += daysuntilcanbuy;
        // if happen to overshoot n, we're done
        if (candies > n) {return days;}
        // what would be the new values of m and w if I were to buy? 
        // Variable purchase tells me the total m and w I would buy this round.
        long purchase = candies / p ;
        // If I were to buy, calc how I would distribute them among m and w,
        // and thus what new values of m and w would be.
        long mold = m, wold = w;
        long mnew, wnew;
        if ( mold+purchase <= wold) { mnew = mold + purchase; wnew = wold; }
        else if ( wold+purchase <= mold) { wnew = wold + purchase; mnew = mold;}
        else {
            if ( (mold+wold+purchase)%2==0 ) {
                mnew = (mold+wold+purchase)/2;
                wnew = (mold+wold+purchase)/2;
            } else {
                mnew = (mold+wold+purchase)/2+1;
                wnew = (mold+wold+purchase)/2;
            }
        }
        // now that I have mold, wold, mnew, and wnew, should I buy?
        // How many days to reach n if keep mold and wold? If use mnew and wnew?
        double daysIfOld = days+1.0*(n-candies)/(1.0*mold*wold);
        double daysIfNew = days+1.0*(n-(candies-purchase*p)) / (1.0*mnew*wnew);
        if ( daysIfNew < daysIfOld ) {
            candies -= purchase*p;
            m = mnew;
            w = wnew;
        } else { // if won't buy, then just return how many days it will take
            return ceil(daysIfOld);
        }
    }
    return days;
}



