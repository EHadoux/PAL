#include "Include/APS.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void set_input(FILE *in);
std::unique_ptr<PAL::APS> parse();

int main(int argc, char **argv) {
    int c;
    FILE *f;
    bool fromfile = false;

    while((c = getopt(argc, argv, "f:")) != -1)
        switch(c) {
            case 'f':
                f = fopen(optarg, "r");
                if(!f)
                    throw invalid_argument("Unknown file: " + string(optarg));
                set_input(f);
                fromfile = true;
                break;
            default:
                abort();
        }

    set_input(stdin);
    std::unique_ptr<PAL::APS> aps = parse();
    cout << "Parsed APS: " << std::endl <<  *aps << endl;
    if(fromfile)
        fclose(f);
}
