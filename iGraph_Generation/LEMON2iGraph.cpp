//
//  LEMON2iGraph.cpp
//  iGraph_Generation
//
//  Created by Peter A. Kolski on 30.10.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//


/*
 TASK:
 + Create a iGraph from a LEMON graph.
 + Keep the vertex ids, so you can transfere the coordinates
 + put it into a class
 + calculate kamadaKawai
 + put the coordinates into a LEMON map
*/

#include <lemon/list_graph.h>
#include <igraph.h>

#include "LEMON2iGraph.h"

using namespace lemon;
using namespace std;

int main(){

    ListDigraph                         leGr;
    ListDigraph::NodeMap< double >      xCoord( leGr );
    ListDigraph::NodeMap< double >      yCoord( leGr );
    leGr.addNode();
    leGr.addNode();
    leGr.addNode();
    leGr.addArc( leGr.nodeFromId( 1 ), leGr.nodeFromId( 2 ) );
    
    layoutKamadaKawai                   KK( &leGr);
    KK.setCoordinateMaps( &xCoord, &yCoord );
    KK.calculate( 100 );
    
    cout << endl << "LEMON" << endl;
    for (ListDigraph::NodeIt n(leGr); n!=INVALID; ++n) {
        cout << leGr.id( n ) << "\t" << xCoord[ n ] << "\t" << yCoord[ n ] << endl;
    }
    
    return 0;
}
