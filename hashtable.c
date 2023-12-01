#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct
{
    char name[MAX_NAME];
    struct Date
    {
        int day;
        int month;
        int year;
    } dob;
    struct person *next;
} person;

person *hash_table[TABLE_SIZE]; // Array of ptrs to person struct & NULL tells you if theres a space or not

// Function prototypes
person *new_person(const char *name, int day, int month, int year);
void init_hash_table();
void print_table();
unsigned int hash(char *name);
bool hash_table_insert(person *p);
bool check_person(person *p1, person *p2);
person *hash_table_lookup(person *p);
person *hash_table_delete(person *p);
int calculate_age(int birth_year);
void print_person(person *p);

// function to create a new person
person *new_person(const char *name, int day, int month, int year)
{
    person *new_node = malloc(sizeof(person));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n"); // checking for space
        return NULL;
    }
    else
    {
        strncpy(new_node->name, name, MAX_NAME);
        new_node->dob.day = day;
        new_node->dob.month = month;
        new_node->dob.year = year;
        new_node->next = NULL;
        return new_node;
    }
}

// Initialize hash_table with NULL values
void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

// Prints the value at each index **NEEDS WORK
void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            person *current = hash_table[i];
            printf("\t%i\t%s", i, current->name);
            while (current->next != NULL)
            {
                current = current->next;
                printf("\t|\t%s", current->name);
            }
            printf("\n");
        }
    }
}

// Hash function does a arithmetical operation to determine a Hash integer (index) of the Hash Table
unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int h_value = 0;
    for (int i = 0; i < length; i++)
    {
        h_value = (name[i] * h_value + 1) % TABLE_SIZE; // Makes sure the hv lands between 0 and TS-1
    }

    return h_value;
}

// function that inserts person into ht, ret t if succesful f ifnot
bool hash_table_insert(person *p)
{
    if (p == NULL)
        return false;
    unsigned int index = hash(p->name); // index of the table where we are going to try to put the person
    if (hash_table[index] == NULL)
    {
        hash_table[index] = p; // set the table to point to the new person
    }
    else
    {
        person *current = hash_table[index];
        // check for duplicates
        while (current != NULL)
        {
            if (check_person(current, p))
            {
                printf("Duplicate person:");
                print_person(current);
                return false;
            }
            current = current->next;
        }

        // No duplicates found insert person to the chain
        current = hash_table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = p;
    }

    return true; // person inserted successfully
}

bool check_person(person *p1, person *p2)
{
    if (strcmp(p1->name, p2->name) == 0 &&
        p1->dob.year == p2->dob.year &&
        p1->dob.day == p2->dob.day &&
        p1->dob.month == p2->dob.month)
    {
        return true; // person match
    }
    return false; // person mismatch
}

// find a person by their key **NEEDS WORK
person *hash_table_lookup(person *p)
{
    int index = hash(p->name);
    if (hash_table[index] == NULL)
    {
        return NULL; // Person was not found return NULL
    }
    else
    {
        person *current = hash_table[index];
        while (current != NULL)
        {
            if (check_person(current, p))
            {
                return current; // found person
            }
            current = current->next;
        }
        return NULL; // person not found in the chain
    }
}

// Delete
person *hash_table_delete(person *p)
{
    int index = hash(p->name);
    if (hash_table[index] == NULL)
    {
        return NULL; // Space in the table is already empty
    }
    else
    {
        person *current = hash_table[index];
        person *prev = NULL; // For List tracking
        while (current != NULL)
        {
            if (check_person(current, p))
            {
                // Person is the first item on the list
                if (prev == NULL)
                {
                    hash_table[index] = current->next; // keep the chain or point to NULL if list is one item
                    return current; // return deleted person
                }
                else
                {
                    prev->next = current->next; // if person is at middle or end
                    return current;
                }
            }
            prev = current;
            current = current->next;
        }
        return NULL; // Person not found
    }
}

// Calculate a Person's age
int calculate_age(int birth_year)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900; // standard time calculation
    return current_year - birth_year;
}

// Print individual Person
void print_person(person *p)
{
    printf("Person: %s, Age: %d, Hash: %d\n", p->name, calculate_age(p->dob.year), hash(p->name));
}
int main()
{

    // Creating people
    person *P1 = new_person("Jacob", 15, 5, 1990);
    person *P2 = new_person("Flor", 17, 2, 1996);
    person *P3 = new_person("Lorenzo", 5, 12, 1998);
    person *P4 = new_person("Dominick", 9, 3, 2000);
    person *P5 = new_person("Omar", 31, 8, 1987);
    person *P6 = new_person("Omar", 25, 3, 2004);
    person *P7 = new_person("Omar", 13, 7, 1971);

    // Calculate and print ages
    // printf("Person: %s, Age: %d, Hash: %d\n", P1->name, calculate_age(P1->dob.year), hash(P1->name));
    // printf("Person: %s, Age: %d, Hash: %d\n", P2->name, calculate_age(P2->dob.year), hash(P2->name));
    // printf("Person: %s, Age: %d, Hash: %d\n", P3->name, calculate_age(P3->dob.year), hash(P3->name));
    // printf("Person: %s, Age: %d, Hash: %d\n", P4->name, calculate_age(P4->dob.year), hash(P4->name));
    // printf("Person: %s, Age: %d, Hash: %d\n", P5->name, calculate_age(P5->dob.year), hash(P5->name));
    // printf("Person: %s, Age: %d, Hash: %d\n", P6->name, calculate_age(P6->dob.year), hash(P6->name));
    // printf("Person: %s, Age: %d, Hash: %d\n", P7->name, calculate_age(P7->dob.year), hash(P7->name));
    print_person(P1);
    print_person(P2);
    print_person(P3);
    print_person(P4);
    print_person(P5);
    print_person(P6);
    print_person(P7);

    // Inserting into Table
    hash_table_insert(P1);
    hash_table_insert(P2);
    hash_table_insert(P3);
    hash_table_insert(P4);
    hash_table_insert(P5);
    hash_table_insert(P6);
    hash_table_insert(P7);

    // Printing Table
    printf("Printing Table...\n");
    print_table();

    // Look up a person;
    printf("Looking up a Person in Table...\n");
    person *result = hash_table_lookup(P6);
    print_person(result);

    // Deleting a person
    // person *deleted = hash_table_delete(P7);
    person *deleted = hash_table_delete(P6);
    // person *deleted = hash_table_delete(P5);
    // person *deleted = hash_table_delete(P4);
    // person *deleted = hash_table_delete(P3);
    //person *deleted = hash_table_delete(P2);
    //person *deleted = hash_table_delete(P1);
    printf("Printing Table after Deleting Person...\n");
    print_table();
    if (deleted != NULL)
    {
        printf("Person Deleted: ");
        print_person(deleted);
        free(deleted);
    }
    else
    {
        printf("Person not found for deletion or deletion unsuccessful.\n");
    }
    // Free allocated memory
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    free(P7);

    return 0;
}
