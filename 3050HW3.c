#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
} node;

struct Queue {
	struct Node* head;
	struct Node* tail;
} queue;

struct Queue* findPath(int*, int, int, int, int, int);
void enQueue(struct Queue *q, int data);
int deQueue(struct Queue *q);

int main(int argc, char* argv[]){
	int comm_line1=argc;
	if(comm_line1!=6){
		printf("Incorrect number of command line arguments. Please run the program while entering f,s,g,u, and d. \n");
		return 0;
	}

  int floors=atoi(argv[1]);
	if(floors >100){
		printf("The number of floors cannot be greater than 100.\n");
		return 0;
	}

	int start=atoi(argv[2]);
	if(start <1){
		printf("The starting floor must be greater than or equal to 1.\n");
		return 0;
	}

	int goal=atoi(argv[3]);
	if(goal>floors || goal <1){
		printf("The goal must be between 1 and the number of floors.\n");
		return 0;
	}
  int up=atoi(argv[4]);
	if(up<0){
		printf("The number of floors going up cannot be negative.\n");
		return 0;
	}
  int down=atoi(argv[5]);
	if(down > 100){
		printf("The number of floors going down must be less than 100.\n");
		return 0;
	}

  printf("Floors=%d\n", floors);
  printf("start=%d\n", start);
  printf("goal=%d\n", goal);
  printf("up=%d\n", up);
  printf("down=%d\n", down);

	int floorArray[floors];
	int i =0;
	for(i=0; i<floors; i++){
		floorArray[i]=-1;
	}

	struct Queue* hold=findPath(floorArray, floors, start, goal, up, down);

	if(hold->tail->prev==NULL)
		printf("Take the stairs.\n");
	else{
		struct Node *tmp = NULL;
		while(hold->tail !=NULL){
			printf("%d->", hold->tail->data);
			tmp=hold->tail;
			hold->tail=hold->tail->prev;
			free(tmp);
		}
			printf("%d\n", goal);
	}

	return 0;
}

struct Queue* findPath(int*floorArray, int floors, int start, int goal, int up, int down){
		struct Queue* queue = malloc(sizeof(struct Queue));
		queue->head=NULL;
		queue->tail=NULL;

		int current;
		struct Queue* path=malloc(sizeof(struct Queue));
		path->head=NULL;
		path->tail=NULL;

		enQueue(queue, start-1);
		floorArray[start-1]=-2;

		while(current !=-1){
			if(current==goal){
				while (floorArray[current]!=-2) {
					enQueue(path, current+1);
					current=floorArray[current];
				}
				enQueue(path, start);
				break;
			}
			else{
				if(current+up < floors && floorArray[current+up]==-1){
					enQueue(queue, current+up);
					floorArray[current+up]=current;
				}
				if(current-down >= 0 && floorArray[current-down]==-1){
					enQueue(queue, current-down);
					floorArray[current-down]=current;
				}
			}
			current=deQueue(queue);
		}
					return path;
}
void enQueue(struct Queue* q, int data){
	if (q->head == NULL) {
		q->head = (struct Node *) malloc(sizeof(struct Node));
		q->head->data = data;
		q->head->next = NULL;
		q->head->prev=NULL;
		q->tail = q->head;
	} else {
		q->tail->next = (struct Node *) malloc(sizeof(struct Node));
		q->tail->next->data = data;
		q->tail->next->next = NULL;
		struct Node* tmp=q->tail;
		q->tail = q->tail->next;
		q->tail->prev=tmp;
	}
}

int deQueue(struct Queue *q) {
	int index=0;
	struct Node *hold = q->head;
	q->head = hold->next;
	index=hold->data;
	free(hold);

	return index;
}


/*	int current=start;
	int hold[floors];
	int count=0;
	hold[count]=start;
	while(current<floors){
		if(current==goal){
			count++;
			hold[count]=goal;
			break;
		}
		if(goal<current && down==0)
			break;
		if(goal<current){
			current=current-down;
			count++;
			hold[count]=current;
		}
		if(goal>current && up ==0)
			break;
		if(goal>current){
			current=current+up;
			count++;
			hold[count]=current;
		}
	}

	if(current!=goal){
	printf("Take the stairs\n");
	}
	else{
	int i;
		for(i=0; i<count; i++){
			printf("%d->", hold[i]);
		}
		printf("\n");
	}*/
