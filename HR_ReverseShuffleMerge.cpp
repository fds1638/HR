// done 7 sep 2020

#include <bits/stdc++.h>

using namespace std;

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {

    std::map<char,int> cmap;
    string retval="";
    int useit[s.size()];
    for (int ss=0; ss<s.size(); ss++) {
        useit[ss]=0;
        if (cmap.find(s[ss])!=cmap.end()) { cmap[s[ss]]++;}
        else { cmap[s[ss]]=1; }
    }
    //std::cout<<"cmap.size() "<<cmap.size()<<endl;

    std::map<char,pair<int,int>> letters;
    std::map<char,int>::iterator cmapit;
    for (cmapit=cmap.begin(); cmapit!=cmap.end(); cmapit++) {
        cout<<cmapit->first<<" "<<cmapit->second<<endl;
        letters[cmapit->first] = {cmapit->second/2,0};
    }        

    int numused = 0;
    int lastused = s.size();
    std::map<char,pair<int,int>>::iterator preferred = letters.begin(); 
    for (int ss=s.size()-1; ss>=0; ss--) {
        if (s[ss]==preferred->first) { //if preferred use it if can
            if (preferred->second.first>0) {
                useit[ss]=1; 
                numused++;
                lastused = ss;
                preferred->second.first--;
                if (preferred->second.first==0) { preferred++; } //next letter
            }
        } 
        else {
            if (letters[s[ss]].second<cmap[s[ss]]/2) { letters[s[ss]].second++; 
            if (s[ss]=='d') {cout<<s[ss]<<" "<<ss<<" "<<letters[s[ss]].second<<endl;}
            }
            else if (letters[s[ss]].second==cmap[s[ss]]/2) { 
                cout<<"must use "<<s[ss]<<" "<<ss<<" lastused "<<lastused<<" s[lastused] "<<s[lastused]<<endl;
                // need to backtrack, use all that I can
                stack<int> bt; //bt = backtrack
                for (int jj=ss+1; jj<lastused; jj++) {
                    if (s[jj]<s[ss]&&(bt.empty()||s[jj]<=s[bt.top()]) &&letters[s[jj]].first>0) {
                        //cout<<"push "<<jj<<" "<<s[jj]<<endl;
                        bt.push(jj);
                    }
                }
                //cout<<"bt.size "<<bt.size()<<" bt.top "<< bt.top() <<endl;
                if ( bt.empty() ) {
                    int kk = ss;
                    while ( s[kk]>=s[ss]||useit[kk]==1) {kk++;}
                    bool preempt = false;
                    for (int ll=kk; ll>ss; ll--) {
                        if (useit[ll]==1&&s[ll]<s[kk]) { preempt = true; }
                    }
                    if (!preempt&&s[kk]<s[ss]&&letters[s[kk]].first>0) {
                        useit[kk]=1; 
                        numused++;
                        letters[s[kk]].first--; //use it
                        letters[s[kk]].second--;  //unsee it
                    }
                    //cout<<"prev prev "<<s[kk]<<" "<<kk<<" "<<" a seen "<<letters['a'].second<<" b seen "<<letters['b'].second<<" c seen "<<letters['c'].second<<" d seen "<<letters['d'].second<<endl;
                }
                while ( !bt.empty() ) {
                    int jj = bt.top();
                    bt.pop();
                    if (s[jj]<s[ss]&&letters[s[jj]].first>0) {
                        useit[jj]=1; 
                        numused++;
                        letters[s[jj]].first--; //use it
                        letters[s[jj]].second--;  //unsee it
                    }
                }
                if (letters[s[ss]].first>0) {
                useit[ss]=1; 
                numused++;
                letters[s[ss]].first--; 
                }
                lastused = ss;
                /*
                for (int jj=lastused-1; jj>ss; jj--) {
                    //cout<<"backtrack "<<s[jj]<<" "<<jj<<" have left "<<letters[s[jj]].first<<" less? "<<lessthan<<endl;
                    
                    if (s[jj]<s[ss]&&letters[s[jj]].first>0) {
                        useit[jj]=1; 
                        letters[s[jj]].first--; //use it
                        letters[s[jj]].second--;  //unsee it
                    }
                }
                */
            }
        }
        if (useit[ss]==1) cout<<s[ss]<<" ";
        if (numused==s.size()/2) { break; }
    }
    cout<<endl;

    for (int ss=0; ss<s.size(); ss++) {
        if (useit[ss]==1) { retval+=s[ss]; }
    }
    reverse(retval.begin(), retval.end());
    return retval;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = reverseShuffleMerge(s);

    fout << result << "\n";

    fout.close();

    return 0;
}



