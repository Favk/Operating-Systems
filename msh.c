// The MIT License (MIT)
//
// Copyright (c) 2016 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*
	Name: Favour Kolade
	ID: 1001860786
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n" // We want to split our command line up into tokens
						   // so we need to define what delimits our tokens.
						   // In this case  white space
						   // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255 // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5 // Mav shell only supports four arguments

int main(){
	char *command_string = (char *)malloc(MAX_COMMAND_SIZE);
	pid_t pids[20];
	int pid_num = 0;
	char *history[15];
	for (int i = 0; i < 15; i++){
		history[i] = (char *)malloc(MAX_COMMAND_SIZE);
	}
	int hist = 0;

	while (1){
		// Print out the msh prompt
		printf("msh> ");
		
		// Read the command from the commandline.  The
		// maximum command that will be read is MAX_COMMAND_SIZE
		// This while command will wait here until the user
		// inputs something since fgets returns NULL when there
		// is no input
		while (!fgets(command_string, MAX_COMMAND_SIZE, stdin));

		/* Parse input */
		char *token[MAX_NUM_ARGUMENTS];

		int token_count = 0;

		// Pointer to point to the token
		// parsed by strsep
		char *argument_ptr;

		char *working_string = strdup(command_string);

		// check if n in !n is in history array
		if (command_string[0] == '!'){
			int index = atoi(&command_string[1]);
			if (index > hist){
				printf("Command not in history\n");
			}
			strcpy(working_string, history[index]);
		}

		strncpy(history[hist++], command_string, MAX_COMMAND_SIZE);
		if (hist > 14 ){
			hist = 0;
		}

		// we are going to move the working_string pointer so
		// keep track of its original value so we can deallocate
		// the correct amount at the end
		char *head_ptr = working_string;

		// Tokenize the input strings with whitespace used as the delimiter
		while (((argument_ptr = strsep(&working_string, WHITESPACE)) != NULL) && 
		(token_count < MAX_NUM_ARGUMENTS)){
			token[token_count] = strndup(argument_ptr, MAX_COMMAND_SIZE);
			if (strlen(token[token_count]) == 0){
				token[token_count] = NULL;
			}
			token_count++;
		}

		// exit the shell quit is entered
		if(token[0] != NULL && strcmp(token[0], "quit") == 0){
			exit(0);
		}
		// else if exit when exit is entered
		else if (token[0] != NULL && strcmp(token[0], "exit") == 0){
			exit(0);
		}
		// else if for cd, xhange your current directory
		else if (token[0] != NULL && strcmp(token[0], "cd") == 0){
			if (chdir(token[1]) != 0 ){
				printf("Directory is not found\n");
			}
		}
		// else if for history, see all the commands you've put into the shell
		else if (token[0] != NULL && strcmp(token[0], "history") == 0){
			for (int i = 0; i < hist; i++){
				printf("[%d]: %s", i, history[i]);
			}
		}
		// else if for listpids, list the pids of the current processes
		else if (token[0] != NULL && strcmp(token[0], "listpids") == 0){
			for (int i = 0; i < pid_num; i++){
				printf("%d: %i\n", i, pids[i]);
			}
		}
		// else
		else{
			pid_t pid = fork();
			if (pid_num > 19){
				pid_num = 0;
			}
			else{
				pids[pid_num++] = pid;
			}

			if (pid == 0){
				int ret = execvp(token[0], &token[0]);
				if (ret = -1){
					printf("%s: Command not found.\n\n", token[0]);
					exit(0);
				}
			}
			else{
				int status;
				wait(&status);
			}
		}

		free(head_ptr);
	}
		return 0;
}