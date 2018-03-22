/*
 ============================================================================
 Name        : TodoApp.c
 Author      : Universitas Nahdlatul Ulama Indonesia
 Version     :
 Copyright   : GPLv2
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	/** Table Header */
	puts("#    Task                            Status    Due Date");
	/** Header Line */
	puts("-------------------------------------------------------");

	/**
	 * TODO ambil data dari database
	 * Menampilkan list task
	 */
	char task[3][53] = {
		"Membuat Flow Chart",
		"Membuat Design Task View",
		"Membuat Design New Task"
	};

	char due[3][10] = {
		"2018-03-01",
		"2018-03-01",
		"2018-03-01"
	};

	char status[3][10] = {
		"Done",
		"Done",
		"Pending"
	};

	int i;
	int iTask;
	int iStatus;
	int iDue;
	int totalKarakterKolomTask = 32; /** Total Karakter untuk kolom Task */
	int totalKarakterKolomStatus = 10; /** Total Karakter untuk kolom Status */
	char spasi[4] = "    ";
	for (i=0; i < 3; i++) {
		/** Nomor */
		printf ("%d    ", (i + 1));

		/** Task */
		for (iTask = 0; iTask < totalKarakterKolomTask; iTask++) {
			if (task[i][iTask] == '\0') {
				printf(" ");
			} else {
				printf("%c", task[i][iTask]);
			}
		}

		/** Status */
		for (iStatus = 0; iStatus < totalKarakterKolomStatus; iStatus ++) {
			if (status[i][iStatus] == '\0') {
				printf (" ");
			} else {
				printf("%c", status[i][iStatus]);
			}
		}


		/** Due Date */
		for (iDue = 0; iDue < 10; iDue++) {
			if (due[i][iDue] == '\0') {
				printf (" ");
			} else {
				printf("%c", due[i][iDue]);
			}
		}

		/** New Line */
		printf ("\n");
	}

	return 0;
}
