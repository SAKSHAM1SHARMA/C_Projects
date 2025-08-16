#include <stdio.h>

int main()
{
	int menu_option;
	do
	{

		printf("1.Add \n 2.Subtraction \n 3.Multiplication \n 4.Division \n 5.Exit \nEnter the option you want to calculate:");
		scanf("%d", &menu_option);
		float first, second, result;
		switch (menu_option)
		{
		case 1:
			printf("Enter two numbers to add: ");
			scanf("%f %f", &first, &second);
			result = first + second;
			printf("Result: %.2f\n", result);
			break;
		case 2:
			printf("Enter two numbers to subtract: ");
			scanf("%f %f", &first, &second);
			result = first - second;
			printf("Result: %.2f\n", result);
			break;
		case 3:
			printf("Enter two numbers to multiply: ");
			scanf("%f %f", &first, &second);
			result = first * second;
			printf("Result: %.2f\n", result);
			break;
		case 4:
			printf("Enter two numbers to divide: ");
			scanf("%f %f", &first, &second);
			if (second != 0)
			{
				result = first / second;
				printf("Result: %.2f\n", result);
			}
			else
			{
				printf("Error: Division by zero is not allowed.\n");
			}
			break;
		case 5:
			printf("Exiting the calculator.\n");
			return 0;
		default:
			printf("Invalid option. Please try again.\n");
		}
		return 0;
	} while (menu_option != 5);
}
