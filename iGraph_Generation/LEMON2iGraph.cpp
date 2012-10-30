//
//  LEMON2iGraph.cpp
//  iGraph_Generation
//
//  Created by Peter A. Kolski on 30.10.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//


/*
 TASK:
 
 
 */

#include <lemon/list_graph.h>
#include <igraph.h>

using namespace lemon;
using namespace std;

int main(){

    ListDigraph leGr;

    leGr.addNode();
    leGr.addNode();
    leGr.addNode();
    leGr.addArc( leGr.nodeFromId( 1 ), leGr.nodeFromId( 2 ) );
    
    
    /*
     Vector erstellen
     Graph erstellen
     
     */
    
    igraph_t    g;
    igraph_vector_t edgeVec;
    igraph_vector_init( &edgeVec, countArcs( leGr)*2 );
    
    int i = 0;
    for (ListDigraph::ArcIt a( leGr ); a!=INVALID; ++a) {
        VECTOR( edgeVec )[ i++ ] = leGr.id( leGr.source( a ) );
        VECTOR( edgeVec )[ i++ ] = leGr.id( leGr.target( a ) );
    }
    igraph_create( &g, &edgeVec, countArcs( leGr ), 1);  // graph erstellen
    
    
    // Instanzen erzeugen, die gefüllt werden sollen
    igraph_es_t  edgeSelector;  // Sagt welche Arcs vom Graphen ausgewählt werden sollen
    igraph_eit_t edgeIterator;  // Ist der Iterator mit Zahlen
    
    // Instanzen initiieren
    igraph_es_all( & edgeSelector, IGRAPH_EDGEORDER_ID );       // EdgeSelector
    igraph_eit_create( & g, edgeSelector, & edgeIterator );     // EdgeIterator
    igraph_integer_t edgeID = 0;
    igraph_integer_t from, to;
    
    cout << "Edges:" << endl;
    cout << "from to id" << endl;
    for ( IGRAPH_EIT_RESET( edgeIterator ); IGRAPH_EIT_END( edgeIterator ) == false; IGRAPH_EIT_NEXT( edgeIterator )) {
        igraph_edge( &g, edgeID, &from,  &to);              // Geht durch die 'edgeID' und weist 'from' & 'to' die IDs zu
        cout << from << "\t" << to << "\t" << edgeID << endl;
        edgeID++;
    }
    

    
    
    
    return 0;
}
