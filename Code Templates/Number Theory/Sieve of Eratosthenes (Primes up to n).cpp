/*********************************************************************************************************
MUST READ!
    (i)     Call the parameter from appropriate point - before or after tcl.

    (ii)    Pass the appropriate parameter into the function. Normally, ≤ 1e7 is safe.
            For an additional reference beside the problem statement, the following will help much -
            
            2     3     5     7    11    13    17    19    23    29 [10th prime]
           31    37    41    43    47    53    59    61    67    71
           73    79    83    89    97   101   103   107   109   113
          127   131   137   139   149   151   157   163   167   173
          179   181   191   193   197   199   211   223   227   229 [50th prime]
          233   239   241   251   257   263   269   271   277   281
          283   293   307   311   313   317   331   337   347   349
          353   359   367   373   379   383   389   397   401   409
          419   421   431   433   439   443   449   457   461   463
          467   479   487   491   499   503   509   521   523   541 [100th prime]
          547   557   563   569   571   577   587   593   599   601
          607   613   617   619   631   641   643   647   653   659
          661   673   677   683   691   701   709   719   727   733
          739   743   751   757   761   769   773   787   797   809
          811   821   823   827   829   839   853   857   859   863
          877   881   883   887   907   911   919   929   937   941
          947   953   967   971   977   983   991   997  1009  1013
         1019  1021  1031  1033  1039  1049  1051  1061  1063  1069
         1087  1091  1093  1097  1103  1109  1117  1123  1129  1151
         1153  1163  1171  1181  1187  1193  1201  1213  1217  1223 [200th prime]
         1229  1231  1237  1249  1259  1277  1279  1283  1289  1291
         1297  1301  1303  1307  1319  1321  1327  1361  1367  1373
         1381  1399  1409  1423  1427  1429  1433  1439  1447  1451
         1453  1459  1471  1481  1483  1487  1489  1493  1499  1511
         1523  1531  1543  1549  1553  1559  1567  1571  1579  1583
         1597  1601  1607  1609  1613  1619  1621  1627  1637  1657
         1663  1667  1669  1693  1697  1699  1709  1721  1723  1733
         1741  1747  1753  1759  1777  1783  1787  1789  1801  1811
         1823  1831  1847  1861  1867  1871  1873  1877  1879  1889
         1901  1907  1913  1931  1933  1949  1951  1973  1979  1987 [300th prime]
         1993  1997  1999  2003  2011  2017  2027  2029  2039  2053
         2063  2069  2081  2083  2087  2089  2099  2111  2113  2129
         2131  2137  2141  2143  2153  2161  2179  2203  2207  2213
         2221  2237  2239  2243  2251  2267  2269  2273  2281  2287
         2293  2297  2309  2311  2333  2339  2341  2347  2351  2357
         2371  2377  2381  2383  2389  2393  2399  2411  2417  2423
         2437  2441  2447  2459  2467  2473  2477  2503  2521  2531
         2539  2543  2549  2551  2557  2579  2591  2593  2609  2617
         2621  2633  2647  2657  2659  2663  2671  2677  2683  2687
         2689  2693  2699  2707  2711  2713  2719  2729  2731  2741 [400th prime]
         2749  2753  2767  2777  2789  2791  2797  2801  2803  2819
         2833  2837  2843  2851  2857  2861  2879  2887  2897  2903
         2909  2917  2927  2939  2953  2957  2963  2969  2971  2999
         3001  3011  3019  3023  3037  3041  3049  3061  3067  3079
         3083  3089  3109  3119  3121  3137  3163  3167  3169  3181
         3187  3191  3203  3209  3217  3221  3229  3251  3253  3257
         3259  3271  3299  3301  3307  3313  3319  3323  3329  3331
         3343  3347  3359  3361  3371  3373  3389  3391  3407  3413
         3433  3449  3457  3461  3463  3467  3469  3491  3499  3511
         3517  3527  3529  3533  3539  3541  3547  3557  3559  3571 [500th prime]


    (iii)   After calling the function, the vector<int>primes is ready to use.
            Remember that, it is declared globally.
            Remember that, the elements are distinct.
            Remember that, it is sorted in non-decreasing order - more precisely in ascending order.

    (iv)    Suppose you need a prime beyond the above list - say 550th prime.
            That is cout<<primes[549] // 1 less for zero indexing of vector.
            But ensure the parameter to pass is sufficient corresponding to the actual value of that prime.

    (v)     Call this function EXACTLY ONCE. It appends to the global vector<int>primes
            without clearing it first - calling it twice will produce duplicate entries.

    (vi)    Valid for n >= 2. Passing n < 2 is safely handled (primes stays empty),
            no undefined behavior.

*********************************************************************************************************/ 

