#include "io.hpp"
#include "dense_dynamic.hpp"
#include "block_stripe.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        return 0;
    }
    stringstream ss;
    ss.clear();
    ss << argv[2];
    double teleport_parameter;
    ss >> teleport_parameter;
    if (!strcmp(argv[1], "dense"))
    {
        dense_dynamic(teleport_parameter);
        return 0;
    }
    
    block_strip(teleport_parameter);
}
