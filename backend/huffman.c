#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char ch;
    int freq;
    struct node* left;
    struct node* right;
} node;

typedef struct char_freq_map {
    char ch;
    int freq;
    struct char_freq_map* next;
} char_freq_map;

typedef struct priority_queue {
    node* data;
    struct priority_queue* next;
} priority_queue;

typedef struct huff_map {
    char ch;
    char* code;
    struct huff_map* next;
} huff_map;

node* create_node(char ch, int freq, node* left, node* right) {
    node* new_node = (node*)malloc(sizeof(node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->ch = ch;
    new_node->freq = freq;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

char_freq_map* increment_char_freq(char_freq_map** map, char ch) {
    char_freq_map* current = *map;
    while (current != NULL) {
        if (current->ch == ch) {
            current->freq++;
            return current;
        }
        current = current->next;
    }
    char_freq_map* new_node = (char_freq_map*)malloc(sizeof(char_freq_map));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->ch = ch;
    new_node->freq = 1;
    new_node->next = *map;
    *map = new_node;
    return new_node;
}

void push_priority_queue(priority_queue** pq, node* data) {
    priority_queue* new_pq_node = (priority_queue*)malloc(sizeof(priority_queue));
    if (!new_pq_node) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_pq_node->data = data;
    new_pq_node->next = NULL;

    if (*pq == NULL || (*pq)->data->freq > data->freq) {
        new_pq_node->next = *pq;
        *pq = new_pq_node;
    } else {
        priority_queue* current = *pq;
        while (current->next != NULL && current->next->data->freq <= data->freq) {
            current = current->next;
        }
        new_pq_node->next = current->next;
        current->next = new_pq_node;
    }
}

node* pop_priority_queue(priority_queue** pq) {
    if (*pq == NULL) {
        return NULL;
    }
    node* data = (*pq)->data;
    priority_queue* temp = *pq;
    *pq = (*pq)->next;
    free(temp);
    return data;
}

void build_huffman_tree(priority_queue** pq, char_freq_map* map) {
    while (map != NULL) {
        node* new_node = create_node(map->ch, map->freq, NULL, NULL);
        push_priority_queue(pq, new_node);
        map = map->next;
    }

    while ((*pq)->next != NULL) {
        node* left = pop_priority_queue(pq);
        node* right = pop_priority_queue(pq);
        node* parent = create_node('\0', left->freq + right->freq, left, right);
        push_priority_queue(pq, parent);
    }
}

void build_huffman_map(node* root, huff_map** map, char* code, int depth) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        huff_map* new_map_node = (huff_map*)malloc(sizeof(huff_map));
        if (!new_map_node) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        new_map_node->ch = root->ch;
        new_map_node->code = (char*)malloc((depth + 1) * sizeof(char));
        if (!new_map_node->code) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        strncpy(new_map_node->code, code, depth);
        new_map_node->code[depth] = '\0';
        new_map_node->next = *map;
        *map = new_map_node;
    }

    code[depth] = '0';
    build_huffman_map(root->left, map, code, depth + 1);
    code[depth] = '1';
    build_huffman_map(root->right, map, code, depth + 1);
}

void free_huff_map(huff_map* map) {
    while (map != NULL) {
        huff_map* next = map->next;
        free(map->code);
        free(map);
        map = next;
    }
}

void free_priority_queue(priority_queue* pq) {
    while (pq != NULL) {
        priority_queue* temp = pq;
        pq = pq->next;
        free(temp);
    }
}

void free_node(node* root) {
    if (root == NULL) {
        return;
    }

    // Free the left and right children recursively
    free_node(root->left);
    free_node(root->right);

    // Finally, free the current node
    free(root);
}


char* encode_string(char* str, huff_map* map) {
    size_t length = strlen(str);
    size_t encoded_length = 0;
    huff_map* current_map = map;

    // Calculate the total length of the encoded string
    size_t i;
    for (i = 0; i < length; i++) {
        current_map = map;
        while (current_map != NULL && current_map->ch != str[i]) {
            current_map = current_map->next;
        }
        if (current_map != NULL) {
            encoded_length += strlen(current_map->code);
        }
    }

    char* encoded_str = (char*)malloc((encoded_length + 1) * sizeof(char));
    if (!encoded_str) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    encoded_str[0] = '\0';

    // Encode the string
    for (i = 0; i < length; i++) {
        current_map = map;
        while (current_map != NULL && current_map->ch != str[i]) {
            current_map = current_map->next;
        }
        if (current_map != NULL) {
            strcat(encoded_str, current_map->code);
        }
    }

    return encoded_str;
}

char* decode_string(char* encoded_str, node* root) {
    node* current_node = root;
    size_t length = strlen(encoded_str);
    size_t decoded_length = 0;

    // Calculate the length of the decoded string
    size_t i;
    for (i = 0; i < length; i++) {
        if (encoded_str[i] == '0') {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
        if (current_node->left == NULL && current_node->right == NULL) {
            decoded_length++;
            current_node = root;
        }
    }

    char* decoded_str = (char*)malloc((decoded_length + 1) * sizeof(char));
    if (!decoded_str) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Decode the string
    current_node = root;
    size_t index = 0;
    //size_t i;
    for ( i = 0; i < length; i++) {
        if (encoded_str[i] == '0') {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
        if (current_node->left == NULL && current_node->right == NULL) {
            decoded_str[index++] = current_node->ch;
            current_node = root;
        }
    }
    decoded_str[index] = '\0';

    return decoded_str;
}

void print_summary(size_t initial_length, size_t encoded_length, size_t map_size) {
    printf("\nCompression Performance\n");
    printf("Initial length: %zu bits\n", initial_length);
    printf("Encoded length: %zu bits\n", encoded_length);
    printf("Map size: %zu bits\n", map_size);
    float ratio = (float)(encoded_length + map_size) / (float)initial_length;
    printf("Size reduced to: %.2f%% of initial size\n", ratio * 100);
    printf("Bits saved: %zu\n", initial_length - (encoded_length + map_size));
}
// take file name from command line argument
int main(int argc, char *argv[]) {
    char file_name[256];
    // printf("Enter the name of the file to compress: ");
    // scanf("%s", file_name);
    // assign first argument to file name
    strcpy(file_name, argv[1]); 


    // Open the input file
    FILE *text = fopen(file_name, "r");
    if (!text) {
        printf("File not found: %s\n", file_name);
        return 1;
    }

    // Read the input file and calculate character frequencies
    char_freq_map *freq_map = NULL;
    char ch;
    size_t initial_length = 0;
    while (fread(&ch, sizeof(char), 1, text) == 1) {
        increment_char_freq(&freq_map, ch);
        initial_length += 8;
    }
    fclose(text);

    // Create the priority queue and Huffman tree
    priority_queue *pq = NULL;
    build_huffman_tree(&pq, freq_map);
    node *huff_root = pop_priority_queue(&pq);
    free_priority_queue(pq);

    // Create the Huffman map
    huff_map *map = NULL;
    char code[256] = {0};
    build_huffman_map(huff_root, &map, code, 0);

    // Encode the input file using the Huffman map
    text = fopen(file_name, "r");
    if (!text) {
        printf("File not found: %s\n", file_name);
        free_huff_map(map);
        free_node(huff_root);
        return 1;
    }

    // Read the file contents and encode the string
    fseek(text, 0, SEEK_END);
    size_t file_size = ftell(text);
    fseek(text, 0, SEEK_SET);
    char *file_contents = (char*)malloc(file_size + 1);
    if (!file_contents) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(text);
        free_huff_map(map);
        free_node(huff_root);
        return 1;
    }
    fread(file_contents, 1, file_size, text);
    fclose(text);
    file_contents[file_size] = '\0';

    char *encoded = encode_string(file_contents, map);
    free(file_contents);
    printf("Encoded string:\n%s\n", encoded);

    // store the encoded string in a file
    FILE *encoded_file = fopen("encoded.txt", "w");
    if (!encoded_file) {
        printf("Failed to create encoded file.\n");
        free(encoded);
        free_huff_map(map);
        free_node(huff_root);
        return 1;
    }
    fprintf(encoded_file, "%s", encoded);
    fclose(encoded_file);


    // Decode the encoded string
    char *decoded = decode_string(encoded, huff_root);
    printf("\nDecoded string:\n%s\n", decoded);

    // store the decoded string in a file
    FILE *decoded_file = fopen("decoded.txt", "w");
    if (!decoded_file) {
        printf("Failed to create decoded file.\n");
        free(encoded);
        free(decoded);
        free_huff_map(map);
        free_node(huff_root);
        return 1;
    }
    fprintf(decoded_file, "%s", decoded);
    fclose(decoded_file);
    free(decoded);
    free(encoded);

    // Calculate the size of the Huffman map
    size_t map_size = 0;
    huff_map *current_map = map;
    while (current_map != NULL) {
        map_size += (8 + strlen(current_map->code));
        current_map = current_map->next;
    }

    print_summary(initial_length, strlen(encoded), map_size);

    


    // Free memory
    free_huff_map(map);
    free_node(huff_root);

    return 0;
}


