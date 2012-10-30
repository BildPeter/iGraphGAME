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
#include <lemon/time_measure.h>

#include "peter/layouts/layoutKamadaKawai.h"

using namespace lemon;
using namespace std;

int main(){

    ListDigraph                     g;
    
    /*
     NODES
     name	xCoord	yCoord	size_all	size_cattle	size_pork	degree	inDegree	outDegree	inFlow	outFlow	flowDifference	transactions	     
     int    long    long    int ...etc...
     
     ARCS
     label	from	to	flow	transactions
     int
     */
    ListDigraph::NodeMap< long >    xCoord(g);
    ListDigraph::NodeMap< long >    yCoord(g);
    ListDigraph::NodeMap< int >     name(g);
    ListDigraph::NodeMap< int >     size_pork(g);
    ListDigraph::NodeMap< double >  xCoordTopo(g);
    ListDigraph::NodeMap< double >  yCoordTopo(g);
    ListDigraph::ArcMap<  int >     from(g);
    ListDigraph::ArcMap<  int >     to(g);
    ListDigraph::ArcMap<  int >     flow(g);
    
    try {
        digraphReader( g, "/Users/sonneundasche/Dropbox/FLI/DATA/EinBundesland/03 Processed/tradeData_processed.lgf")
        .nodeMap("name", name)
        .nodeMap("xCoord", xCoord)
        .nodeMap("yCoord", yCoord)
        .nodeMap("size_pork", size_pork)
        .arcMap("from", from)
        .arcMap("to", to)
        .arcMap("flow", flow)
        .run();
    } catch (lemon::Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
    }
    
    cout << "Daten gelesen"<< endl;
    Timer   T;
    
    layoutKamadaKawai* KKdyn = new layoutKamadaKawai( &g);
    KKdyn->setCoordinateMaps( &xCoordTopo, &yCoordTopo);
    KKdyn->calculate( 100 );
    delete KKdyn;
    
    cout << "Layout Berechnung: " << T.realTime() << " sek" << endl;
    
    digraphWriter( g, "/Users/sonneundasche/Dropbox/FLI/DATA/EinBundesland/03 Processed/data_Layout_kamadaKawai.lgf")
    .nodeMap("name", name)
    .nodeMap("xCoord", xCoord)
    .nodeMap("yCoord", yCoord)
    .nodeMap("xCoordTopo", xCoordTopo)
    .nodeMap("yCoordTopo", yCoordTopo)
    .nodeMap("size_pork", size_pork)
    .arcMap("from", from)
    .arcMap("to", to)
    .arcMap("flow", flow)
    .run();
    
    cout << "done!" << endl;
}