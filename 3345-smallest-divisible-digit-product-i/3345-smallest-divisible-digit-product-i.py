class Solution:
    def smallestNumber(self, n, t):
        current = n
        
        while True:
            digit_product = 1
            for digit in str(current):
                digit_product *= int(digit)
                
            if digit_product % t == 0:
                return current
                
            current += 1