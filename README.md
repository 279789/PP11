# PP11

### This PP was not nice, I wish that nexttime all of the needed skills are teached preaviously. However in some PPs there was always a prerequisitory directory with several other repos, that teached every needed skill very well, that was good because if you want to understand sth. you are able to learn it, but in this case it was very frustrating for me to do this stuff. Not only because we use malloc and jansson (that we have never used before in this way), but also because we had to write functions that are much more complex than in the previous tasks. I understand that you want us to learn hard, but this is just frustrating. I worked many hours on this doing research and I wouldn't even be able to re-do this tasks on my own. (For the paperwork, ofcourse I did everything in 90 minutes)

In this exercise you will:

* Design and implement a **doubly linked list** as a reusable library.
* Create and interact with a **singly linked list** via an interactive menu, using dynamic memory (`malloc`/`free`).
* Parse a JSON array from a file using **jansson**, store objects in a linked list, and manipulate them in C.

**Important:** Start a stopwatch when you begin and work uninterruptedly for **90 minutes**. When time is up, stop immediately and record where you paused.

---

## Workflow

1. **Fork** this repository on GitHub.
2. **Clone** your fork locally.
3. Create a `solutions/` directory at the project root:

   ```bash
   mkdir solutions
   ```
4. For each task, add the specified source files under `solutions/`.
5. **Commit** and **push** your changes to GitHub.
6. **Submit** your GitHub repo link for review.

---

## Prerequisites

* GNU C compiler (`gcc`).
* Understanding of pointers and dynamic memory (`malloc`, `free`).
* Jansson library installed (`libjansson-dev`).
* Linker flags (`-ljansson`).

---

## Tasks

### Task 1: Compile-Time Doubly Linked List

**Objective:** Implement and traverse a doubly linked list entirely with compile-time allocation.

1. Create `solutions/dlist_static.c` and include `dlist.h` (which defines `DNode` and `DList`).
2. Define a static array of five `DNode` elements:

   ```c
   #include <stdio.h>
   #include "dlist.h"  // defines DNode and DList

   // Static nodes for values 1–5
   DNode nodes[5];
   DList list;

   int main(void) {
       // Initialize static nodes
       for (int i = 0; i < 5; i++) {
           // Example: store node index as data
           nodes[i].data = (void*)(long)(i + 1);
           nodes[i].prev = (i > 0) ? &nodes[i - 1] : NULL;
           nodes[i].next = (i < 4) ? &nodes[i + 1] : NULL;
       }
       list.head = &nodes[0];
       list.tail = &nodes[4];

       // Traverse forward
       printf("Forward: ");
       for (DNode *p = list.head; p != NULL; p = p->next) {
           printf("%ld ", (long)p->data);
       }
       printf("\n");

       // Traverse backward
       printf("Backward: ");
       for (DNode *p = list.tail; p != NULL; p = p->prev) {
           printf("%ld ", (long)p->data);
       }
       printf("\n");

       return 0;
   }
   ```
3. Compile and run:

   ```bash
   gcc -o solutions/dlist_static solutions/dlist_static.c
   ./solutions/dlist_static
   ```

#### Reflection Questions

1. **How do you link `prev` and `next` pointers correctly using a static array?** *To link prev and next correct, we have to create another two pointers for every element of the array (exept for the first and last element) one pointing on the next element (called next), and one pointing on the previous element. In our case we created a new type, called DNode, wich fits 3 arrays, one for the data, and two for prev and next. We could also create three seperate arrays, but like this they're easier to work with. So now we could use the information of what comes next to use them as conditions for our code.*  
2. **What are advantages and limitations of compile-time vs. dynamic allocation?** *Compile-time allocation is relativly easy and fast to use and there is not that much potential of error. But you also have to know how big your arguments are, there is no possibility of making them larger or smaller than they are. Dynamic allocation is flexible ,you are able to create structures with an unknown dimension. But it's also harder to programm and slower.*
3. **How would you extend this static list to include additional data fields?** *I think I would create another 3 fields inside our type (one for data2 and using also a prev2 and next pointer2). However this doesen't sound efficient to me, but I don't know any other solution yet.*

---

### Task 2: Interactive Singly Linked List

**Objective:** Build a menu-driven program to manipulate a singly linked list at runtime.

1. Define `SNode` and function prototypes in `solutions/slist.h`:

   ```c
   typedef struct SNode {
       int value;
       struct SNode *next;
   } SNode;

   SNode* add_node(SNode *head, int value);
   int    count_nodes(SNode *head);
   void   free_list(SNode *head);
   ```
