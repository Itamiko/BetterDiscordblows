#include <stdio.h>
#include <stdlib.h>
#include <argtable3.h>

struct arg_lit *h, *i, *u, *r, *c, *config;
struct arg_str *f, *flavor;
struct arg_end *end;

void freemem_exit(int fail, void **argtable)
{
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	exit(fail ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void usage(const int fail)
{
	fprintf(stdout,
		"Usage: bdb [option]\n\n"
		"OPTIONS\n"
		" -h --help			Print help information\n"
		" -i --install			Install BetterDiscord patch\n"
		" -u --uninstall			Uninstall BetterDiscord patch\n"
		" -r --restore			Restore discord client to original state\n"
		" -f --flavor <version name>	Discord favor version\n"
		" -c --config <key> [value]	Change default configuration\n");
	exit(fail ? EXIT_FAILURE : EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	void *argtable[] = {
		h = arg_lit0("h", "help", "Print help information"),
		i = arg_lit0("i", "install", "Install BetterDiscord Patch"),
		u = arg_lit0("u", "uninstall", "Uninstall BetterDiscord patch"),
		r = arg_lit0("r", "restore",
			     "Restore BetterDiscord to a fresh start"),
		f = arg_str0("f", "flavor", "<Discord Flavor>",
			     "Choose a different discord version"),
		c = arg_litn("c", "config", 1, 2,
			     "Change default configuration values"),
		end = arg_end(20)
	};

	const char *progname = "bdb";
	int nerrors;

	if (arg_nullcheck(argtable) != 0) {
		printf("%s: insufficient memory\n", progname);
		freemem_exit(1, argtable);
	}

	nerrors = arg_parse(argc, argv, argtable);

	if (h->count > 0) {
		usage(1);
	}
	if (nerrors > 0) {
		printf("Try '%s --help' for more information.\n", progname);
		freemem_exit(0, argtable);
	}

	return 0;
}
