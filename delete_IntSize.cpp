//
//  delete_IntSize.cpp
//  iGraph_Generation
//
//  Created by Peter on 22.01.13.
//  Copyright (c) 2013 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <lemon/list_graph.h>

int main(){

    lemon::ListDigraph::Arc mArc;
    int *a;
    bool *b;

    std::cout << std::numeric_limits<unsigned int>::digits10 << "\t" << sizeof(mArc) << std::endl;

}