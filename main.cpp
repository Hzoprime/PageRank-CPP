#include "io.hpp"
#include "dense_dynamic.hpp"
#include "block_stripe.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 0;
    }
    if (!strcmp(argv[1], "dense"))
    {
        dense_dynamic();
        return 0;
    }
    
    block_strip();
}
