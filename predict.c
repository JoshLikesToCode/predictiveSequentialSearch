#include <stdio.h>
#include <stdlib.h>

static int last_value = 0;
static int last_index = -1;
static int predict_steps = 0;
static int regular_steps = 0;
static int regular_searches = 0;
static int predicted_searches = 0;

void find_item(int* arr, int size, int key);

int main()
{
	printf("Enter size of your array\n");
	int size, i;
	scanf("%d", &size);
	int *arr = malloc(size * sizeof(*arr));
	printf("Enter the elements of the array in ascending order: ");
	for(int i = 0; i < size; i++)
		scanf("%d", &arr[i]);

	printf("[ ");
	for(int i = 0; i < size; i++)
		printf("%d, ", arr[i]);
	printf("]\n");

	int c;
	printf("Type X to cancel.\n");
	while((c = getchar()) != 'X')
	{
		printf("What is the number you are looking for?\n");
		int number;
		scanf("%d", &number);
		find_item(arr, size, number);
	}
	if(regular_searches > 0)
	{
		printf("Regular searches on average took %d steps.\n", (regular_steps/regular_searches));
	} else {
		printf("You didn't do any regular searches.");
	}

        if(predicted_searches > 0)
        {
                printf("Predicted searches on average took %d steps.\n", (predict_steps/predicted_searches));
        } else {
                printf("You didn't do any predicted searches.");
        }


}

void find_item(int* arr, int size, int key)
{
	printf("Do you want us to predict this search? Enter 1 for yes and 0 for no.\n");
	int predict_flag = 1;
	fflush(stdout);
	scanf("%d", &predict_flag);
	int i = 0;

	switch(predict_flag)
	{
		case 1:
			if(last_index >= 0)
			{
                		if(last_value > key)
                		{
                    			i = last_index-1;
                    			if(i < 0)
                    			{
                        			i += 1;
					}
                   	 		int x = 0;
					for(; i >= 0; i--)
					{
                        			x++;
						if(arr[i] == key)
						{
                            				last_index = i;
                            				last_value = key;
                            				printf("1 - The key of %d was found in %d steps.\n", key, x);
                            				predict_steps += x;
                           	 			predicted_searches++;
                            				return;
						}
					}
					for(int j = 0; j < size; j++)
					{
						if(arr[j] == key)
						{
							last_index = j;
							last_value = key;
							printf("2 - The key of %d was found in %d steps.\n", key, x+j);
							predict_steps += (x+j);
							predicted_searches++;
							return;
						}
					}
               	}
                else if(last_value < key)
                {
                	i = last_index+1;
                    
                	if(i > size)
                	{
              			i -= 1;
                	}
                	int z = 0;
                	for(; i < size; i++)
                	{
                		z++;
                        	if(arr[i] == key)
                        	{
                        		last_index = i;
                            		last_value = key;
                            		printf("3 - The key of %d was found in %d steps.\n", key, z);
                            		predict_steps += i;
                            		predicted_searches++;
                            		return;
                        	}
			}
			for(int j = 0; j < size; j++)
			{
				if(arr[j] == key)
				{
					last_index = j;
					last_value = key;
					printf("4 - The key of %d was found in %d steps.\n", key, z+j);
					predict_steps += (z+j);
					return;
				}
			}

                }
		else if(last_value == key)
		{
			i = last_index;
			printf("The key of %d was found in 0 steps.\n", key);
			predicted_searches++;
			return;
		}

		printf("The key you were looking for doesn't exist.\n");
		predict_steps += size;
		predicted_searches++;
		return;
		}

		printf("You must do a previous search before we can predict. We will do a non-predictive search this time.\n");
		for(; i < size; i++)
		{
			if(arr[i] == key)
			{
				last_value = key;
				last_index = i;
				printf("5 - The key of %d was found in %d steps.\n", key, i);
				regular_steps += i;
				regular_searches++;
				return;
				}
			}
		printf("The key wasn't found\n");
		regular_steps += i;
		regular_searches++;
		return;

	case 0:
		for(; i < size; i++)
                {
                    if(arr[i] == key)
                    {
                        last_value = key;
			last_index = i;
                        printf("The key of %d was found in %d steps.\n", key, i);
                        regular_steps += i;
			regular_searches++;
			return;
                    }
                }
                printf("The key wasn't found\n");
		regular_steps += size;
		regular_searches++;
		return;
    }
}
