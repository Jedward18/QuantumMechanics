/**
 * Swaps the values of two characters.
 *
 * param a Pointer to the first character.
 * param b Pointer to the second character.
 *
 * Swaps the values pointed to by a and b.
 */
void swap(char *a, char *b){
    char temp = *a; // Store the value of *a in temp
    *a = *b;        // Assign the value of *b to *a
    *b = temp;      // Assign the value of temp (original *a) to *b
}