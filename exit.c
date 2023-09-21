/**
 * custom_strncpy - Copies a string with a specified limit
 * @destination: The destination string to copy to
 * @source: The source string to copy from
 * @limit: The maximum number of characters to copy
 * Return: A pointer to the concatenated string
 */
char *custom_strncpy(char *destination, char *source, int limit)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < limit - 1)
    {
        destination[i] = source[i];
        i++;
    }
    if (i < limit)
    {
        j = i;
        while (j < limit)
        {
            destination[j] = '\0';
            j++;
        }
    }
    return (result);
}

/**
 * custom_strncat - Concatenates two strings with a specified limit
 * @destination: The first string
 * @source: The second string to append
 * @limit: The maximum number of characters to append
 * Return: A pointer to the concatenated string
 */
char *custom_strncat(char *destination, char *source, int limit)
{
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;
    while (destination[i] != '\0')
        i++;
    while (source[j] != '\0' && j < limit)
    {
        destination[i] = source[j];
        i++;
        j++;
    }
    if (j < limit)
        destination[i] = '\0';
    return (result);
}

/**
 * custom_strchr - Locates a character in a string
 * @str: The string to search within
 * @character: The character to locate
 * Return: A pointer to the memory area in str where the character is found
 */
char *custom_strchr(char *str, char character)
{
    do
    {
        if (*str == character)
            return (str);
    } while (*str++ != '\0');

    return (NULL);
}

