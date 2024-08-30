#ifndef TESTS_H
#define TESTS_H

#include "linux-list.h"

void load_words(void);
void close_all(void);
void do_test_a(int count);
void do_test_b(int count);

struct struct_a {
	char *name;
	int name_len;
	int major;
	int minor;
	void *priv;
	struct list_head list;
};

struct struct_b {
	char *name;
	int name_len;
	int major;
	int minor;
	void *priv;
};

struct priv_a {
	int a;
	int b;
	int c;
};

struct priv_b {
	int a[16];
};

#endif /* TESTS_H */