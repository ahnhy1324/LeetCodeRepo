/****
1925. Count Square Sum Triples
Solved
Easy
Topics
conpanies icon
Companies
Hint
A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.
Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.
Example 1:
Input: n = 5
Output: 2
Explanation: The square triples are (3,4,5) and (4,3,5).
Example 2:
Input: n = 10
Output: 4
Explanation: The square triples are (3,4,5), (4,3,5), (6,8,10), and (8,6,10).
Constraints:
1 <= n <= 250
******/ 
int table[255]={0};
int prime[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173};
int countTriples(int n) {
    int maximum = (n*10000)/14142;
    int cnt = 0;
    int sum=0;
    int tmp = 0;
    int indexer;
    for(int index = 0; index <= 250; index++)
    {
        table[index] = index * index;
    }
    for( int i = 0 ; prime[i] <= maximum ; i++)
    {
        indexer= (n-prime[i]);
        for ( int j = 1 ; j <= indexer; j++)
        {
            tmp = (prime[i] + j);
            int q = 0;
            for(q = i; q != 0 ; q--)
            {
                if((tmp%prime[q-1])==0)break;
            }
            if(q)break;
            sum = table[prime[i]] + table[tmp];
            if( sum <= table[n])
            {
                for(int index = 0; index < n; index++)
                {
                    if( sum == table[index+1])
                    {
                        cnt+=n/(sum);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    return cnt*2;
}