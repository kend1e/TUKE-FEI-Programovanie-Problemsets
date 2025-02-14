#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

uint32_t handle_num(uint64_t num);

int main()
{
    uint64_t sum = 0;
    
    while(true)
    {
        int c = getchar();
        if(c == EOF || c == '\n' || c == '\r')
            break;
        if(c < '0' || c > '9')
            continue;
        sum += c - '0';
    }

    printf("%u\n", handle_num(sum));
}

uint32_t handle_num(uint64_t num)
{
    int sum = 0;
    while(num > 0)
    {
        sum += num % 10;
        num /= 10;
    }

    if(sum > 9)
        return handle_num(sum);
    return sum;
}