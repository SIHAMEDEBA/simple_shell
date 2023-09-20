#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/**
 * main - function of the shell program.
 *
 * @argc: number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: Returns integer
 */
int main(int argc, char **argv);

/**
 * tokenization - input line into an array of arguments.
 *
 * @inputLine: The input line to be tokenized
 * @argv: array of strings store the tokens
 * @charsRead: char read
 *
 * Return: returns number of tokens or -1 error.
 */

int tokenization(char *inputLine, char **argv, ssize_t charsRead);

/**
 * execmd -  command with the given arguments.
 *
 * @argv: array of strings
 * Return: void
 */
void execmd(char **argv);

#endif
