// done 8 September 2020
// solves Hacker Rank Maximum Subarray Sum
// https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
// Diffiulty Hard

// Some fun with modulo arithmetic

long maximumSum(vector<long> a, long m) {
    // go through a and get the cumulative
    // sum so far modulo m
    long cum[a.size()];
    cum[0]=a[0]%m;
    for (long aa=1; aa<a.size(); aa++) {
        cum[aa]=(cum[aa-1]+a[aa]%m)%m;
    }

    // The idea is to go through cum, and for every new
    // cumulative value look for the smallest higher value
    // that we have seen so far. That will give the two
    // cumulative values whose difference is closest to m
    // without going over m.
    std::set<long> seen; // stores cum values seen so far
    seen.insert(m); // starting at 0 equivalent to starting at m
    long retval = 0; // return value, max seen so far
    for (long aa=0; aa<a.size(); aa++) {
        // insert new value into set seen and return the iterator
        std::pair<std::set<long>::iterator,bool> ret;
        ret = seen.insert(cum[aa]);
        std::set<long>::iterator seenit=ret.first;
        // You are guaranteed to not have seen be the end
        // of the set because we've entered m into the set
        // and if this value of cum[aa] is 0 modulo m then
        // it will be entered as 0 not m. So can always iterate
        // seen.
        seenit++;
        retval = max(retval, m+cum[aa]-*seenit);
    }    
    return retval;
}


