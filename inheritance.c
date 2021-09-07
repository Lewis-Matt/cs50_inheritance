// Simulate genetic inheritance of blood type
// Creates a family of a specified generation size and assigns blood type alleles to each family member.
// The oldest generation will have alleles assigned randomly to them.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    // Every person has an array of size two parents, and each of those parents is a pointer to another person
    // So "struct person" is the type
    struct person *parents[2];
    // Every person has 2 alleles
    char alleles[2];
}
person;

// Global constants
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// Prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed (provide initial input) random number generator (for generating random alleles)
    srand(time(0));

    // Create a new family with three generations, w/ a pointer to the most recent person
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person (p points to it)
    person *p = malloc(sizeof(person));
    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents (1 fewer gen than what we started with)
        // p->parents[0] gives us access to index 0 of the parents array, inside the 'person' struct
        // Each parent has their own parents, -1 from the generation until generations !> 1
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);
        // TODO: Randomly assign child alleles based on parents
        // Alleles is an array of two chars, and we want to randomly select one of them - %2 will either give
        // us a 0 or 1 (index position of parent allele)
        // that will be stored in the most recent person (pointed to by p on the left of =) allele spot
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }

    // Generation without parent data (or our Base case), once generations are <=1
    else
    {
        // TODO: Set parent pointers to NULL, as there are no parents
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        // TODO: Randomly assign alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }
    // TODO: Return newly created person to line 36
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case, there is nothing to free
    if (p == NULL)
    {
        return;
    }
    // TODO: Free parents, recursively call - keeps going until we hit base case (line 80)
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
// create_family - malloc for new person, if gen>1 recursively create previous gens. Using return value, update new
// person's family. inherit alleles from parents (randomly choosing 1 from each)
// gen == 1, no previous gens, set parents to NULL. random gen alleles for this person
// free - need a base case: handle an input of NULL. Then recursively free the parents & grandparents, then the child
// rand() returns int between 0 and RAND_MAX (32767). to gen a random num that is 0 or 1, use rand() % 2
// p->parents[0] accesses a persons first parent
