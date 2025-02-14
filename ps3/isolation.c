#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

// Fowler–Noll–Vo hash function 64-bit constants
#define FNV_OFFSET_BASIS 0xCBF29CE484222325
#define FNV_PRIME 0x00000100000001B3

#define HASH_LEFT 0b10101010
#define HASH_RIGHT 0b01010101

struct graph_point {
    int value;
    struct graph_point *point_left;
    struct graph_point *point_right;
};

void hash_apply_graph(uint64_t *hash, const struct graph_point *graph, int depth);
void hash_apply_value(uint64_t *hash, uint8_t value);

struct graph_point *graph_construct(int graph_values_count, const int graph_values[graph_values_count]);
void graph_insert_point(struct graph_point *parent_point, int child_point_value);
void graph_set_point(struct graph_point **point_ptr, int point_value);
void graph_free(struct graph_point *parent_point);

int main()
{
    int prototypes_count, points_count;
    scanf("%d %d", &prototypes_count, &points_count);

    uint64_t prototypes_hash_array[prototypes_count];

    int types = 0;

    for(int i = 0; i < prototypes_count; ++i)
    {
        prototypes_hash_array[types] = FNV_OFFSET_BASIS;

        int graph_values[points_count];

        for(int j = 0; j < points_count; ++j)
            scanf("%d", graph_values + j);

        struct graph_point *graph = graph_construct(points_count, graph_values);

        hash_apply_graph(prototypes_hash_array + types, graph, 0);

        graph_free(graph);

        bool new_type = true;
        for(int j = types - 1; j >= 0; --j)
            if(prototypes_hash_array[types] == prototypes_hash_array[j])
            {
                new_type = false;
                break;
            }
        if(new_type)
            types++;
    }

    printf("%d\n", types);
}

void hash_apply_graph(uint64_t *hash, const struct graph_point *graph, int depth)
{
    if(graph->point_left != NULL)
    {
        hash_apply_value(hash, depth);
        hash_apply_value(hash, HASH_LEFT);
        hash_apply_graph(hash, graph->point_left, depth + 1);
    }

    if(graph->point_right != NULL)
    {
        hash_apply_value(hash, depth);
        hash_apply_value(hash, HASH_RIGHT);
        hash_apply_graph(hash, graph->point_right, depth + 1);
    }
}

void hash_apply_value(uint64_t *hash, uint8_t value)
{
    *hash ^= value;
    *hash *= FNV_PRIME;
}

struct graph_point *graph_construct(int graph_values_count, const int graph_values[graph_values_count])
{
    struct graph_point *graph = calloc(1, sizeof(struct graph_point));

    if(graph_values_count <= 0)
        return graph;

    graph->value = graph_values[0];

    for(int i = 1; i < graph_values_count; ++i)
        graph_insert_point(graph, graph_values[i]);

    return graph;
}

void graph_insert_point(struct graph_point *parent_point, int child_point_value)
{
    if(child_point_value < parent_point->value)
        graph_set_point(&parent_point->point_left, child_point_value);
    else
        graph_set_point(&parent_point->point_right, child_point_value);
}

void graph_set_point(struct graph_point **point_ptr, int point_value)
{
    if(*point_ptr == NULL)
    {
        *point_ptr = calloc(1, sizeof(struct graph_point));
        (*point_ptr)->value = point_value;
    }
    else
        graph_insert_point(*point_ptr, point_value);
}

void graph_free(struct graph_point *parent_point)
{
    if(parent_point->point_left != NULL)
        graph_free(parent_point->point_left);
    
    if(parent_point->point_right != NULL)
        graph_free(parent_point->point_right);

    free(parent_point);
}
