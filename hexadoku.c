/*


email: skumar19@binghamton.edu

Algorithm based on the code found at:  http://pythontips.com/2013/09/01/sudoku-solver-in-python/

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define CHAR "0123456789ABCDEF"

//Checks if two cells belong to the same row
bool same_row(int i,int j){
	return ((i/16) == (j/16));
}
//Checks if two cells belong to the same column
bool same_col(int i, int j){
	return ((((i-j))%16) == 0);
}

//Checks if two cells belong to the same block
bool same_block(int i, int j){

    int floor_i1 = (i/(4*4*4));
    int floor_j1 = (j/(4*4*4));
    int floor_i2 = ((i%16)/4);
    int floor_j2 = ((j%16)/4);

    return ((floor_i1 == floor_j1) && (floor_i2 == floor_j2));
}

//Verifier function that verifies that each entry in the puzzle doesn't violate the constraints

bool verify(char *output){

	int i=0, j=0;
	for(i=0;i<256;i++){

		for(j=0;j<256;j++){
			
			if(same_col(i,j)||same_row(i,j)||same_block(i, j)){
		
				if(output[i]==output[j] && i!=j){

					return false;
				}

			}

		}
	}

	return true;
}

//A find function that checks if the given character is present and if present - returns the first index of its occurence 

int find(char *p, char c){

	int len = strlen(p);
	int i = 0;

	for(i=0; i<len; i++){
		if(*(p+i)==c){
			return i;
		}
	
	}
	return -1;
}

//The generate function that processes the input string and generates the output string that solves the Hexadoku

char *generate(char *input){

	int j=0;
	int count =0;
	int i = find(input,'.');

//If there are no blanks, this block verifies if the solution is valid

        if(i<0){

		bool v;

		v= verify(input);

		//If block that returns the solution if valid
		if(v){
			char* retval = malloc(sizeof(char)*16*16);
			int k = 0;
			for(k = 0; k < sizeof(char)*16*16; k++){
				retval[k] = input[k];
			}	
			return retval;

		}//Else block that executes if there are no valid solutions
		else{
			printf("\n\n No Valid Solution \n\n");

			return NULL;

		}
		
	}

//Code block that adds the characters to be excluded in to an array 

	char ex_num[16*3];
	int ex_num_index = 0;
	for(j=0; j < (16*16); j++){

		if(same_row(i,j)||same_col(i,j)||same_block(i,j)){
			ex_num[ex_num_index++]=input[j];
		}
	}
	ex_num[ex_num_index]='\0';

//Recursive code block that generates the required solution

	for(j=0;j<16;j++){
		int found;
		found = find(ex_num,CHAR[j]);

//If the character is not in the excluded list, we attempt to recurse with it  

		if(found<0){
			int x=0;
			int rec_arr_index = 0;
			char rec_arr[257];
			for(x=0;x<strlen(input);x++){
				rec_arr[rec_arr_index++]=input[x];
			}
			rec_arr[256] = '\0';

			rec_arr[i]=CHAR[j];
			char *temp = generate(rec_arr);

			if(temp!=NULL){
				return temp;
			}
		}

	}

	 
	return NULL;
}

int main(){

	char *input = "0...........................................................................2...............................................A..................................................F................................3...............................................";

       char *output = generate(input);
       if(output!=NULL){
       		printf("\n\n%s\n\n",output);

	}
       free(output);
}
