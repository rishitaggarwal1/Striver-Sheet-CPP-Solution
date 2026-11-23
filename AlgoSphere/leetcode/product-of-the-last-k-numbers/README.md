# Product of the Last K Numbers

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/product-of-the-last-k-numbers/)

**Contents:** [Problem](#problem) · [Hints](#hints) · [Test cases](#test-cases)

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

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
