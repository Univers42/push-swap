# Push swap an efficient algorithm to sort two stacks

## Good pedagogical exercice
While a lot of people might discuss the logic behind this project because of its not real world representive. 
Push swap is pedagoogical and aim people who want ot build  their frist soritng algorithm to a deep level of
understanding.

## Mathematical logic behind permutations
how many ways I can sort this stack ? well there is a mathematical formula that says the  following
`P(n, r) = n! / (n-r)!`

All  the issue with  Push swap is about understanding the permutations, and that using any algorithm...
the only algorithm that can do that is the `greedy algorithm` considered for long as a good solution among other solutions. The greedy algorithm alone is maybe not efficient enough for this exercice so to increase speedness of movements, we can  try only to create ann hybrid program that would the job correctly.

### Explanation:
this formula is created in the idea that to chose the first element, we have `N` possibilities.  then we choose the second element, there is only left `(n - 1)` choice,  so forth, and so on...
if we have `books = 5` and that we want to chose 3 to place them on a stage ( the order would be important, so we use the permutations)
`P(5, 3) = 5!/(5 - 3)! = 5! / 2! = (5 * 4 * 3 *2 * 1) / (2 * 1) = 60` => 60 ways to sort the book

but in our case we have simpler choice, to do, what are the movmenent of permutations we have as maximum ?
well we can 

so we can think of creating an algorithm that parse 500 numbers really fastly, the best solution would to chose primarily at least, a permutation but :
`500! ~= 1.22 x 10^1134 (a number with other 1000 digits)` this is insane litterally.

## RADIX_SORT < GREEDY < CHUNK SORT < HYBRID
### RADIX_SORT
The  monst common and that shouldn't pass the the project but at least interesting to know.
because it's : 
- predictable
- constant
- scalable
- don't rely on comparison based algorithm
- O(n log n) in complexity

You take each number and  look at its `binary representation`, then:
1. On each "bit pass" we move numbers on that bit
- 0? "push to stack B" : "rotate Stack A"d
2. bring them back
3. loop : LSB -> MSB

with this algorithm we would need  `2^9 = 512`
- so we'll do at best 6000 moves total, we cold not create better than that,, the rest is about optimizations

### GREEDY SCORING INSERTION
For each element in stack B, we calculate:
1. For each element in stack B, we calculate:
- how many moves it would take ot get it into the correct position in A
2. Pick the cheapest  one (fewest combined moves)
3. Execute the moves
4. Repeat until stack B is empty

For each node in B:
- moves_b : number or `rb` or `rrb` needed to bring it to top of B
- moves_a : nnumber of `ra`or `rra`needed to place it in correct sport in A
- total_moves = best combo of moves_a + moves_b (possibly using `rr` or `rrr` together)

step:
- Define stack node
-  Assign positions to elements
- Find target position in A for each B node
- calculate costs
- pick the cheapest move
- execute moves to push cheapest
- loop until B is empty
- Final touch :  rotate A to correct position

```c
void big_sort(t_stack **a, t_stack **b)
{
	push_half_to_b(a, b);       // push all but 3 to B
	sort_three(a);              // sort the remaining 3
	sort_with_scoring(a, b);    // greedy insert back
	final_rotate_a(a);          // fix final rotation
}
```
### CHUNK SORTING
### DYNAMI PROGRAMMING FOR SMALL PARTS
### A* searchh or BFS on small stacks


## BONUS

### CHECKER CREATION

### VIZUALIZER TERMINAL OF DATAS
