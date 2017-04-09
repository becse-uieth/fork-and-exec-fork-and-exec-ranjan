#include <stdlib.h>

int main(void)
{
    int result;

    result = system("date | tee result.log");
    return 0;
}
