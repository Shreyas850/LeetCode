class Solution {
    func reverseKGroup(_ head: ListNode?, _ k: Int) -> ListNode? {
        if head == nil || k == 1 { return head }
        
        // Step 1: Count the total number of nodes
        var count = 0
        var curr = head
        while curr != nil {
            count += 1
            curr = curr?.next
        }
        
        // Step 2: Use a dummy node to easily handle the head of the list
        let dummy = ListNode(0)
        dummy.next = head
        var prevGroupTail: ListNode? = dummy
        
        // Step 3: Reverse in groups of k
        while count >= k {
            curr = prevGroupTail?.next
            var prev: ListNode? = nil
            var next: ListNode? = nil
            
            // Standard linked list reversal for k nodes
            for _ in 0..<k {
                next = curr?.next
                curr?.next = prev
                prev = curr
                curr = next
            }
            
            // Connect the reversed group back to the main list
            let tailOfReversedGroup = prevGroupTail?.next
            tailOfReversedGroup?.next = curr
            prevGroupTail?.next = prev
            
            // Move our pointer forward for the next group
            prevGroupTail = tailOfReversedGroup
            
            count -= k
        }
        
        return dummy.next
    }
}