#include "rt.h"
t_list *ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	if (lst == NULL || new == NULL)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	last = ft_lstlast(*lst);
	new->next = last->next;
	last->next = new;
}
t_list *ft_lstnew(void *content)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
size_t wordcount(const char *s, char c)
{
	size_t count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			while (*s && *s != c)
				s++;
			count++;
		}
	}
	return (count);
}

char *ft_wd(char const *str, char c)
{
	size_t i;
	char *wd;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	wd = (char *)malloc(sizeof(char) * (i + 1));
	if (!wd)
		return (0);
	i = 0;
	while (*str && *str != c)
	{
		wd[i] = *str;
		i++;
		str++;
	}
	wd[i] = '\0';
	return (wd);
}

char **fail_allo(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
	return (NULL);
}

char **ft_split(char const *s1, char c)
{
	size_t i;
	size_t wc;
	char **strings;

	i = 0;
	if (!s1)
		return (NULL);
	wc = wordcount(s1, c);
	strings = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!strings)
		return (0);
	while (i < wc)
	{
		while (*s1 && *s1 == c)
			s1++;
		strings[i] = ft_wd(s1, c);
		if (!strings[i])
			return (fail_allo(i, strings));
		while (*s1 && *s1 != c)
			s1++;
		i++;
	}
	strings[i] = 0;
	return (strings);
}
int ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
void add_to_objs_list(t_object **head, t_object *new)
{
	t_object *tmp;

	if(!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
t_object *new_object(t_otype type, void *ptr)
{
	t_object *new;

	new = malloc(sizeof(t_object));
	new->type = type;
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}