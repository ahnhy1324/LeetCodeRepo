
#include <stdbool.h>
/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).
Example 1:
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:
Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:
Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Constraints:
1 <= s.length <= 20
1 <= p.length <= 20
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match
*/
#include <stdlib.h>
typedef struct TREE_TYPE{
    char val[20];
    int length;
    int rp;
    bool isWildcard;
    struct TREE_TYPE * backward;
    struct TREE_TYPE * next;
} Tree;

void ParsePattern(char*p , Tree* root)
{
    Tree* curr = root;
    while(*p != '\0')
    {
        if(*p == '.')
        {
            curr->isWildcard = true;
            curr->val[0] = '.';
            curr->length = 1;
            curr->rp = 0;
            if( *(p+1) == '*')
            {
                curr->isWildcard = true;
                curr->val[0] = *p;
                curr->length = 20;// max length
                curr->rp = 0;
                p++;
            }
            curr->next = malloc(sizeof(Tree));
            *curr->next = (Tree){0};
            curr->next->backward = curr;
            curr = curr->next;
        }
        else
        {
            curr->isWildcard = false;
            curr->val[0] = *p;
            curr->length = 1;
            curr->rp = 0;
            if( *(p+1) == '*')
            {
                curr->isWildcard = true;
                curr->val[0] = *p;
                curr->length = 20;// max length
                curr->rp = 0;
                p++;
            }
            curr->next = malloc(sizeof(Tree));
            *curr->next = (Tree){0};
            curr->next->backward = curr;
            curr = curr->next;
        }

        p++;
    }
}
/// @brief match string with pattern. if match return true else false
/// @param s 
/// @param Pattern 
/// @param length
/// @return result
bool MatchPattern(char* s, Tree* Pattern, int length)
{
    int currlen = 0;
    bool result = true;//true start
    Tree* curr= Pattern;// point to pattern head
    while(*s != '\0')// traverse string
    {
        currlen++;
        if(curr->isWildcard == true)// wildcard match
        {
            curr->rp++;
            if(( *(s+1) != *(curr->val)))
            {
                curr = curr->next;
            }
            else if(( *(s+1) == *(curr->val)))
            {

            }
            if(curr->next != NULL && curr->next->val[0]==*(s+1))
            {
                curr = curr->next;
            }
        }
        else
        {
            if(*s != *(curr->val))
            {
                if( curr->backward != NULL && curr->backward->isWildcard == true)
                {
                    
                    curr->backward->rp =0;
                    s-= curr->rp;
                    curr->rp =0;
                    curr = curr->backward;
                    continue;
                }
                else
                {
                    result = false;
                    break;
                }

            }
            curr->rp++;
        }
        s++;
        if( curr->rp >= curr->length)
        {
            curr = curr->next;
            if( curr == NULL && *s != '\0')
            {
                result = false;
            }
        }
        if( curr == NULL)
        {
            if(  *s == '\0' )result = true;
            else result = false;
            break;
        }
    }
    return result;
}

bool isMatch(char* s, char* p) {
    int len = 0;
    Tree * root;
    root = (Tree *)malloc(sizeof(Tree));
    * root = (Tree){0};
    ParsePattern(p, root);
    char * start = s;
    while( *s != '\0')
    {
        len++;
        s++;
        if(len >20 )break;
    }
     return MatchPattern(start, root, len);
}