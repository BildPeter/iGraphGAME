//
//  LEMON2iGraph.h
//  iGraph_Generation
//
//  Created by Peter A. Kolski on 30.10.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//

#include <lemon/list_graph.h>
#include <igraph.h>

using namespace lemon;
using namespace std;

#ifndef iGraph_Generation_LEMON2iGraph_h
#define iGraph_Generation_LEMON2iGraph_h

class layoutKamadaKawai{
public:
    layoutKamadaKawai( ListDigraph *LEMON_Graph );
    ListDigraph         *mLEGraph;
    
    igraph_t            g;
    igraph_vector_t     edgeVec;

    void initGraph();
};

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

layoutKamadaKawai::layoutKamadaKawai(ListDigraph *LEMON_Graph )
{
    mLEGraph = LEMON_Graph;
}


void layoutKamadaKawai::initGraph(){
    // 1.) Vector erstellen
    // 2.) Edges aus Lemon in den Vector
    // 3.) Graph erstellen
    
    igraph_vector_init( &edgeVec, countArcs( *mLEGraph)*2 );
    int i = 0;
    for (ListDigraph::ArcIt a( *mLEGraph ); a!=INVALID; ++a) {
        VECTOR( edgeVec )[ i++ ] = (*mLEGraph).id( (*mLEGraph).source( a ) );
        VECTOR( edgeVec )[ i++ ] = (*mLEGraph).id( (*mLEGraph).target( a ) );
    }
    igraph_create( &g, &edgeVec, countNodes( *mLEGraph ), 1);  // graph erstellen

}

#endif
