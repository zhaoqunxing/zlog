#include "../zlog/zlog.h"

int main(int argc, char* argv[])
{
    LOG("E", "%s%d, %s%d", "practice", 1, "practice", 2);
    return 0;
}