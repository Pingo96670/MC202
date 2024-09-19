#include <stdio.h>

// Recursive function to calculate probability of receiving the reward
// Checks odds in a "tree-like" manner, which ends up going through all possible roll combinations that reach the given sum x in n or less rolls
// When all recursive calls reach an endpoint, adds up each "branch"'s probability, which is finally returned to main call

// There may be a much more efficient method
float dice_roll_prob_tree(int n, int x) {
    // Roll combinations exceed x or n attempts, returning 0
    if (x<0 || n<0) {
        return 0;
    }

    // Roll combinations reach x, returning 1, which is then multiplied by 1/6 in parent call for actual odds
    else if (x==0) {
        return 1;
    }

    // Checks all possible results for the following roll
    else {
        return 1.0/6.0*(dice_roll_prob_tree(n-1, x-1)+
                        dice_roll_prob_tree(n-1, x-2)+
                        dice_roll_prob_tree(n-1, x-3)+
                        dice_roll_prob_tree(n-1, x-4)+
                        dice_roll_prob_tree(n-1, x-5)+
                        dice_roll_prob_tree(n-1, x-6));
    }
}

int main() {
    int n, x;

    scanf("%d %d", &n, &x);

    printf("%.3f", dice_roll_prob_tree(n, x));

    return 0;
}