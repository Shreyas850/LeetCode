class Solution {
public:
    // Custom comparator for the min-heap to order ListNode* by value
    struct CompareNode {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, CompareNode> minHeap;
        
        // Push the head of each non-empty linked list into the heap
        for (ListNode* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }
        
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        
        // Continually extract the minimum node and push its successor
        while (!minHeap.empty()) {
            ListNode* smallest = minHeap.top();
            minHeap.pop();
            
            tail->next = smallest;
            tail = tail->next;
            
            if (smallest->next != nullptr) {
                minHeap.push(smallest->next);
            }
        }
        
        ListNode* mergedHead = dummy->next;
        delete dummy;
        return mergedHead;
    }
};