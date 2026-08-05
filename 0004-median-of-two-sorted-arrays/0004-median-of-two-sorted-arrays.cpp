#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array to minimize binary search range
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.size();
        int n = nums2.size();
        
        int low = 0;
        int high = m;
        
        while (low <= high) {
            int partitionX = low + (high - low) / 2;
            // +1 ensures it works for both even and odd total lengths
            int partitionY = (m + n + 1) / 2 - partitionX; 
            
            // Handle edge cases where partition is at the extreme ends
            int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
            
            int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];
            
            // Check if we found the correct partition
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // If total length is even
                if ((m + n) % 2 == 0) {
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                } 
                // If total length is odd
                else {
                    return max(maxLeftX, maxLeftY);
                }
            } 
            // We are too far on the right side for partitionX, move left
            else if (maxLeftX > minRightY) {
                high = partitionX - 1;
            } 
            // We are too far on the left side for partitionX, move right
            else {
                low = partitionX + 1;
            }
        }
        
        return 0.0; // Fallback
    }
};