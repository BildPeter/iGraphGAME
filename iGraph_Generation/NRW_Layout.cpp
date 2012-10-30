//
//  NRW_Layout.c
//  iGraph_Generation
//
//  Created by Peter A. Kolski on 30.10.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//



#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>

#include "peter/layouts.h"

using namespace lemon;
using namespace std;

int main(){

    ListDigraph                     g;
    ListDigraph::NodeMap< double >  xCoord(g);
    ListDigraph::NodeMap< double >  yCoord(g);

    
    digraphReader( g, "")
    .run();

    layoutKamadaKawai* KKdyn = new layoutKamadaKawai( &g);
    KKdyn->setCoordinateMaps( &xCoord, &yCoord);
    KKdyn->calculate( 100 );
    delete KKdyn;
}