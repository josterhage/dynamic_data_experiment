#ifndef CS_LIST_H
#define CS_LIST_H

#include <stdlib.h>

/* A more traditional linked list implementation using separate objects
 * with opaque pointers to hold the data */

/* Singly-linked list */

struct slist_node {
	struct slist_node *next;
	void *opaque;
};

/**
 * @brief Creates a new slist_node
 * @param opaque Data held by the node
 * @return a new slist_node
 */
static inline struct slist_node *new_slist_node(void *opaque)
{
	struct slist_node *new_node = calloc(1, sizeof(struct slist_node));
	new_node->opaque = opaque;
	return new_node;
}

/**
 * @brief Adds a new item to the middle of a list
 * @param new New slist_node
 * @param prev Node to add after
 */
static inline void slist_insert_at(struct slist_node *new, struct slist_node *prev)
{
	new->next = prev->next;
	prev->next = new;
}

/**
 * @brief Adds a new item to the tail of the list
 * @param head Pointer to the list head
 * @param new New node to add
 */
static inline void slist_add(struct slist_node *head, struct slist_node *new)
{
	struct slist_node *tail = head;
	while (tail->next) { tail = tail->next; }
	tail->next = new;
}

/**
 * @brief Deletes the item at the tail of the list
 * @param head Pointer to the list head
 * @return Pointer to the removed item
 */
static inline struct slist_node *slist_del_tail(struct slist_node *head)
{
	struct slist_node *cursor = head;
	while (cursor->next->next) { cursor = cursor->next; }
	struct slist_node *ret = cursor->next;
	cursor->next = NULL;
	return ret;
}

/**
 * @brief Deletes a specific node from a list
 * @param head Pointer to the list head
 * @param node Node to remove
 * @return 0 on success, -1 if the node is not in the list
 */
static inline int slist_del_at(struct slist_node *head, struct slist_node *node)
{
	struct slist_node *cursor = head;
	while (cursor->next && cursor->next != node) {cursor = cursor->next; }
	if (!cursor->next)
		return -1;
	cursor->next = node->next;
	return 0;
}

/**
 * @brief Declare an iterator over an slist
 * @param head Pointer to the list head
 * @param cursor Pointer to a `struct slist_node` to use as the cursor
 */
#define slist_for_each(head, cursor) \
	for (cursor = head; cursor->next; cursor = cursor->next)

/* Doubly linked list */

struct dlist_node {
	struct dlist_node *next;
	struct dlist_node *prev;
	void *opaque;
} ;

static inline struct dlist_node *new_dlist_node(void *opaque)
{
	struct dlist_node *new = calloc(1, sizeof(struct dlist_node));
	new->next = new;
	new->prev = new;
	new->opaque = opaque;
}

static inline void __dlist_add(struct dlist_node *new,
							  struct dlist_node *next,
							  struct dlist_node *prev)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * @brief Adds a new dlist_node
 * @param  
 * @param head 
 */
static inline void dlist_add(struct dlist_node *new, struct dlist_node *head)
{
	__dlist_add(new, head, head->next);
}

#endif /* CS_LIST_H */