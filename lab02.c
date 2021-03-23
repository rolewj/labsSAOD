#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
 
typedef struct student{
	int id;
	char name[128];
	char group[12];
	int grade;
} Student;

void print_student(Student* student){
	printf("%d %s %d %s \n", student->id, student->group, student->grade, student->name);
}

int main(int argc, char** argv){
	FILE* file = fopen("students.txt", "r");
	int size;
	fscanf(file, "%d", &size); 
	Student* array = (Student*) malloc(sizeof(Student) * size);
	for (int i=0; i != size; i++){
		fscanf(file, "%d%s%d", &array[i].id, array[i].group, &array[i].grade);
		fgets(array[i].name, 127, file);
	}

	if (strcmp("-uid", argv[1]) == 0){
		int id = atoi(argv[2]);
		printf("Студент с id: %d\n", id);
		for (int i = 0; i!=size; i++){
			if (array[i].id == id){
				print_student(&array[i]);
			}
		}
	}

	if (strcmp("-n", argv[1]) == 0){
		printf("Студент с частью имени: %s\n", argv[2]);
		for (int i = 0; i!=size; i++){
			if (strstr(array[i].name, argv[2]) != NULL){
				print_student(&array[i]);
			}
		}
	}

	if (strcmp("-g", argv[1]) == 0){
		printf("Студенты группы: %s\n", argv[2]);
		for (int i = 0; i!=size; i++){
			if (strcmp(array[i].group, argv[2]) == 0){
				print_student(&array[i]);
			}
		}
	}

	if (strcmp("-b", argv[1]) == 0){
		int av_grade = atoi(argv[2]);
		for (int i=0; i!=size; i++){
			if (array[i].grade>av_grade){
				print_student(&array[i]);
			}
		}
	}
		
	free(array);
	return 0;
}