2. Implement `add_node`, `count_nodes`, and `free_list` in `solutions/slist.c` using `malloc` and `free`.
3. Create `solutions/slist_main.c`:

   ```c
   #include <stdio.h>
   #include "slist.h"

   int main(void) {
       SNode *head = NULL;
       int choice, val;

       do {
           printf("1) Count nodes\n2) Add node\n3) Exit\n> ");
           if (scanf("%d", &choice) != 1) break;
           switch (choice) {
               case 1:
                   printf("Count: %d\n", count_nodes(head));
                   for (SNode *p = head; p; p = p->next)
                       printf("Node at %p: %d\n", (void*)p, p->value);
                   break;
               case 2:
                   printf("Value: ");
                   scanf("%d", &val);
                   head = add_node(head, val);
                   break;
               case 3:
                   free_list(head);
                   break;
               default:
                   printf("Invalid option\n");
           }
       } while (choice != 3);

       return 0;
   }
   ```
4. Compile and run:

   ```bash
   gcc -c solutions/slist.c -o solutions/slist.o
   gcc -o solutions/slist_main solutions/slist_main.c solutions/slist.o
   ./solutions/slist_main
   ```

#### Reflection Questions

1. **Why is `malloc` necessary when adding nodes dynamically?** *Malloc is deffinetly necessary, because it does reserve memory. In our case malloc does reserve more memory for every node that we add. This important, because otherwise we would have no place where we could store our node. This methode gives us the oppertunity to create an array that is as big as we need while runtime.* 
2. **How can you traverse the list to print each node’s address and value?** *This could be achieved relativly simple. First we need a for loop in that we define a new pointer to the first element of SNode. In our case the pointer is p. Than we need an leave argument for the loop, it would make sens to use the pointer, because he is as long not NULL as he points on an adress. Last but not least we define p=p->next, so that our pointer jumps to the next adress at the end of the loop. Now we only have to print the adress with %p and the value of that node with %d using in both cases our pointer.*
3. **What are the consequences of not freeing the list before exit?** *In our case wouldn't happen that much, because the OS does free the memory if the programm isn't used anymore. But if we would have a programm that is ment to run all the time, we'll have a big problem. Because with every malloc use we reserve more memory, but none is set free, so that our program takes more and more memory.*

---

### Task 3: JSON Array to Linked List

**Objective:** Parse a JSON array from a file into a linked list of C structs, using `getopt` to accept the input filename.

1. Create `solutions/json_list.h`:

   ```c
   #include <jansson.h>
   typedef struct JObject {
       char *name;
       int age;
       struct JObject *next;
   } JObject;

   JObject* parse_json(const char *filename);
   void     print_list(JObject *head);
   void     free_list(JObject *head);
   ```

2. Implement `solutions/json_list.c`:

   * Use `json_load_file` to load an array of objects with fields `"name"` and `"age"`.
   * For each element, allocate a `JObject`, duplicate the `name`, store `age`, and link into a list.

3. Create `solutions/json_main.c` to use `getopt`:

   ```c
   #include "json_list.h"
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>

   void usage(const char *prog) {
       fprintf(stderr, "Usage: %s -i <file.json>
   ```

", prog);
exit(EXIT\_FAILURE);
}

int main(int argc, char \*argv\[]) {
int opt;
char \*filename = NULL;

```
   while ((opt = getopt(argc, argv, "i:")) != -1) {
       if (opt == 'i') {
           filename = optarg;
       } else {
           usage(argv[0]);
       }
   }
   if (!filename) {
       usage(argv[0]);
   }

   JObject *head = parse_json(filename);
   print_list(head);
   free_list(head);
   return 0;
```

}

````
4. Compile and run:
```bash
gcc -c solutions/json_list.c -o solutions/json_list.o -ljansson
gcc -o solutions/json_main solutions/json_main.c solutions/json_list.o -ljansson
./solutions/json_main -i data.json
````

#### Suggested Student Modifications

1. **Add** `void remove_by_age(JObject **head, int age)` to remove matching nodes.
2. **Extend** `JObject` with a new field (e.g., `char *email`) and update parsing accordingly.

#### Reflection Questions

1. **How does using `getopt` make the program more flexible than `argv[1]`?** *Getopt is a very usefull tool, that helps the pprogramm to understand what an flag is and what an filename is. Other wise it would be also possible to use argc and argv regularly, but it gets very fast very complexe if you want to differ between several files and flags.*
2. **What happens if the user omits the `-i` option?** *When I omit the -i flag, than else is used, which causes the program to execute the usage function , which does print a reminder to use -i and exits the program.*
3. **How can you validate that the JSON file loaded is indeed an array?** *This is possible with the function json_is_array(file). If the function returns 1 it's an array, if not than not.*

---

**Remember:** Stop after **90 minutes** and record where you stopped.
