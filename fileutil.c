#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an array of strings (arr).
	// Set an initial capacity of 10
	int capacity = 10;
	// Initialize the parent array with capacity
	char **arr = malloc(capacity * sizeof(char *));

	// Initialize a temporary variable to hold the read lines
	char buffer[255];
	// Initialize a counter to keep track of entries and to use for indexing
	int count = 0;

	// Read the file line by line.
    while (fgets(buffer, sizeof(buffer), in))
	{
		//   Trim newline.
		buffer[strcspn(buffer, "\n")] = 0;

		//   Expand array if necessary (realloc).
		if (count >= capacity)
		{
			// Increase capacity by 10 if the number of indices have already reached capacity
			capacity += 10;
			// reallocate the array to the new memory space
			arr = realloc(arr, capacity * sizeof(char *));
		}

		//   Allocate memory for the string (str).
		//   Attach the string to the large array (assignment =).
		arr[count] = malloc((strlen(buffer) + 1) * sizeof(char)); // +1 for the null terminator

		//   Copy each line into the string (use strcpy).
		strcpy(arr[count], buffer);

		// Increment the count to move to the next index
		count++;
	}
    // Close the file.
	fclose(in);

	// The size should be the number of entries in the array.
	*size = count;
	
	// Return pointer to the array of strings.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		// if match found then return the line
		if (strstr(lines[i], target) != NULL)
			{
				return lines[i];
			}
	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	// Using pointer to a pointer, so have to iterate through the parent array and free each element which are also pointers
	for (int i = 0; i < size; i++)
	{
		free(arr[i]);
	}
	// now free the parent array
	free(arr);
}
