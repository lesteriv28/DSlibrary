 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdint.h>
 #include <stdbool.h>

 #define MAX_NAME 256
 #define TABLE_SIZE 10

 typedef struct {
    char name[MAX_NAME];
    int age;
    //... add other stuff later
 } person;

 person * hash_table[TABLE_SIZE]; //Array of ptrs to person struct & NULL tells you if theres a space or not

 //You use ptrs because we dont need space for the whole table

//Initialize hash_table with NULL values
    void init_hash_table() {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            hash_table[i] = NULL;
        }
        
    }

//Prints the value at each index
    void print_table() {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hash_table[i] == NULL)
            {
                printf("\t%i\t---\n", i); 
            } else {
                printf("\t%i\t%s\n",i, hash_table[i]->name); 
            }
            
            
        }
        
    }

 //A hash function is a randomizer
 unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int h_value = 0;
    for (int i = 0; i < length; i++)
    {
        //h_value += i; Will make the hv be the amount of characters in the string
       //h_value += name[i]; // Will make the hv the sum of the ASCII value of all the characters in the string
       // h_value += (name[i] * h_value + 1); //Will make the hv the sum of ascii character times the previous val of the hv in the iteration

        h_value = (name[i] * h_value + 1) % TABLE_SIZE; //Makes sure the hv lands between 0 and TS-1

    }

    
    return h_value;
 }


//function that inserts person into ht, ret t if succesful f ifnot
    bool hash_table_insert(person *p) {
        if (p == NULL) return false;
        unsigned int index = hash(p->name); //index of the table where we are going to try to put the person
        if (hash_table[index] != NULL) {
           // printf("Collision happened here... \n At index%u\n", index); // tells us where the collision happened.
            printf("Collision happened here... \n At index: %u\n Name of the Person: %s\n", index, p->name); // tells us where the collision happened and which name triggered it.
            return false; //if someone is already here, we cant fill it out
            
        }
        hash_table[index] = p; //set the table to point to the new person
        return true; //person inserted successfully
    }
 

 int main(){
    person jacob = {.name="Jacob", .age=256};
    person tom = {.name="Tom", .age=56};
    person alissa = {.name="Alissa", .age=25};
    
    hash_table_insert(&jacob);
    hash_table_insert(&tom);
    hash_table_insert(&alissa);
    print_table();
   /*printf("Jacob ===> %u\n", hash("Jacob"));
    printf("Tom ===> %u\n", hash("Tom"));
    printf("Sally ===> %d\n", hash("Sally"));
    printf("Perona ===> %d\n", hash("Perona"));*/ 

    return 0;
 }
 