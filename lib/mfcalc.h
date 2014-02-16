struct symrec
{
	char	*name;
	int		type;
	union {
		double	var;
		double	(*fnctptr)();
	} value;
	struct symrec *next;
};

typedef struct symrec symrec;

extern symrec *sym_table;

symrec *putsym(char *, int);
symrec *getsym(char *);
