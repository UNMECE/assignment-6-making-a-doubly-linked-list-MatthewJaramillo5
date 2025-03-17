#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct _coordinate {
    float x;
    float y;
    int coord_id;
    struct _coordinate *next;
    struct _coordinate *previous;
};

typedef struct _coordinate Coordinate;
void add_coordinate(Coordinate *list_end, float x, float y);
void forward_display(Coordinate *list_beginning);
void backward_display(Coordinate *list_end);
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete);
int list_length(Coordinate *list_beginning);
void closest_to(Coordinate *list_beginning, float x, float y);

void add_coordinate(Coordinate *list_end, float x, float y){
	Coordinate *new_coord = (Coordinate *)malloc(sizeof(Coordinate));
	new_coord->x = x;
	new_coord->y = y;
	new_coord->coord_id = list_end->coord_id + 1;
   	new_coord->next = NULL;
   	new_coord->previous = list_end;
   	list_end->next = new_coord;
  	list_end = new_coord;
	}

void forward_display(Coordinate *list_begenning){
	Coordinate *current = list_begenning->next;
	while(current != NULL){
		printf("ID: %d (x: %.2f, y: %.2f)\n", current->coord_id, current->x, current->y);
		current = current->previous;
	}
}

void backward_display(Coordinate *list_end) {
    Coordinate *current = list_end;
	    while (current != NULL) {
        	printf("ID: %d (x: %.2f, y: %.2f)\n", current->coord_id, current->x, current->y);
        	current = current->previous;
    	}
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete){
	Coordinate *current = list_beginning->next;
	while(current != NULL){
		if(current->coord_id == coord_id_to_delete){
			if(current->previous != NULL){
				current->previous->next = current->next;
			}
			if(current->next != NULL){
				current->next->previous = current->previous;
			}
			free(current);
			printf("Coordinate ID %d deleted \n", coord_id_to_delete);
			return;
		}
		current = current->next;
	}
	printf("Coordinate ID %d not found \n", coord_id_to_delete);
}

int list_length(Coordinate *list_beginning){
	int length = 0;
	Coordinate *current = list_beginning->next;
  	 while (current != NULL) {
		length ++;
		current = current->next;
	}
return length;
}

void closest_to(Coordinate *list_beginning, float x, float y){
	Coordinate *current = list_beginning->next;  // skip the dummy head node
	if (current == NULL) {
		printf("The list is empty\n");
		return;
	}

	Coordinate *closest = current;
	float min_distance = sqrtf(powf(current->x - x, 2) + powf(current->y - y, 2));
	current = current->next;
	
	while(current != NULL){
		float distance = sqrtf(powf(current->x - x, 2) + powf(current->y - y, 2));
       		if (distance < min_distance) {
			min_distance = distance;
			closest = current;
		}
	current = current->next;
	}
printf("Closest coordinate: ID %d (x: %.2f, y: %.2f) with distance %.2f\n", closest->coord_id, closest->x, closest->y, min_distance);
}


int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s <number_of_coordinates\n", argv[0]);
		return 1;
	}
	int num_coordinates = atoi(argv[1]);

	srand(time(NULL));
	
	Coordinate *list_beginning = (Coordinate *)malloc(sizeof(Coordinate));
   	list_beginning->next = NULL;
   	list_beginning->previous = NULL;
   	list_beginning->coord_id = 0;

	Coordinate *list_end = list_beginning;

	int i;
	for(i = 0; i < num_coordinates; i++){
		float x = (float)(rand() % 100);  
       		float y = (float)(rand() % 100); 
        	add_coordinate(list_end, x, y);
        	list_end = list_end->next; 
	}

	printf("Coordinates (forward):\n");
  	forward_display(list_beginning);

	// Display all coordinates from end to beginning
	printf("Coordinates (backward):\n");
	backward_display(list_end);

	// Getting the length of the list
	printf("List length: %d\n", list_length(list_beginning));

	// Delete a coordinate with a specific coord_id (example: 3)
	 delete_coordinate(list_beginning, 3);

	//Display after deletion 
	printf("Coordinates after deletion:\n");
   	forward_display(list_beginning);

	closest_to(list_beginning, 50.0f, 50.0f);

	Coordinate *current = list_beginning;
   	while (current != NULL) {
		 Coordinate *temp = current;
         	 current = current->next;
        	 free(temp);
		}
	return 0;
}
