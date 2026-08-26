class Solution {
    func shortestBeautifulSubstring(_ s: String, _ k: Int) -> String {
        let chars = Array(s)
        var onesIndices = [Int]()
        
        for (i, char) in chars.enumerated() {
            if char == "1" {
                onesIndices.append(i)
            }
        }
        
        if onesIndices.count < k {
            return ""
        }
        
        var minLength = Int.max
        var bestSubstring = ""
        
        for i in 0...(onesIndices.count - k) {
            let start = onesIndices[i]
            let end = onesIndices[i + k - 1]
            let currentLength = end - start + 1
            
            if currentLength < minLength {
                minLength = currentLength
                bestSubstring = String(chars[start...end])
            } else if currentLength == minLength {
                let currentSubstring = String(chars[start...end])
                if currentSubstring < bestSubstring {
                    bestSubstring = currentSubstring
                }
            }
        }
        
        return bestSubstring
    }
}