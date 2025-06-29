#include <jansson.h>
#include <stdio.h>
#include "json_list.h"

JObject* parse_json(const char *filename) {

	json_error_t error; // Notwendig für die Load funktion
	json_t *file = json_load_file(filename, 0, &error); //File Einlesen
	
	size_t len = json_array_size(file); //Anzahl Objekte in der json datei#
	
	JObject *head = NULL;
        JObject *tail = NULL;

	for (size_t i = 0; i < len; i++) { //So lange i kleiner len (noch nicht alle objekte durchlaufen) läuft die Schleife.
	
		json_t *obj = json_array_get(file, i); //Nimm das Objekt i aus dem File
		json_t *jname = json_object_get(obj, "name"); //Nimmt den Name aus dem Objekt
        	json_t *jage = json_object_get(obj, "age"); //Nimmt das Alter aus dem Objekt
		json_t *jemail = json_object_get(obj, "email"); // Nimmt die Email vom Objekt

		JObject *node = malloc(sizeof(JObject));
		node->name = json_string_value(jname);
		node->age = json_integer_value(jage);
		node->email = json_string_value(jemail);
		node->next = NULL;

		if (head == NULL) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}
	return head;
}

void print_list(JObject *head) {
	
	for(JObject *actual = head; actual!= NULL; actual = actual->next) {
		printf("Name:%s\nAge:%d\nEmail:%s\n\n",actual->name, actual->age, actual->email);
	}
}


void free_list(JObject *head) {
	JObject *mem;
	for( JObject *actual = head; actual!= NULL; actual = mem) {
	mem = actual->next;
	free(actual);
	}
}


void remove_by_age(JObject **head, int age ){

	JObject *mem;

	for( JObject *actual = *head, *old = NULL; actual != NULL; actual = mem) {
	mem = actual->next;
	if (actual->age == age) {
		if(old == NULL) {
			*head = actual->next;
		}
		else if(old != NULL) {
			old->next = actual->next;
		}
		free(actual);
	} 
	else {
		old = actual;
	}
	}
}
	
	
	
	
	
	
	
































