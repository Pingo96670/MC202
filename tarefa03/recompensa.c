#include <stdio.h>

// Recursive function to calculate probability of receiving the reward
// There may be a much more efficient method
float dice_roll(int n, int x, float *chance) {
    if (x<0 || n<0) {
        return 0;
    }

    else if (x==0) {
        return 1;
    }

    else {
        return 1.0/6.0*(dice_roll(n-1, x-1, chance)+
                        dice_roll(n-1, x-2, chance)+
                        dice_roll(n-1, x-3, chance)+
                        dice_roll(n-1, x-4, chance)+
                        dice_roll(n-1, x-5, chance)+
                        dice_roll(n-1, x-6, chance));
    }
}

int main() {
    int n, x;
    float chance=0;

    scanf("%d %d", &n, &x);

    printf("%.3f", dice_roll(n, x, &chance));

    return 0;
}