#include<bits/stdc++.h>

using namespace std;

#define tourist int main(){ios::sync_with_stdio(0);cin.tie(0);  // tourist - fast input output
#define Ace_Azimuth_Aviator return 0;}                          // Ace_Azimuth_Aviator - return 0;

#define css <<' '                                               // css - continuous single space
#define cnl <<'\n'                                              // cnl - continuous new line
#define pnl cout<<'\n';                                         // pnl - print new line
#define tcl int t;cin>>t;while(t--){                            // tcl - test case loop
#define tnl if(t)pnl}                                           // tnl - testcase new line

#define pno cout<<"NO";                                         // pno - print NO
#define pye cout<<"YES";                                        // pye - print YES
#define pny ?cout<<"NO":cout<<"YES";                            // pny - print NO/YES
#define pyn ?cout<<"YES":cout<<"NO";                            // pyn - print YES/NO

#define pze cout<<0;                                            // pze - print 0
#define pon cout<<1;                                            // pon - print 1
#define pzo ?cout<<0:cout<<1;                                   // pzo - print 0/1
#define poz ?cout<<1:cout<<0;                                   // poz - print 1/0

#define pmo cout<<-1;                                           // pmo - print minus one

#define bat bool ans=true;                                      // bat - boolean answer true
#define baf bool ans=false;                                     // baf - boolean answer false
#define atb {ans=true;break;}                                   // atb - answer true break
#define afb {ans=false;break;}                                  // afb - answer false break

#define lli long long                                           // lli - long long
#define imx INT_MAX                                             // imx - INT_MAX
#define imn INT_MIN                                             // imn - INT_MIN
#define con const int c=1e9                                     // con - constant
#define mod 998244353                                           // mod - modular arithmetic

#define vin(a,n) vector<int>a(n);for(auto&x:a)cin>>x;           // vin - vector int input
#define vlo(a,n) vector<lli>a(n);for(auto&x:a)cin>>x;           // vlo - vector long long input

#define all(a) a.begin(),a.end()                                // all(a) - all elements of the container a
#define rall(a) a.rbegin(),a.rend()                             // rall(a) - all elements of the container a in reverse order
#define allc(a) a.cbegin(), a.cend()                            // allc(a) - all elements of the const container a
#define rallc(a) a.crbegin(), a.crend()                         // rallc(a) - all elements of the const container a in reverse order

#define pub(a,x) a.push_back(x)                                 // pub(a,x) - push back x in container a
#define emb(a,...) a.emplace_back(__VA_ARGS__)                  // emb(a,...) - emplace back argument(s) in the container a

#define lob lower_bound                                         // lob - lower_bound
#define upb upper_bound                                         // upb - upper_bound

#define l2c(x) (int)ceil(log2(x))                               // l2c(x) - log2(x) rounded up

/*********************Perhaps we have to copy from the next line*********************/
vector<int>primes;

void GetPrimes(int n){
    if(n<2)
        return;

    vector<bool>isPrime(n+1,true);
    isPrime[0]=isPrime[1]=false;

    for(int i{2};1ll*i*i<=n;++i)
        if(isPrime[i])
            for(int j{i*i};j<=n;j+=i)
                isPrime[j]=false;

    for(int i{2};i<=n;++i)
        if(isPrime[i])
            emb(primes,i);
}
/*********************Perhaps we have to copy up to the previous line*********************/

tourist

/************************Perhaps we have to copy from the next line************************/
GetPrimes(1e7);
/*********************Perhaps we have to copy up to the previous line*********************/

tcl

tnl
Ace_Azimuth_Aviator
