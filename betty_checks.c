/**
 * _strlen - returns the length of a string
 * @s: string to get the length of
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
        int len = 0;

        while (*s != '\0')
        {
                len++;
                s++;
        }

        return (len);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
        int dest_len = _strlen(dest);
        int i;

        for (i = 0; src[i] != '\0'; i++)
        {
                dest[dest_len + i] = src[i];
        }

        dest[dest_len + i] = '\0';

        return (dest);
}
