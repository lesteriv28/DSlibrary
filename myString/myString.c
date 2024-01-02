#include"myString.h"

// MyString functions
int mystrlen(const char *s)
{

	int count = 0;
	for (; *s != '\0'; s++)
	{
		count++;
	}
	return count;
}

char *mystrcpy(char *dst, const char *src)
{
	if (src == NULL)
	{
		perror("String to be copied from is empty");
	}
	char *t = dst;
	while (*src != '\0')
	{
		*t = *src;
		t++;
		src++;
	}
	*t = '\0';
	return dst;
}

int mystrcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		perror("One or both string empty");
	}
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 < *s2)
		{
			return -1;
		}
		else if (*s1 > *s2)
		{
			return 1;
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return 0;
	}
	if (*s1 == '\0')
	{
		return -1;
	}
	if (*s2 == '\0')
	{
		return 1;
	}
	return 0;
}

char *mystrdup(const char *src)
{
	if (src == NULL)
	{
		perror("Empty string input");
		return NULL; // Return early if src is NULL
	}

	char *rv = malloc(sizeof(char) * (mystrlen(src) + 1));
	if (rv == NULL)
	{
		perror("Memory allocation error");
		return NULL; // Return NULL on memory allocation failure
	}

	rv = mystrcpy(rv, src);
	return rv;
}

