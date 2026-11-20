# DSA Notes

Problem-by-problem notes. Each folder walks through one problem: progressive hints, the intuition behind it, every approach from brute force to optimal with a complexity breakdown and a step-by-step dry run, a commented C++ solution, and test cases.

**15 problems** · 1 solved · Easy 2 · Medium 8 · Hard 5 · 12 patterns

**How to use these notes:** try the problem first, then open the hints one at a time. Read the intuition and the approaches only after you've made an attempt.

| # | Problem | Platform | Difficulty | Pattern | Optimal | Solution | Solved |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | [Best Time to Buy and Sell Stock](leetcode/best-time-to-buy-and-sell-stock/) | LeetCode | Easy | Running minimum (one-pass prefix DP) | `O(n)` time, `O(1)` space | [C++](leetcode/best-time-to-buy-and-sell-stock/best-time-to-buy-and-sell-stock.cpp) |   |
| 2 | [Cherry Pickup II](leetcode/cherry-pickup-ii/) | LeetCode | Hard | 3D DP on (row, j1, j2): two walkers moving in lockstep | `O(rows · cols^2 · 9)` time, `O(cols^2)` space | [C++](leetcode/cherry-pickup-ii/cherry-pickup-ii.cpp) |   |
| 3 | [Climbing Stairs](leetcode/climbing-stairs/) | LeetCode | Easy | 1D DP (Fibonacci recurrence) | `O(n)` time, `O(1)` space | [C++](leetcode/climbing-stairs/climbing-stairs.cpp) |   |
| 4 | [Count Square Submatrices with All Ones](leetcode/count-square-submatrices-with-all-ones/) | LeetCode | Medium | 2D DP: largest square ending at each cell | `O(m·n)` time, `O(n)` space | [C++](leetcode/count-square-submatrices-with-all-ones/count-square-submatrices-with-all-ones.cpp) |   |
| 5 | [Expression Add Operators](leetcode/expression-add-operators/) | LeetCode | Hard |   |   |   |   |
| 6 | [House Robber](leetcode/house-robber/) | LeetCode | Medium | 1D DP on prefixes (pick / skip) | `O(n)` time, `O(1)` space | [C++](leetcode/house-robber/house-robber.cpp) |   |
| 7 | [House Robber II](leetcode/house-robber-ii/) | LeetCode | Medium | 1D take/skip DP, run twice to break the circle | `O(n)` time, `O(1)` space | [C++](leetcode/house-robber-ii/house-robber-ii.cpp) |   |
| 8 | [Max Circular Subarray Sum](gfg/max-circular-subarray-sum-1587115620/) | GeeksforGeeks | Hard |   |   |   |   |
| 9 | [Maximize Consecutive Elements in an Array After Modification](leetcode/maximize-consecutive-elements-in-an-array-after-modification/) | LeetCode | Hard | Sorting + Dynamic Programming | `O(n log n)` time, `O(n)` space | [C++](leetcode/maximize-consecutive-elements-in-an-array-after-modification/maximize-consecutive-elements-in-an-array-after-modification.cpp) |   |
| 10 | [Minimum Falling Path Sum](leetcode/minimum-falling-path-sum/) | LeetCode | Medium | Grid DP, row by row (free start and end) | `O(n^2)` time, `O(n)` space | [C++](leetcode/minimum-falling-path-sum/minimum-falling-path-sum.cpp) |   |
| 11 | [N-Queens](leetcode/n-queens/) | LeetCode | Hard |   |   |   |   |
| 12 | [Rotate Array](leetcode/rotate-array/) | LeetCode | Medium | Array reversal (three reverses) | `O(n)` time, `O(1)` space |   | ✅ [C++](leetcode/rotate-array/my-solution.cpp) |
| 13 | [Triangle](leetcode/triangle/) | LeetCode | Medium | 2D grid DP on a triangle, filled bottom-up | `O(n^2)` time, `O(n)` space | [C++](leetcode/triangle/triangle.cpp) |   |
| 14 | [Unique Paths](leetcode/unique-paths/) | LeetCode | Medium | Grid DP for counting paths, which collapses to a binomial coefficient | `O(min(m, n))` time, `O(1)` space | [C++](leetcode/unique-paths/unique-paths.cpp) |   |
| 15 | [Unique Paths II](leetcode/unique-paths-ii/) | LeetCode | Medium | 2D grid DP (counting paths) | `O(m·n)` time, `O(n)` space | [C++](leetcode/unique-paths-ii/unique-paths-ii.cpp) |   |
