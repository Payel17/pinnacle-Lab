#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){

    const int MIN = 1;
    const int MAX = 100;
    int guess;
    int guesses;
    int answer;
    srand(time(0));

    answer= (rand() % MAX) + MIN;

    do
    {
        printf("\nEnter a guess: ");
        scanf("%d", &guess);

        if (guess>answer)
        {
            printf("High, try again.\n");
        }
        else if (guess<answer)
        {
            printf("Low, try again.\n");
        }
        else
        {
            printf("Correct !!!\n");
        }
        guesses++;

    } while (guess != answer);

    printf("\n\n*********** Game Over *********\n");
    printf("Answer: %d\n",answer);
    printf("Guesses: %d\n",guesses);
    printf("*******************************");

    return 0;
}
