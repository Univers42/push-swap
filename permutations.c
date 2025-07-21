# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

//simly print each node of the array
void print_permutation(int *curr, int curr_size)
{
    int i;;

    i = -1;
    while (++i < curr_size)
        printf("%d", curr[i]);
    printf("\n");
}

/**
 * in permutation backtracking, we want each permutation touse every
 * nnumber exactlu once.
 * This `is_used` function checks if a number is allready in the current
 * partial permuatiaon (curr)
 * - if (curr[i] == num), it means is alread chose for this posiiton,
 * so we skip it for the next postion
 * why ?
 * without this check, we could have permutations like `[1], [2], [3]`
 * whic are not valid (numbers repeat)
 * with the check, we only get permutation s like `1,2,3 or 2,3,1` where
 * each number appears once.
 * The check ensures each number is uses ony once per permmutation
 * it's essentiall fo rgenerating all unique permutations of the input
 * array
 */
bool is_used(int *curr, int curr_size, int num)
{
    int i;

    i = -1;
    while (++i < curr_size)
        if (curr[i] == num)
            return (true);
    return (false);
}

/**
 * the function `backtrcak` recursive fills the `curr` array, one number at a time, 
 * making sure each number is only used once per permutation.
 * When `curr_size == num_size`, it means the permutation is complete (all position)
 * are filled
 * at this point we print the permutation and return
 * Exploring all path:
 * The `while` loop tries every possible unused number for the next positin:
 * For each choice, it recurses deeper building up the permutation.
 * 
 */
void backtrack(int *curr, int curr_size, int *nums, int nums_size)
{
    int i;
    if (curr_size == nums_size)
    {
        print_permutation(curr, curr_size);
        return ;
    }
    i = -1;
    while (++i < nums_size)
    {

        if (!is_used(curr, curr_size, nums[i]))
        {
            curr[curr_size] = nums[i];
            backtrack(curr, curr_size + 1, nums, nums_size);
        }
    }
}

void permute(int *nums, int nums_size)
{
    int *curr;

    curr = malloc(sizeof(int) * nums_size);
    if (!curr)
        return ;
    backtrack(curr, 0, nums, nums_size);
    free(curr);
}

void permute_possibility(int numsSize)
{
    int i;
    int res;

    i = numsSize + 1;
    res = 1;
    while (--i)
        res = res * i;
    printf("%d\n", res);
}

int main()
{
    int nums[] = {1, 2, 3};
    permute_possibility(5);
    permute(nums, 3);
    return (0);
}