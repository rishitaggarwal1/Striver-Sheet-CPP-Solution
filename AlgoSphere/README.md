# DSA Notes

Problem-by-problem notes. Each folder walks through one problem: progressive hints, the intuition behind it, every approach from brute force to optimal with a complexity breakdown and a step-by-step dry run, a commented C++ solution, and test cases.

**30 problems** · 12 solved · Easy 5 · Medium 17 · Hard 8 · 23 patterns

**How to use these notes:** try the problem first, then open the hints one at a time. Read the intuition and the approaches only after you've made an attempt.

| # | Problem | Platform | Difficulty | Pattern | Optimal | Solution | Solved |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | [Best Time to Buy and Sell Stock](leetcode/best-time-to-buy-and-sell-stock/) | LeetCode | Easy | Running minimum (one-pass prefix DP) | `O(n)` time, `O(1)` space | [C++](leetcode/best-time-to-buy-and-sell-stock/best-time-to-buy-and-sell-stock.cpp) |   |
| 2 | [Check if All A's Appears Before All B's](leetcode/check-if-all-as-appears-before-all-bs/) | LeetCode | Easy |   |   |   | ✅ [C++](leetcode/check-if-all-as-appears-before-all-bs/my-solution.cpp) |
| 3 | [Cherry Pickup II](leetcode/cherry-pickup-ii/) | LeetCode | Hard | 3D DP on (row, j1, j2): two walkers moving in lockstep | `O(rows · cols^2 · 9)` time, `O(cols^2)` space | [C++](leetcode/cherry-pickup-ii/cherry-pickup-ii.cpp) |   |
| 4 | [Climbing Stairs](leetcode/climbing-stairs/) | LeetCode | Easy | 1D DP (Fibonacci recurrence) | `O(n)` time, `O(1)` space | [C++](leetcode/climbing-stairs/climbing-stairs.cpp) |   |
| 5 | [Count Square Submatrices with All Ones](leetcode/count-square-submatrices-with-all-ones/) | LeetCode | Medium | 2D DP: largest square ending at each cell | `O(m·n)` time, `O(n)` space | [C++](leetcode/count-square-submatrices-with-all-ones/count-square-submatrices-with-all-ones.cpp) |   |
| 6 | [Expression Add Operators](leetcode/expression-add-operators/) | LeetCode | Hard |   |   |   |   |
| 7 | [Find Subtree Sizes After Changes](leetcode/find-subtree-sizes-after-changes/) | LeetCode | Medium | DFS with per-character ancestor state (backtracking), then subtree-size accumulation | `O(n)` time, `O(n)` space | [C++](leetcode/find-subtree-sizes-after-changes/find-subtree-sizes-after-changes.cpp) |   |
| 8 | [House Robber](leetcode/house-robber/) | LeetCode | Medium | 1D DP on prefixes (pick / skip) | `O(n)` time, `O(1)` space | [C++](leetcode/house-robber/house-robber.cpp) |   |
| 9 | [House Robber II](leetcode/house-robber-ii/) | LeetCode | Medium | 1D take/skip DP, run twice to break the circle | `O(n)` time, `O(1)` space | [C++](leetcode/house-robber-ii/house-robber-ii.cpp) |   |
| 10 | [K-th of Two Sorted Arrays](gfg/k-th-element-of-two-sorted-array1317/) | GeeksforGeeks | Medium |   |   |   |   |
| 11 | [M-Coloring Problem](gfg/m-coloring-problem-1587115620/) | GeeksforGeeks | Medium | Backtracking (constraint satisfaction) | `O(m^V · V) worst case, heavily pruned in practice` time, `O(V)` space | [C++](gfg/m-coloring-problem-1587115620/m-coloring-problem-1587115620.cpp) | ✅ [C++](gfg/m-coloring-problem-1587115620/my-solution.cpp) |
| 12 | [Max Circular Subarray Sum](gfg/max-circular-subarray-sum-1587115620/) | GeeksforGeeks | Hard |   |   |   |   |
| 13 | [Maximize Consecutive Elements in an Array After Modification](leetcode/maximize-consecutive-elements-in-an-array-after-modification/) | LeetCode | Hard | Sorting + Dynamic Programming | `O(n log n)` time, `O(n)` space | [C++](leetcode/maximize-consecutive-elements-in-an-array-after-modification/maximize-consecutive-elements-in-an-array-after-modification.cpp) |   |
| 14 | [Maximum Subarray With Equal Products](leetcode/maximum-subarray-with-equal-products/) | LeetCode | Easy | Prime-exponent reasoning + sliding window | `O(n)` time, `O(1)` space | [C++](leetcode/maximum-subarray-with-equal-products/maximum-subarray-with-equal-products.cpp) | ✅ [C++](leetcode/maximum-subarray-with-equal-products/my-solution.cpp) |
| 15 | [Median of Two Sorted Arrays](leetcode/median-of-two-sorted-arrays/) | LeetCode | Hard |   |   |   |   |
| 16 | [Minimum Falling Path Sum](leetcode/minimum-falling-path-sum/) | LeetCode | Medium | Grid DP, row by row (free start and end) | `O(n^2)` time, `O(n)` space | [C++](leetcode/minimum-falling-path-sum/minimum-falling-path-sum.cpp) |   |
| 17 | [N-Queens](leetcode/n-queens/) | LeetCode | Hard | Backtracking with constant-time conflict sets | `O(n!) roughly` time, `O(n) besides output` space | [C++](leetcode/n-queens/n-queens.cpp) | ✅ [C++](leetcode/n-queens/my-solution.cpp) |
| 18 | [Network Delay Time](leetcode/network-delay-time/) | LeetCode | Medium | Single-source shortest paths (Dijkstra) | `O(E log E), i.e. O(E log n)` time, `O(n + E)` space | [C++](leetcode/network-delay-time/network-delay-time.cpp) | ✅ [C++](leetcode/network-delay-time/my-solution.cpp) |
| 19 | [Palindrome Partitioning](leetcode/palindrome-partitioning/) | LeetCode | Medium | Backtracking with precomputed palindrome DP table | `O(n · 2^n)` time, `O(n^2) besides output` space | [C++](leetcode/palindrome-partitioning/palindrome-partitioning.cpp) | ✅ [C++](leetcode/palindrome-partitioning/my-solution.cpp) |
| 20 | [Product of the Last K Numbers](leetcode/product-of-the-last-k-numbers/) | LeetCode | Medium | Prefix products reset at zero | `O(1) per add and getProduct (amortised for append)` time, `O(n)` space | [C++](leetcode/product-of-the-last-k-numbers/product-of-the-last-k-numbers.cpp) | ✅ [C++](leetcode/product-of-the-last-k-numbers/my-solution.cpp) |
| 21 | [Rat in Maze](gfg/rat-in-a-maze-problem/) | GeeksforGeeks | Medium |   |   |   | ✅ [C++](gfg/rat-in-a-maze-problem/my-solution.cpp) |
| 22 | [Rotate Array](leetcode/rotate-array/) | LeetCode | Medium | Array reversal (three reverses) | `O(n)` time, `O(1)` space |   | ✅ [C++](leetcode/rotate-array/my-solution.cpp) |
| 23 | [Smallest Unique Subarray](leetcode/smallest-unique-subarray/) | LeetCode | Hard | Binary search on answer + rolling hash | `O(n log n)` time, `O(n)` space | [C++](leetcode/smallest-unique-subarray/smallest-unique-subarray.cpp) | ✅ [C++](leetcode/smallest-unique-subarray/my-solution.cpp) |
| 24 | [Stone Removal Game](leetcode/stone-removal-game/) | LeetCode | Easy | Deterministic game simulation | `O(1)` time, `O(1)` space |   | ✅ [C++](leetcode/stone-removal-game/my-solution.cpp) |
| 25 | [Sudoku Solver](leetcode/sudoku-solver/) | LeetCode | Hard | Backtracking with constraint bitmasks | `Exponential worst case, but each node costs O(m) and in practice only a few hundred nodes are explored` time, `O(m) recursion plus 27 integers` space | [C++](leetcode/sudoku-solver/sudoku-solver.cpp) | ✅ [C++](leetcode/sudoku-solver/my-solution.cpp) |
| 26 | [Triangle](leetcode/triangle/) | LeetCode | Medium | 2D grid DP on a triangle, filled bottom-up | `O(n^2)` time, `O(n)` space | [C++](leetcode/triangle/triangle.cpp) |   |
| 27 | [Unique Paths](leetcode/unique-paths/) | LeetCode | Medium | Grid DP for counting paths, which collapses to a binomial coefficient | `O(min(m, n))` time, `O(1)` space | [C++](leetcode/unique-paths/unique-paths.cpp) |   |
| 28 | [Unique Paths II](leetcode/unique-paths-ii/) | LeetCode | Medium | 2D grid DP (counting paths) | `O(m·n)` time, `O(n)` space | [C++](leetcode/unique-paths-ii/unique-paths-ii.cpp) |   |
| 29 | [Word Search](leetcode/word-search/) | LeetCode | Medium |   |   |   |   |
| 30 | [Zigzag Conversion](leetcode/zigzag-conversion/) | LeetCode | Medium | Simulation, then periodic index arithmetic | `O(n)` time, `O(1) besides the output` space | [C++](leetcode/zigzag-conversion/zigzag-conversion.cpp) |   |

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
