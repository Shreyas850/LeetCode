class Solution {
    struct Point: Hashable {
        let r: Int
        let c: Int
    }
    
    func minMoves(_ classroom: [String], _ energy: Int) -> Int {
        let m = classroom.count
        let n = classroom[0].count
        var grid = [[Character]]()
        
        for row in classroom {
            grid.append(Array(row))
        }
        
        var startR = 0
        var startC = 0
        var litterIndices = [Point: Int]()
        var litterCount = 0
        
        for r in 0..<m {
            for c in 0..<n {
                if grid[r][c] == "S" {
                    startR = r
                    startC = c
                } else if grid[r][c] == "L" {
                    litterIndices[Point(r: r, c: c)] = litterCount
                    litterCount += 1
                }
            }
        }
        
        let targetMask = (1 << litterCount) - 1
        if targetMask == 0 { 
            return 0 
        }
        
        var visited = Array(repeating: Array(repeating: Array(repeating: -1, count: 1 << litterCount), count: n), count: m)
        
        var queue = [(r: Int, c: Int, mask: Int, energy: Int, steps: Int)]()
        var head = 0
        
        let maxEnergy = energy
        queue.append((startR, startC, 0, maxEnergy, 0))
        visited[startR][startC][0] = maxEnergy
        
        let dr = [-1, 1, 0, 0]
        let dc = [0, 0, -1, 1]
        
        while head < queue.count {
            let curr = queue[head]
            head += 1
            
            if curr.energy == 0 {
                continue
            }
            
            for i in 0..<4 {
                let nr = curr.r + dr[i]
                let nc = curr.c + dc[i]
                
                if nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != "X" {
                    var nextEnergy = curr.energy - 1
                    var nextMask = curr.mask
                    
                    if grid[nr][nc] == "L" {
                        if let idx = litterIndices[Point(r: nr, c: nc)] {
                            nextMask |= (1 << idx)
                        }
                    } else if grid[nr][nc] == "R" {
                        nextEnergy = maxEnergy
                    }
                    
                    if nextMask == targetMask {
                        return curr.steps + 1
                    }
                    
                    if nextEnergy > visited[nr][nc][nextMask] {
                        visited[nr][nc][nextMask] = nextEnergy
                        queue.append((nr, nc, nextMask, nextEnergy, curr.steps + 1))
                    }
                }
            }
        }
        
        return -1
    }
}