#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <string.h>
#include <pty.h>
#include <stdio.h>
#include "hl_vt100.h"

void disp(struct vt100_headless *vt100)
{
    unsigned int y;
    const char **lines;

    lines = vt100_headless_getlines(vt100);
    write(1, "\n", 1);
    for (y = 0; y < vt100->term->height; ++y)
    {
        write(1, "|", 1);
        write(1, lines[y], vt100->term->width);
        write(1, "|\n", 2);
    }
}

int main(int ac, char **av)
{
    struct vt100_headless *vt100_headless;

    if (ac == 1)
    {
        puts("Usage: test PROGNAME");
        return EXIT_FAILURE;
    }
    vt100_headless = new_vt100_headless();
    vt100_headless->changed = disp;
    vt100_headless_fork(vt100_headless, av[1], (av + 1));
    vt100_headless_main_loop(vt100_headless);
    return EXIT_SUCCESS;
}
