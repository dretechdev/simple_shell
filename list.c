#include "main.h"

/**
 * add_node - adds a node to the start of the list.
 * @head: address of pointer to head node.
 * @str: str field of node.
 * @num: node index
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_node_end - adds a node to the end of the list.
 * @head: address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 * Return: size of list.
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nod, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = _strdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_list_str - prints only the str element of a list
 * @h: pointer to first node.
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete.
 * Return: 1 (success), 0 (failure)
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nodes, *prev_nod;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nodes = *head;
		*head = (*head)->next;
		free(nodes->str);
		free(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (a == index)
		{
			prev_nod->next = nodes->next;
			free(nodes->str);
			free(nodes);
			return (1);
		}
		a++;
		prev_nod = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *nodes, *next_nod, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nodes = head;
	while (nodes)
	{
		next_nod = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = next_nod;
	}
	*head_ptr = NULL;
}

