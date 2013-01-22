
//
//  main.cpp
//  iGraph_Generation
//
//  Created by Peter A. Kolski on 05.10.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//


/*--------------------------------------------------------------------------------------------
  --------------------------------------------------------------------------------------------
 
 
 ------------------------------------------- TO DO   ----------------------------------------
 - Einlesen testen
 - Attribute in den Dateinamen schreiben
 - beliebige Datei übersetzen per 'argv'
  --------------------------------------------------------------------------------------------
  ------------------------------------------------------------------------------------------*/


#include <igraph.h>
#include <iostream.h>
#include <fstream.h>

using namespace std;

int main( int argc, char** argv)
{
    if (argc < 2) {
        cout << "Not enought arguments!" << endl << "NrNodes - density" << endl;
        return -1;
    }
    
    
    igraph_integer_t    nrNodesToCreate  = argv[0];
    igraph_integer_t    nrOutArcsPerNode = argv[1];
    
//    ap.ref
    
    igraph_t            graph;
    
//    igraph_real_t       probArcs = 5.0/10;
//    igraph_erdos_renyi_game(&graph, IGRAPH_ERDOS_RENYI_GNP, nrNodesToCreate , probArcs,
//                            IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
//    igraph_full( &graph, nrNodesToCreate, true, false);
    igraph_barabasi_game( &graph, nrNodesToCreate, nrOutArcsPerNode, NULL, false, true );
    
    
    cout << igraph_vcount( & graph ) << " e: " << igraph_ecount( & graph ) <<endl;
    
    
    // Instanzen erzeugen, die gefüllt werden sollen
    igraph_es_t  edgeSelector;  // Sagt welche Arcs vom Graphen ausgewählt werden sollen
    igraph_eit_t edgeIterator;  // Ist der Iterator mit Zahlen
    igraph_integer_t edgeID = 0;
    igraph_integer_t from, to;
    
    // Instanzen initiieren
    igraph_es_all( & edgeSelector, IGRAPH_EDGEORDER_ID );           // EdgeSelector
    igraph_eit_create( & graph, edgeSelector, & edgeIterator );     // EdgeIterator
    
    // ----------------- LEMON GRAPH FORMAT ------------------------
    // Die Pure Topologie ohne Maps
    
    ofstream    fileOut;
    int         nodesAmount = igraph_vcount( &graph );  // Anzahl der Knoten
    
    fileOut.open("iGraph_BarabasiAlbert.lgf");

    
    // --- Arrtibutes
//    fileOut << "@attributes" << endl;    
    //    fileOut << "Type of graph: \t Barabasi-Albert" << endl;
    fileOut << "# Amount of nodes: \t" << igraph_vcount( &graph ) << endl;
    fileOut << "# Amount of arcs: \t" << igraph_ecount( &graph ) << endl;
    //    fileOut << "# Amount of OUT-arcs per node \t" << nrOutArcsPerNode << endl;
    fileOut << endl << endl;
    
    // --- Nodes
    fileOut << "@nodes" << endl;
    fileOut << "label" << endl;
    for ( int i = 0; i < nodesAmount; i++) {
        fileOut << i << endl;
    }
    
    // --- Arcs
    fileOut << endl << endl << "@arcs" << endl;
    fileOut << "\t\t" << "label" << endl;    
    for ( IGRAPH_EIT_RESET( edgeIterator ); IGRAPH_EIT_END( edgeIterator ) == false; IGRAPH_EIT_NEXT( edgeIterator )) {
        igraph_edge( &graph, edgeID, &from,  &to);              // Geht durch die 'edgeID' und weist 'from' & 'to' die IDs zu
        fileOut << from << "\t" << to << "\t" << edgeID << endl;
        edgeID++;
    }

    // --- CLOSE ---
    fileOut.close();
    igraph_eit_destroy( &edgeIterator );
    igraph_es_destroy(  &edgeSelector );
    igraph_destroy(&graph);
    
    cout << "Erledigt!" << endl;
    
    return 0;
}
