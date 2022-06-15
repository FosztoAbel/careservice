#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "modositas.h"
#include "fomenu.h"
#include "debugmalloc.h"

int main()
{
    Auto *tomb = dinamikus();
    feltoltes(tomb);
    menu(tomb);
    free(tomb);

    return 0;
}
