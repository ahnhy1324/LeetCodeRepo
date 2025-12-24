/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.
 */
struct ListNode* pKList[5000];
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    int nPeriod = 0;
    struct ListNode* pPointerStart  = NULL;
    struct ListNode* pTmpNode = NULL;
    struct ListNode* Store = NULL;
    pTmpNode = head;
    while( pTmpNode != NULL)
    {
        pKList[nPeriod] = pTmpNode;
        pTmpNode = pTmpNode->next;
        nPeriod++;
        nPeriod %= k;
        if(nPeriod==0)
        {
            if( pPointerStart == NULL)
            {
                pPointerStart = pKList[k-1];
            }
            else
            {
                Store->next = pKList[k-1];
            }
            for(int index = 0; index < k-1 ; index++)
            {
               pKList[k-(index+1)]->next = pKList[k-(index+2)];
            }
            Store = pKList[0];
        }
    }
        if(nPeriod != 0 && Store != NULL)
    {
        Store->next = pKList[0];
    }
    if( pPointerStart == NULL)pPointerStart=pKList[0];
    return pPointerStart;
}