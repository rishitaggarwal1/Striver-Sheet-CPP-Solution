# Product of the Last K Numbers

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/product-of-the-last-k-numbers/) · Pattern: **Prefix products reset at zero** · ✅ Solved in C++

> Support appending non-negative integers to a list and answering, at any time, the product of the last `k` appended integers.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [My solution](#my-solution) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Design an algorithm that accepts a stream of integers and retrieves the product of the last k integers of the stream.

Implement the ProductOfNumbers class:

- ProductOfNumbers() Initializes the object with an empty stream.

- void add(int num) Appends the integer num to the stream.

- int getProduct(int k) Returns the product of the last k numbers in the current list. You can assume that always the current list has at least k numbers.

The test cases are generated so that, at any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.

Example:

Input
["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
[[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]

Output
[null,null,null,null,null,null,20,40,0,null,32]

Explanation
ProductOfNumbers productOfNumbers = new ProductOfNumbers();
productOfNumbers.add(3);        // [3]
productOfNumbers.add(0);        // [3,0]
productOfNumbers.add(2);        // [3,0,2]
productOfNumbers.add(5);        // [3,0,2,5]
productOfNumbers.add(4);        // [3,0,2,5,4]
productOfNumbers.getProduct(2); // return 20. The product of the last 2 numbers is 5 * 4 = 20
productOfNumbers.getProduct(3); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
productOfNumbers.getProduct(4); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
productOfNumbers.add(8);        // [3,0,2,5,4,8]
productOfNumbers.getProduct(2); // return 32. The product of the last 2 numbers is 4 * 8 = 32

Constraints:

- 0 <= num <= 100

- 1 <= k <= 4 * 10^4

- At most 4 * 10^4 calls will be made to add and getProduct.

- The product of the stream at any point in time will fit in a 32-bit integer.

Follow-up: Can you implement both GetProduct and Add to work in O(1) time complexity instead of O(k) time complexity?
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Numbers keep arriving one at a time, and at any moment you may be asked to multiply together the most recent `k` of them. You want both adding a number and answering a query to be cheap.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In the example, any query whose window reaches back over the `0` returns 0, no matter what else is in it. Queries that stay entirely after the `0` behave as if the earlier part of the stream never existed.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

There can be up to `4 * 10^4` calls, and each `k` can be up to `4 * 10^4`. Multiplying the last `k` numbers on every query costs `O(k)`, which is about `1.6 * 10^9` operations in the worst case and too slow. You want `O(1)` per operation.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is a running prefix product, the multiplicative cousin of prefix sums. A product over a range can be recovered by dividing one prefix product by an earlier one, just as a range sum is a difference of prefix sums.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Division breaks when a zero is involved, so whenever a `0` arrives, throw away all history and start fresh. If a query's `k` reaches back to or past that reset point, the window must contain the zero, so the answer is 0.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep a list of prefix products that starts with a sentinel `1`. Each entry is the product of all numbers added since the most recent zero, up to that position. The list's length minus one tells you how many nonzero numbers have arrived since the last zero.

</details>

<details>
<summary>Hint 7 · Approach</summary>

On `add(num)` with `num` equal to 0: reset the list to just `[1]`.
On `add(num)` with any other value: append `last entry * num` to the list.
On `getProduct(k)`: let `n` be the list length.
If `k >= n`, return 0, because the window includes a zero.
Otherwise, return `list[n-1] / list[n-1-k]`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is the boundary check: use `k >= n`, not `k > n`, because the sentinel occupies one slot. Also handle a zero as the very first number, and several zeros in a row; resetting handles both. The guarantee that products fit in 32 bits keeps the stored prefixes safe from overflow. Each `add` and `getProduct` runs in `O(1)` time (amortized for list appends), and space is `O(n)` for the stored prefixes.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "product of the last k numbers" means a contiguous suffix | this is a range query, so precompute prefix products and divide, the same way prefix sums answer range sums. |
| `0 <= num <= 100`, so zeros can appear | division by a prefix that contains 0 breaks. Any window that covers a 0 has product 0, so only the stretch after the most recent zero matters. |
| Follow-up asks for O(1) `add` and `getProduct` | each query must be answered from stored state, not by rescanning `k` elements. |
| "product of any contiguous sequence ... fits in a 32-bit integer" | a prefix product that starts right after the last zero is itself a contiguous product, so it never overflows. That only holds if the prefix restarts at zeros. |

### What the constraints tell you

Up to 4·10^4 calls with `k` up to 4·10^4. Rescanning `k` numbers per query is about 4·10^4 × 4·10^4 = 1.6·10^9 multiplications in the worst case, which is too slow. O(1) per call means about 4·10^4 total operations, so the target is O(1) amortised per operation.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most direct way to answer `getProduct(k)`?**

<details>
<summary>Answer</summary>

Keep every number in a list and multiply the last `k` of them. That is correct but costs O(k) per query, up to 1.6·10^9 work overall.

</details>

**Q2. Suffix product queries look like suffix sum queries. What is the standard trick there?**

<details>
<summary>Answer</summary>

Store prefix sums and subtract. For products, store `prefix[i]` = product of the first `i` numbers, then answer with `prefix[n] / prefix[n-k]`.

</details>

**Q3. Why does plain prefix-product division fail on the example `[3,0,2,5,4]`?**

<details>
<summary>Answer</summary>

After the 0, every prefix is 0. `getProduct(2)` would compute `0 / 0` instead of 20. Dividing out a zero is impossible.

</details>

**Q4. What does a zero really tell us about future queries?**

<details>
<summary>Answer</summary>

Any window that reaches back to or past that zero has product 0. Windows that stay strictly after it never involve anything before it. So everything before the latest zero can be forgotten.

</details>

**Q5. So how should the prefix array behave when `num == 0` arrives?**

<details>
<summary>Answer</summary>

Reset it to `[1]`, so prefixes start fresh after the zero. Its length minus one is now the count of numbers since the last zero. If `k` is at least the prefix length, the window includes that zero and the answer is 0. Otherwise the answer is `prefix[last] / prefix[last-k]`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Store list, multiply last k](#1-brute-force-store-list-multiply-last-k) | `O(1) add, O(k) getProduct` | `O(n)` |
| 2 | [Better: List plus last-zero index](#2-better-list-plus-last-zero-index) | `O(1) add, O(k) getProduct worst case` | `O(n)` |
| 3 | [Optimal: Prefix products reset on zero](#3-optimal-prefix-products-reset-on-zero) | `O(1) per add and getProduct (amortised for append)` | `O(n)` |

### 1. Brute force: Store list, multiply last k

> **Where you start:** The problem literally says "product of the last k numbers", so the first instinct is to keep the stream and loop over its tail.

**Idea.** Append each `num` to a list. For `getProduct(k)`, multiply the last `k` elements. It is trivially correct because it computes exactly the definition. You can stop early when you hit a 0.

**Steps**

1. Keep a dynamic list `nums`.
2. `add(num)`: append `num`.
3. `getProduct(k)`: set `p = 1`.
4. Loop over the last `k` entries, multiplying into `p`. Return 0 immediately if an entry is 0.
5. Return `p`.

**Pseudocode**

```text
 1 │ function ProductOfNumbers()
 2 │   nums ← empty list // the whole stream, kept in arrival order
 3 │ function add(num)
 4 │   append num to the end of nums // O(1) amortized
 5 │ function getProduct(k)
 6 │   p ← 1 // empty product
 7 │   n ← length(nums)
 8 │   for i ← n − 1 down to n − k // walk the last k entries, newest first
 9 │     if nums[i] = 0
10 │       return 0 // one zero makes the whole product 0, so stop early
11 │     p ← p × nums[i]
12 │   return p
```

**Time complexity: `O(1) per add, O(k) per getProduct`**

| Part | Cost | Why |
| --- | --- | --- |
| add (lines 3-4) | 1 append × O(1) amortized | A dynamic array append only writes one slot, and it occasionally resizes, which averages out to constant time. |
| getProduct setup (lines 6-7) | O(1) | These lines only make two assignments. |
| getProduct loop (lines 8-11) | at most k iterations × O(1) | Each iteration does one comparison and one multiplication, and the loop covers only the last k entries. |

- **Adding it up:** add = O(1). getProduct = O(1) + k·O(1) = O(k). Over Q calls the total is O(A + Σk), where A is the number of adds.
- **Best vs worst case:** Best case: the newest number is 0, so the loop returns after 1 iteration (O(1)). Worst case: the last k numbers have no 0 (for example a long run of 1s), so all k iterations run.
- **At the maximum input:** With 4·10^4 total calls, about 2·10^4 adds followed by 2·10^4 calls of getProduct(2·10^4) on all 1s gives about 4·10^8 multiplications. That is a few hundred milliseconds in C++, borderline but usually accepted. The prefix-product follow-up brings this down to O(1) per call.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| nums list (line 2, grown by line 4) | n integers | Every added number is stored forever, because a later getProduct may need any of the last k of them. |
| getProduct locals p, n, i (lines 6-8) | O(1) | These are a fixed number of scalars, whatever k is. |

- **Adding it up:** O(n) + O(1) = O(n), where n is the number of add calls so far.
- **Not counted:** There is no recursion. The returned integer is not counted.

**Dry run** on `["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
[[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | The constructor runs and the stream starts empty. | `nums = []` |
| 2 | 4 | add(3) appends 3 at index 0. | `num = 3`<br>`nums = [3]` |
| 3 | 4 | add(0), add(2), add(5) and add(4) each append one value in the same way (collapsed into one step). The stream is now [3,0,2,5,4]. | `num = 4`<br>`nums = [3, 0, 2, 5, 4]` |
| 4 | 7 | getProduct(2) sets p = 1 and n = 5. The loop will visit i = 4 down to 3. | `k = 2`<br>`p = 1`<br>`n = 5` |
| 5 | 11 | i = 4: nums[4] = 4 is not 0, so p = 1 × 4 = 4. | `p = 4`<br>`i = 4`<br>`nums = [3, 0, 2, 5, 4]` (i→4) |
| 6 | 11 | i = 3: nums[3] = 5 is not 0, so p = 4 × 5 = 20. | `p = 20`<br>`i = 3`<br>`nums = [3, 0, 2, 5, 4]` (i→3) |
| 7 | 12 | The loop has covered the last 2 entries, so the call returns 20. | `returned = 20`<br>`nums = [3, 0, 2, 5, 4]` |
| 8 | 7 | getProduct(3) resets p = 1 with n = 5. The loop will visit i = 4 down to 2. | `k = 3`<br>`p = 1` |
| 9 | 11 | i = 4: p = 1 × 4 = 4. | `p = 4`<br>`i = 4`<br>`nums = [3, 0, 2, 5, 4]` (i→4) |
| 10 | 11 | i = 3: p = 4 × 5 = 20. | `p = 20`<br>`i = 3`<br>`nums = [3, 0, 2, 5, 4]` (i→3) |
| 11 | 11 | i = 2: nums[2] = 2, so p = 20 × 2 = 40. | `p = 40`<br>`i = 2`<br>`nums = [3, 0, 2, 5, 4]` (i→2) |
| 12 | 12 | All 3 entries have been multiplied, so the call returns 40. | `returned = 40`<br>`nums = [3, 0, 2, 5, 4]` |
| 13 | 10 | getProduct(4) multiplies i = 4, 3, 2 as before, giving p = 40 (skipped). At i = 1, nums[1] = 0, so it returns 0 immediately. | `k = 4`<br>`i = 1`<br>`returned = 0`<br>`nums = [3, 0, 2, 5, 4]` (i→1) |
| 14 | 4 | add(8) appends 8 at index 5. | `num = 8`<br>`nums = [3, 0, 2, 5, 4, 8]` |
| 15 | 11 | getProduct(2) with n = 6: at i = 5, p = 1 × 8 = 8. At i = 4, p = 8 × 4 = 32. | `k = 2`<br>`p = 32`<br>`n = 6`<br>`i = 4`<br>`nums = [3, 0, 2, 5, 4, 8]` (i→4) |
| 16 | 12 | The last 2 entries are done, so the call returns 32. | `returned = 32`<br>`nums = [3, 0, 2, 5, 4, 8]` |

**Result:** [null,null,null,null,null,null,20,40,0,null,32]. Each getProduct multiplies exactly the last k stored numbers, which is the definition itself, and stopping early on a 0 is safe because any product containing a 0 is 0.

**C++ solution**

```cpp
class ProductOfNumbers {
public:
    ProductOfNumbers() {
        // nums starts empty; nothing else to set up
    }
    
    void add(int num) {
        nums.push_back(num); // store every number so any suffix can be re-multiplied later
    }
    
    int getProduct(int k) {
        int p = 1;                       // multiplicative identity
        int n = (int)nums.size();
        for (int i = n - 1; i >= n - k; --i) { // walk the last k numbers, newest first
            if (nums[i] == 0) return 0;  // a zero anywhere makes the product 0, so stop early
            p *= nums[i];                // fits in 32 bits per the problem guarantee
        }
        return p;
    }

private:
    vector<int> nums; // the full stream in arrival order
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
public:
    ProductOfNumbers() {
        // nums starts empty; nothing else to set up
    }
    
    void add(int num) {
        nums.push_back(num); // store every number so any suffix can be re-multiplied later
    }
    
    int getProduct(int k) {
        int p = 1;                       // multiplicative identity
        int n = (int)nums.size();
        for (int i = n - 1; i >= n - k; --i) { // walk the last k numbers, newest first
            if (nums[i] == 0) return 0;  // a zero anywhere makes the product 0, so stop early
            p *= nums[i];                // fits in 32 bits per the problem guarantee
        }
        return p;
    }

private:
    vector<int> nums; // the full stream in arrival order
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

int main() {
    vector<string> ops = {"ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"};
    vector<int> args = {0,3,0,2,5,4,2,3,4,8,2};
    vector<string> expected = {"null","null","null","null","null","null","20","40","0","null","32"};
    ProductOfNumbers* obj = nullptr;
    vector<string> out;
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == "ProductOfNumbers") { obj = new ProductOfNumbers(); out.push_back("null"); }
        else if (ops[i] == "add") { obj->add(args[i]); out.push_back("null"); }
        else { out.push_back(to_string(obj->getProduct(args[i]))); }
    }
    auto show = [](const vector<string>& v) {
        string s = "[";
        for (size_t i = 0; i < v.size(); ++i) { if (i) s += ","; s += v[i]; }
        return s + "]";
    };
    cout << "Output:   " << show(out) << "\n";
    cout << "Expected: " << show(expected) << "\n";
    delete obj;
    return 0;
}
```

</details>

**Why move on:** Each query redoes multiplications that earlier queries already did. Worst case 1.6·10^9 operations is too slow and fails the O(1) follow-up.

### 2. Better: List plus last-zero index

> **How you get here:** The brute force walks all the way to a zero just to return 0. If we remember where the most recent zero is, we can answer those queries instantly.

**Idea.** Alongside the list, store `lastZero`, the index of the most recent 0 (or -1 if none). If `k > n - 1 - lastZero`, the window includes that zero, so return 0 at once. Otherwise multiply the last `k` numbers, which are all non-zero. This is correct because any window containing a 0 has product 0. It is still O(k) when the window contains no zero.

**Steps**

1. Keep list `nums` and integer `lastZero = -1`.
2. `add(num)`: append it. If `num == 0`, set `lastZero` to its index.
3. `getProduct(k)`: let `n` be the list size.
4. If `n - k <= lastZero`, return 0.
5. Otherwise multiply `nums[n-k .. n-1]` and return the product.

**Complexity:** time `O(1) add, O(k) getProduct worst case`, space `O(n)`. Queries whose window covers a zero become O(1). Zero-free windows still cost O(k), so the worst case is unchanged. The list stores the whole stream.

**Why move on:** A long stretch of 1s with no zeros still forces O(k) multiplication per query, about 1.6·10^9 in the worst case. We still recompute overlapping suffix products every time.

### 3. Optimal: Prefix products reset on zero

> **How you get here:** The Better approach already showed that nothing before the last zero matters. The products after it overlap from query to query, so precompute them as prefix products and divide.

**Idea.** Maintain `prefix`, starting as `[1]`, where `prefix[i]` is the product of the first `i` numbers since the most recent zero. On `add(0)`, reset `prefix` to `[1]`. Otherwise append `prefix[last] * num`. For `getProduct(k)`: if `k >= prefix.length`, the window reaches the zero (or the very start before any zero, which k never exceeds), so return 0. Otherwise return `prefix[last] / prefix[last - k]`. The division is exact and never divides by 0, because all stored factors are non-zero. Each prefix is a contiguous product, so it fits in 32 bits.

**Steps**

1. Initialise `prefix = [1]`.
2. `add(num)`: if `num == 0`, reset `prefix = [1]`.
3. Otherwise append `prefix[last] * num`.
4. `getProduct(k)`: let `m = prefix.length`.
5. If `k >= m`, return 0, because the window includes the last zero.
6. Otherwise return `prefix[m-1] / prefix[m-1-k]`.

**Pseudocode**

```text
 1 │ function ProductOfNumbers()
 2 │   prefix ← [1]  // prefix[0] = 1 is the empty product, so a division always has a valid denominator
 3 │ function add(num)
 4 │   if num = 0
 5 │     prefix ← [1]  // every window that reaches this zero has product 0, so earlier prefixes are useless
 6 │   else
 7 │     last ← prefix[length(prefix) − 1]  // product of all numbers since the last zero
 8 │     append last × num to prefix  // new running product, still a contiguous product, so it fits in 32 bits
 9 │ function getProduct(k)
10 │   m ← length(prefix)  // m − 1 = how many numbers have come after the most recent zero
11 │   if k ≥ m
12 │     return 0  // the window covers more than the zero-free tail, so it includes the last zero
13 │   return prefix[m − 1] / prefix[m − 1 − k]  // exact division: all stored factors are non-zero
```

**Time complexity: `O(1) per call (amortised for append), O(q) for q calls`**

| Part | Cost | Why |
| --- | --- | --- |
| Constructor (lines 1-2) | 1 call × O(1) | It only creates a one-element list. |
| add (lines 3-8) | 1 call × O(1) amortised | Either a reset to [1], or one read, one multiplication and one dynamic-array append, which is amortised O(1). |
| getProduct (lines 9-13) | 1 call × O(1) | It reads the length, makes one comparison, does two indexed reads and one division. It never loops over k. |

- **Adding it up:** Each call costs O(1), so q calls cost q × O(1) = O(q). Compare this with O(k) per getProduct for the naive loop.
- **At the maximum input:** At most 4·10^4 calls → about 4·10^4 constant-time operations. That is well under a millisecond.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| prefix list (lines 2, 5, 8) | up to n + 1 integers | One entry per non-zero number added since the last zero, plus the leading 1. In the worst case (no zeros) that is all n added numbers. |

- **Adding it up:** Only the prefix list grows, so auxiliary space is O(n), where n is the number of add calls.
- **Not counted:** A reset on zero lets the list shrink back to size 1. There is no recursion.

**Dry run** on `ProductOfNumbers(), add(3), add(0), add(2), add(5), add(4), getProduct(2), getProduct(3), getProduct(4), add(8), getProduct(2)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | The constructor creates prefix = [1], which is the empty product. | `prefix = [1]` |
| 2 | 8 | add(3): 3 is non-zero, so last = prefix[0] = 1 and we append 1 × 3 = 3. | `num = 3`<br>`last = 1`<br>`prefix = [1, 3]` |
| 3 | 5 | add(0): any window that includes this zero has product 0, so prefix resets to [1] and the 3 is forgotten. | `num = 0`<br>`prefix = [1]` |
| 4 | 8 | add(2): last = 1, so we append 1 × 2 = 2. | `num = 2`<br>`last = 1`<br>`prefix = [1, 2]` |
| 5 | 8 | add(5): last = 2, so we append 2 × 5 = 10. | `num = 5`<br>`last = 2`<br>`prefix = [1, 2, 10]` |
| 6 | 8 | add(4): last = 10, so we append 10 × 4 = 40. prefix now holds the running products of 2, 5, 4. | `num = 4`<br>`last = 10`<br>`prefix = [1, 2, 10, 40]` |
| 7 | 10 | getProduct(2): m = 4, so 3 numbers have arrived since the last zero. Since k = 2 < 4, the window does not reach the zero. | `k = 2`<br>`m = 4`<br>`prefix = [1, 2, 10, 40]` (m-1→3) |
| 8 | 13 | The answer is prefix[3] / prefix[1] = 40 / 2 = 20, which equals 5 × 4. | `return = 20`<br>`prefix = [1, 2, 10, 40]` (m-1→3, m-1-k→1) |
| 9 | 13 | getProduct(3): m = 4 and k = 3 < 4, so the answer is prefix[3] / prefix[0] = 40 / 1 = 40, which equals 2 × 5 × 4. | `k = 3`<br>`return = 40`<br>`prefix = [1, 2, 10, 40]` (m-1→3, m-1-k→0) |
| 10 | 12 | getProduct(4): m = 4 and k = 4 ≥ 4, so the window [0,2,5,4] includes the zero and we return 0. | `k = 4`<br>`return = 0`<br>`prefix = [1, 2, 10, 40]` (m-1→3) |
| 11 | 8 | add(8): last = 40, so we append 40 × 8 = 320. | `num = 8`<br>`last = 40`<br>`prefix = [1, 2, 10, 40, 320]` |
| 12 | 10 | getProduct(2): m = 5 and k = 2 < 5, so the window stays inside the zero-free tail. | `k = 2`<br>`m = 5`<br>`prefix = [1, 2, 10, 40, 320]` (m-1→4) |
| 13 | 13 | The answer is prefix[4] / prefix[2] = 320 / 10 = 32, which equals 4 × 8. | `return = 32`<br>`prefix = [1, 2, 10, 40, 320]` (m-1→4, m-1-k→2) |

**Result:** The output is [null,null,null,null,null,null,20,40,0,null,32]. Each ratio of two prefixes is exactly the product of the last k non-zero numbers, and a k that reaches past the zero-free tail correctly gives 0.

**C++ solution**

```cpp
class ProductOfNumbers {
public:
    vector<int> prefix; // prefix[i] = product of the first i numbers since the most recent zero

    ProductOfNumbers() {
        prefix = {1}; // empty product; gives a safe denominator for every division
    }
    
    void add(int num) {
        if (num == 0) {
            prefix = {1}; // any window crossing this zero is 0, so discard older prefixes
        } else {
            prefix.push_back(prefix.back() * num); // contiguous product, guaranteed to fit in 32 bits
        }
    }
    
    int getProduct(int k) {
        int m = prefix.size(); // m - 1 numbers have arrived since the last zero
        if (k >= m) return 0; // window reaches back to the last zero
        return prefix[m - 1] / prefix[m - 1 - k]; // exact: all factors are non-zero
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
public:
    vector<int> prefix; // prefix[i] = product of the first i numbers since the most recent zero

    ProductOfNumbers() {
        prefix = {1}; // empty product; gives a safe denominator for every division
    }
    
    void add(int num) {
        if (num == 0) {
            prefix = {1}; // any window crossing this zero is 0, so discard older prefixes
        } else {
            prefix.push_back(prefix.back() * num); // contiguous product, guaranteed to fit in 32 bits
        }
    }
    
    int getProduct(int k) {
        int m = prefix.size(); // m - 1 numbers have arrived since the last zero
        if (k >= m) return 0; // window reaches back to the last zero
        return prefix[m - 1] / prefix[m - 1 - k]; // exact: all factors are non-zero
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

int main() {
    vector<string> ops = {"ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"};
    vector<int> args = {0,3,0,2,5,4,2,3,4,8,2};
    vector<string> expected = {"null","null","null","null","null","null","20","40","0","null","32"};
    ProductOfNumbers* obj = nullptr;
    vector<string> got;
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] == "ProductOfNumbers") { obj = new ProductOfNumbers(); got.push_back("null"); }
        else if (ops[i] == "add") { obj->add(args[i]); got.push_back("null"); }
        else { got.push_back(to_string(obj->getProduct(args[i]))); }
    }
    auto show = [](const vector<string>& v) {
        string s = "[";
        for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += v[i]; }
        return s + "]";
    };
    cout << "Output:   " << show(got) << "\n";
    cout << "Expected: " << show(expected) << "\n";
    cout << (got == expected ? "PASS" : "FAIL") << "\n";
    delete obj;
    return 0;
}
```

</details>

**Why this is the best:** Every query needs at least constant time, so this cannot be beaten asymptotically. The cost is O(n) memory, which the Better approach also needed. The method also relies on exact integer division, which only works because the zeros were removed.

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 3 of 8 | 2026-11-23 |

For comparison, the optimal approach (Prefix products reset on zero) runs in `O(1) per add and getProduct (amortised for append)` time and `O(n)` space.

```cpp
class ProductOfNumbers {
public:
    vector<long long> v;
    int lz = -1;
    ProductOfNumbers() {
        v.push_back(1);
    }
    
    void add(int num) {
        int n = v.size();
        if(num == 0)
        {
            lz = n+1;
            v.push_back(1);   
        }
        else
            v.push_back(v[n-1]*num);
    }
    
    int getProduct(int k) {
        int n = v.size();
        if(n-lz <k)    return 0;
        return v[n-1]/v[n-k-1];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
```

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| operations = ["ProductOfNumbers","add","add","add","getProduct","getProduct","getProduct"]<br>values = [[],[2],[3],[4],[1],[2],[3]] | [null,null,null,null,4,12,24] | Simple prefix products with no zeros. |
| operations = ["ProductOfNumbers","add","add","add","add","getProduct","getProduct","getProduct"]<br>values = [[],[5],[0],[3],[7],[2],[3],[4]] | [null,null,null,null,null,21,0,0] | Queries crossing a zero return 0. |
| operations = ["ProductOfNumbers","add","add","getProduct","add","getProduct","getProduct"]<br>values = [[],[1],[6],[2],[10],[1],[3]] | [null,null,null,6,null,10,60] | Interleaved adds and queries with ones. |
| operations = ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct"]<br>values = [[],[0],[2],[0],[3],[3],[2],[3]] | [null,null,null,null,null,null,9,0] | Multiple zeros, only last segment matters. |
| operations = ["ProductOfNumbers","add","add","add","getProduct","add","getProduct"]<br>values = [[],[4],[5],[2],[2],[3],[4]] | [null,null,null,null,10,null,120] | Query whole stream after extra add. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | operations = ["ProductOfNumbers","add","getProduct"]<br>values = [[],[7],[1]] | [null,null,7] | One add and k=1. |
| Single zero | operations = ["ProductOfNumbers","add","getProduct"]<br>values = [[],[0],[1]] | [null,null,0] | Product of only element is 0. |
| Zero last | operations = ["ProductOfNumbers","add","add","add","getProduct","getProduct"]<br>values = [[],[3],[4],[0],[1],[3]] | [null,null,null,null,0,0] | Every query includes it. |
| Max values | operations = ["ProductOfNumbers","add","add","add","getProduct"]<br>values = [[],[100],[100],[100],[3]] | [null,null,null,null,1000000] | Num=100 repeated. |
| All ones | operations = ["ProductOfNumbers","add","add","add","getProduct","getProduct"]<br>values = [[],[1],[1],[1],[1],[3]] | [null,null,null,null,1,1] | Product stays 1. |
| All zeros | operations = ["ProductOfNumbers","add","add","add","getProduct","getProduct"]<br>values = [[],[0],[0],[0],[1],[3]] | [null,null,null,null,0,0] | Every product is 0; large case would be 4*10^4 such calls. |

## Mistakes and edge cases

**Common mistakes**

- Not handling zeros and dividing `prefix[n]/prefix[n-k]` when the prefix includes a 0. This gives division by zero or a wrong 0 for windows that lie after the zero, such as `getProduct(2) = 20` in the example.
- Off-by-one in the zero check. With `prefix = [1, a, b]`, `k = 2` is valid (`b*a/1`), while `k = 3` reaches the zero and must return 0. The condition is `k >= prefix.length`, not `k > prefix.length`.
- Keeping one global prefix product across zeros by skipping zeros instead of resetting. Windows that span a zero then return a non-zero value, for example `getProduct(4)` in the example would not give 0.
- Never resetting at zeros, so the running product of the whole stream grows past 32 bits. The overflow guarantee only covers contiguous products, which the reset prefix always is.

**Edge cases to check**

- `getProduct(k)` where `k` equals exactly the count of numbers since the last zero: the answer must be `prefix[last] / prefix[0]`, not 0.
- `getProduct(k)` immediately after `add(0)`: `prefix = [1]`, so any `k >= 1` must return 0.
- A stream with no zeros at all: `k` never exceeds the stream length, so the `[1]` sentinel at the front makes `k = n` return the full product.
- Many consecutive zeros, such as `add(0)` repeated: each one resets the array, and queries return 0 until enough non-zero numbers arrive.
- Long runs of 1s: prefix values stay constant and the division still works. This is the case that makes the O(k) approaches slow.

## Practice next

- [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) · Same prefix-array idea with subtraction instead of division to answer range queries in O(1).
- [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) · Uses prefix and suffix products, and has to deal with the fact that zeros make division unusable.
- [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) · Zeros split the array into independent segments for products, just as the reset does here.
- [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) · Turns contiguous-range questions into prefix differences, the core trick reused here with products.

## Takeaways

- Range queries over a combine operation that has an inverse (+ with -, × with ÷) can be answered in O(1) using prefix aggregates.
- When the inverse fails on a special value (0 for multiplication), ask what that value implies. Here it makes everything before it irrelevant, so you reset rather than patch around it.
- A sentinel at the front (`prefix = [1]`) removes the special case for windows that start at the very beginning.
- Read overflow guarantees precisely. "Any contiguous product fits" tells you which stored values are safe, and that should shape your design.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
