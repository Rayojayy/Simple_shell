#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry point for a basic UNIX command line interpreter.
 *
 * Displays a prompt, accepts single-word commands, and executes them.
 * Repeats until an error or Ctrl+D is encountered. Handles basic errors.
 * executeCommand - Execute a command using execve
 * @command: The command to execute
 *
 * This function executes specified command using execve and handle any error
 * It handles any execution error and exit the child process in case of failure
 *
 * Return: Always returns 0
 */

void executeCommand(const char *command)
{
	char *argv[] = {NULL, NULL};

	argv[0] = (char *)command;


	if (execve(command, argv, NULL) == -1)
	{
		perror("Command execution failed");
		_exit(1);
	}
}


int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	pid_t child_pid;

	while (1)
	{
		printf("simple_shell$ ");
		fflush(stdout);

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		child_pid = fork();

		if (child_pid < 0)
		{
			perror("Fork failed");
			_exit(1);
		} else if (child_pid == 0)
		{
			if (execlp(command, command, NULL) == -1)
			{
				perror("Command not found");
				_exit(1);
			}
		} else
		{
			int status;

			waitpid(child_pid, &status, 0);
		}
	}

	return (0);
}
