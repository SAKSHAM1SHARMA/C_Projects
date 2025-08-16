#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int random,users_number;
	int number_of_guesses = 0;
	srand(time(NULL));
	
	printf("Welcome to the number guessing game UwU\n");
	random = rand() % 100 + 1;//random number generation
	
	do{
		printf("Enter the number you think I have between (1 to 100):");
		scanf("%d",&users_number);
		number_of_guesses++;
		
		if(users_number > random){
			printf("That's not the number I have try guessing smaller one.\n");
		}
		
		else if(users_number<random){
			printf("Guess larger number.\n");
		}
		else{
			printf("You have correctly guessed the number in %d attempts.\n",number_of_guesses);
		}
		
	}while(users_number != random);
	
	printf("Thanks for playing See you soon.");
	
	
	return 0;
}
