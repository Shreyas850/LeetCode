class BookMyShow {
    private var n: Int
    private var m: Int
    private var treeMax: [Int]
    private var treeSum: [Int]
    private var seatsLeft: [Int]
    private var minRow: Int
    
    init(_ n: Int, _ m: Int) {
        self.n = n
        self.m = m
        self.treeMax = Array(repeating: 0, count: 4 * n)
        self.treeSum = Array(repeating: 0, count: 4 * n)
        self.seatsLeft = Array(repeating: m, count: n)
        self.minRow = 0
        build(0, 0, n - 1)
    }
    
    private func build(_ node: Int, _ l: Int, _ r: Int) {
        if l == r {
            treeMax[node] = m
            treeSum[node] = m
            return
        }
        let mid = l + (r - l) / 2
        build(node * 2 + 1, l, mid)
        build(node * 2 + 2, mid + 1, r)
        treeMax[node] = max(treeMax[node * 2 + 1], treeMax[node * 2 + 2])
        treeSum[node] = treeSum[node * 2 + 1] + treeSum[node * 2 + 2]
    }
    
    func gather(_ k: Int, _ maxRow: Int) -> [Int] {
        if k > m {
            return []
        }
        
        let row = findFirst(0, 0, n - 1, maxRow, k)
        if row == -1 {
            return []
        }
        
        let startSeat = m - seatsLeft[row]
        seatsLeft[row] -= k
        update(0, 0, n - 1, row, seatsLeft[row])
        
        return [row, startSeat]
    }
    
    func scatter(_ k: Int, _ maxRow: Int) -> Bool {
        if querySum(0, 0, n - 1, 0, maxRow) < k {
            return false
        }
        
        var remaining = k
        var i = minRow
        
        while remaining > 0 && i <= maxRow {
            if seatsLeft[i] > 0 {
                let take = min(seatsLeft[i], remaining)
                seatsLeft[i] -= take
                remaining -= take
                update(0, 0, n - 1, i, seatsLeft[i])
            }
            if seatsLeft[i] == 0 {
                minRow = i + 1
            }
            i += 1
        }
        
        return true
    }
    
    private func findFirst(_ node: Int, _ l: Int, _ r: Int, _ maxRow: Int, _ val: Int) -> Int {
        if treeMax[node] < val || l > maxRow {
            return -1
        }
        if l == r {
            return l
        }
        let mid = l + (r - l) / 2
        let res = findFirst(node * 2 + 1, l, mid, maxRow, val)
        if res != -1 {
            return res
        }
        return findFirst(node * 2 + 2, mid + 1, r, maxRow, val)
    }
    
    private func querySum(_ node: Int, _ l: Int, _ r: Int, _ ql: Int, _ qr: Int) -> Int {
        if ql > r || qr < l {
            return 0
        }
        if ql <= l && r <= qr {
            return treeSum[node]
        }
        let mid = l + (r - l) / 2
        return querySum(node * 2 + 1, l, mid, ql, qr) + querySum(node * 2 + 2, mid + 1, r, ql, qr)
    }
    
    private func update(_ node: Int, _ l: Int, _ r: Int, _ idx: Int, _ val: Int) {
        if l == r {
            treeMax[node] = val
            treeSum[node] = val
            return
        }
        let mid = l + (r - l) / 2
        if idx <= mid {
            update(node * 2 + 1, l, mid, idx, val)
        } else {
            update(node * 2 + 2, mid + 1, r, idx, val)
        }
        treeMax[node] = max(treeMax[node * 2 + 1], treeMax[node * 2 + 2])
        treeSum[node] = treeSum[node * 2 + 1] + treeSum[node * 2 + 2]
    }
}