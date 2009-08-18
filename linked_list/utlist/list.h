
#define BUFLEN 20

typedef struct el {
  char bname[BUFLEN];
  int foo;
  struct el *next, *prev;
} el;



int add_number(int num);

int add_pre_number(int num);

void print_sorted();

void get_head_and_del();
