#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int value;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    for(int i=0;i<candidate_count;i++)
    {
        for(int j=0;j<candidate_count;j++)
        {
            printf("%d ",preferences[i][j]);
        }
        printf("\n");
    }

    add_pairs();
    for (int i = 0; i < pair_count; i++)
    {
        printf("%d  %d",pairs[i].winner, pairs[i].loser);
        printf("\n");
        
    }
    sort_pairs();
    for (int i = 0; i < pair_count; i++)
    {
        printf("%d  %d",pairs[i].winner, pairs[i].loser);
        printf("\n");
        
    }
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int x = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[x].winner = i;
                pairs[x].loser = j;
                pairs[x].value = preferences[i][j] - preferences[j][i];
                x++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[x].winner = j;
                pairs[x].loser = i;
                pairs[x].value = preferences[j][i] - preferences[i][j];
                x++;
            }
        }
        pair_count = x;
    }
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int temp1 = 0, temp2 = 0, temp3 = 0;
    
    
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (pairs[i].value > pairs[j].value)
            {
                temp1 = pairs[i].winner;
                temp2 = pairs[i].loser;
                temp3 = pairs[i].value;
                
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[i].value = pairs[j].value;
                
                pairs[j].winner = temp1;
                pairs[j].loser = temp2;
                pairs[j].value = temp3;
            }
        }
    }
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                locked[i][j] = true;
                locked[j][i] = false;
            }
            else
            {
                locked[i][j] = false;
                locked[j][i] = true;
            }
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int x = 0, y = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                x++;
            }
        }
        if (x == 2)
        {
            printf("%s",candidates[i]);
            y++;
        }
        x = 0;
    }

    if(y == 0)
    {
        for(int i = 0; i < candidate_count; i++)
        {
            for(int j = i + 1; j < candidate_count; j++)
            {
                if (x != (pair_count - 1))
                {
                    locked[pairs[x].winner][pairs[x].loser] = true;
                    locked[pairs[x].loser][pairs[x].winner] = false;
                    x++;
                }
                else
                {
                    locked[pairs[x].winner][pairs[x].loser] = true;
                    locked[pairs[x].loser][pairs[x].winner] = true;
                }
            }
        }

        print_winner();
    }
    // TODO
    return;
}

