/*
 ============================================================================
 Name        : TodoApp.c
 Author      : Universitas Nahdlatul Ulama Indonesia
 Version     :
 Copyright   : GPLv2
 Description : TodoApp
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Struktur Task
 */
struct Tasks
{
	int id;
	char task[32];
	char status[10];
	char due[10];
};

int totalTask = 3;
struct Tasks records[10];

void printSpace(int length, int max)
{
	int totalSpace = max - length;
	int i;
	for (i = 0; i < totalSpace; i++) {
		printf (" ");
	}
}

void newTask()
{
	char task[32];
	char inputTask[32];
	char due[10];
	char inputDue[10];
	struct Tasks _task;

	puts("New Task");
	/** Header Line */
	puts("-------------------------------------------------------");
	puts ("Task:");
	scanf (" %[^\n]s", inputTask);

	puts ("Due Date:");
	scanf (" %[^\n]s", inputDue);

	strncpy(_task.task, inputTask, 32);
	strncpy(_task.due, inputDue, 10);
	strncpy(_task.status, "Pending", 10);
	_task.id = totalTask + 1;
	records[totalTask] = _task;
	totalTask++;
}

void markAsDone(int index)
{
    records[index].status = 'Done';
}

int main(void)
{
	char anyKey[20];
	char ch;
	/**
	 * Dummy Data
	 */
	records[0].id = 1;
	strcpy (records[0].task, "Membuat Flow Chart");
	strcpy (records[0].status, "Done");
	strcpy (records[0].due, "2018-03-01");

	records[1].id = 2;
	strcpy (records[1].task, "Membuat Prototype Design");
	strcpy (records[1].status, "Done");
	strcpy (records[1].due, "2018-03-01");

	records[2].id = 3;
	strcpy (records[2].task, "Membuat User Interface");
	strcpy (records[2].status, "Pending");
	strcpy (records[2].due, "2018-10-01");

	puts ("[ Ctrl+N ] New Task");
	/** Table Header */
	puts("#    Task                            Status    Due Date");
	/** Header Line */
	puts("-------------------------------------------------------");

	/**
	 * Loop and print data
	 */
	int i;
	for (i = 0; i < 10; i++) {
		/**
		 * Skip jika karakter pertama pada task adalah NULL
		 * yang berarti tidak ada record pada index tersebut!
		 */
		if (NULL == records[i].task[0]) {
			continue;
		}
		printf ("%d    ", (i + 1));
		printf ("%s", records[i].task);
		printSpace(strlen(records[i].task), 32);

		printf ("%s", records[i].status);
		printSpace(strlen(records[i].status), 10);

		printf ("%s", records[i].due);
		printf ("\n");
	}

	do {
		//puts("Enter some text :");
		scanf("%s", anyKey);

		if ( !strcmp(anyKey, "\007") ) {
			newTask();
		}

		else {
			printf("Nope - I do not recognise that phrase.... \n");
		}

		printf("Try again? (y/n) : ");
		scanf(" %c%*c", &ch);
	} while( toupper(ch) != 'N' );

	return 0;
}
