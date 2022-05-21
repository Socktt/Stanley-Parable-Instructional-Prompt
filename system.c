void * memset(void *dest, int c, int n) // Set part of memory at pointer dest with data c, n times incrementing dest every write
{
    unsigned char *ptr = dest;
    while (n-- > 0)
        *ptr++ = c;
    return dest;
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void strcpy(char start[], char dest[], int n) // Copy str array of length n
{
    while (n-- >= 0)
    {
        dest[n] = start[n];
    }
    return;
}

/*
compare 2 strings, returns 1 if not equal, 0 if equal
*/
int strcmp(char a[], char b[])
{
    for (int i = 0; a[i] != 0 && b[i] != 0; i++)
        if (a[i] != b[i])
            return 1;
    if (a[0] != b[0])
        return 1;
    return 0;
}