#include <iostream>
#include "gmsh_parser.h"

int main(){
    GMSHParser gmshParser;

    gmshParser.open("../../models/vector_potential.geo");

    std::cout<<"test"<<std::endl;
}
