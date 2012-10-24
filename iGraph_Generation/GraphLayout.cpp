//
//  GraphLayout.cpp
//  iGraph_Generation
//
//  Created by BildPeter Visuals on 01.11.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//

/*--------------------------------------------------------------------------------------------
 --------------------------------------------------------------------------------------------
 
 
 ------------------------------------------- TO DO   ----------------------------------------
 - Kamada Kawai besser normieren und zentrieren
 - Attribute in den Dateinamen schreiben
 - beliebige Datei übersetzen per 'argv'
 --------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------*/

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>
#include <igraph.h>
#include <iostream.h>
#include <fstream.h>

using namespace std;
using namespace lemon;

int readGraph( ListDigraph &graph, const string &path );

int main(void)
{
    /*
    ListDigraph lGraph;
    FILE                *file;
    
    readGraph( lGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/DatenVerarbeitet/euregio.lgf" );
    
    DigraphWriter< ListDigraph >( lGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/DatenVerarbeitet/euregioArcList.lgf" )
    .skipNodes()
    .run();
    */
    
    

    igraph_t            graph;
    FILE                *file;
    igraph_matrix_t     myMatrix;
    string              layoutInfo;
    string              fileOutPathName = "";
    
    // Matrix has to be initialsed
    igraph_matrix_init( &myMatrix, 0, 0 );

    // Read Edgelist
    file = fopen( "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/DatenVerarbeitet/eu.txt", "r");
    igraph_read_graph_edgelist( &graph,  file, 0, true);
    fclose( file );

    // ------------------------------------------------------------------------------------------------------------
    // -------------------------------              Layout Types            ---------------------------------------
    // ------------------------------------------------------------------------------------------------------------
//    igraph_layout_circle( &graph, &myMatrix); layoutInfo = "Circle";
//    igraph_layout_random( &graph,  &myMatrix ); layoutInfo = "Random";
    igraph_layout_kamada_kawai( &graph,  &myMatrix,  1000, 100, 10, 0.99, 1, 0); layoutInfo = "Kamada_Kawai";
    
    
    // ------------------------------------------------------------------------------------------------------------
    // Console OUTPUT
    // ------------------------------------------------------------------------------------------------------------
    cout << "Nodes: " << igraph_vcount( & graph ) << " Edges: " << igraph_ecount( & graph ) <<endl;
    cout << "Nr of rows: " << igraph_matrix_nrow( &myMatrix ) << " || Nr of colomns: " << igraph_matrix_ncol( &myMatrix ) << endl;

    /*
    for (int i = 0; i < igraph_matrix_nrow( &myMatrix ); i++) {
        cout << i << "\t";
        for (int k = 0; k < igraph_matrix_ncol( &myMatrix ); k++)
            cout << MATRIX( myMatrix, i, k) << "\t";
        cout << endl;
    }
     */
        
    // ------------------------------------------------------------------------------------------------------------
    // Norm the Matrix
    // ------------------------------------------------------------------------------------------------------------
    
    igraph_real_t normValue = igraph_matrix_max( &myMatrix );
    
    for (int i = 0; i < igraph_matrix_nrow( &myMatrix ); i++)
        for (int k = 0; k < igraph_matrix_ncol( &myMatrix ); k++)
            MATRIX( myMatrix, i, k)  = MATRIX( myMatrix, i, k) / normValue ;

    // ----- Output -----
    for (int i = 0; i < igraph_matrix_nrow( &myMatrix ); i++) {
        cout << i << "\t";
        for (int k = 0; k < igraph_matrix_ncol( &myMatrix ); k++)
            cout << MATRIX( myMatrix, i, k) << "\t";
        cout << endl;
        }
        
        

    // Instanzen erzeugen, die gefüllt werden sollen
    igraph_es_t  edgeSelector;  // Sagt welche Arcs vom Graphen ausgewählt werden sollen
    igraph_eit_t edgeIterator;  // Ist der Iterator mit Zahlen
    igraph_integer_t edgeID = 0;
    igraph_integer_t from, to;
    
    // Instanzen initiieren
    igraph_es_all( & edgeSelector, IGRAPH_EDGEORDER_ID );           // EdgeSelector
    igraph_eit_create( & graph, edgeSelector, & edgeIterator );     // EdgeIterator
    
    // ----------------------------------------- LEMON GRAPH FORMAT -----------------------------------------------
    // Die Topologie mit Maps der Layout Koordinaten
    // ------------------------------------------------------------------------------------------------------------
    
    ofstream    fileOut;
    fileOutPathName = "/Users/sonneundasche/Desktop/euregio_Layout_" + layoutInfo + ".lgf";
    char *fileOutPathNameCHAR = const_cast<char*>(fileOutPathName.c_str());
    cout << "Output file name: " << fileOutPathName << endl;    
    fileOut.open(  fileOutPathNameCHAR );

    
    // --- Arttibutes
    fileOut << "# Layout Type: \t" << layoutInfo << endl;
    fileOut << "# Amount of nodes: \t" << igraph_vcount( &graph ) << endl;
    fileOut << "# Amount of arcs: \t" << igraph_ecount( &graph ) << endl;
    fileOut << endl << endl;
    
    // --- Nodes
    fileOut << "@nodes" << endl;
    fileOut << "label" << "\txCoord" << "\tyCoord" << endl;
    for (int i = 0; i < igraph_matrix_nrow( &myMatrix ); i++) {
        fileOut << i << "\t";
        for (int k = 0; k < igraph_matrix_ncol( &myMatrix ); k++)
            fileOut << MATRIX( myMatrix, i, k) << "\t";
        fileOut << endl;
    }
    
    // --- Arcs
    fileOut << endl << endl << "@arcs" << endl;
    fileOut << "\t\t" << "label" << endl;
    for ( IGRAPH_EIT_RESET( edgeIterator ); IGRAPH_EIT_END( edgeIterator ) == false; IGRAPH_EIT_NEXT( edgeIterator )) {
        igraph_edge( &graph, edgeID, &from,  &to);              // Geht durch die 'edgeID' und weist 'from' & 'to' die IDs zu
        fileOut << from << "\t" << to << "\t" << edgeID << endl;
//        fileOut << from << "\t" << to << endl;
        edgeID++;
    }
    
    
    
    // ------------------------------------------------------------------------------------------------------------
    // --- CLOSE ---
    fileOut.close();
    igraph_matrix_destroy( & myMatrix );
    igraph_eit_destroy( &edgeIterator );
    igraph_es_destroy(  &edgeSelector );
    igraph_destroy(&graph);
    
    
    cout << "Erledigt!" << endl;

    
    return 0;
}

    
int readGraph( ListDigraph &graph, const string &path ){
    try {
        digraphReader( graph, path)
        .run();
    } catch (Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
        return -1;
    }
    return 0;
}

