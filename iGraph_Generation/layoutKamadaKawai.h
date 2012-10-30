//
//  layoutKamadaKawai.h
//
//  Created by Peter A. Kolski on 30.10.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//

#include <lemon/list_graph.h>
#include <igraph.h>

using namespace lemon;
using namespace std;

#ifndef layoutKamadaKawai_h
#define layoutKamadaKawai_h

class layoutKamadaKawai
{
public:
    layoutKamadaKawai( ListDigraph *LEMON_Graph );
    ~layoutKamadaKawai();
    
    void setCoordinateMaps( ListDigraph::NodeMap< double > *xMap, ListDigraph::NodeMap< double > *yMap );
    void setParameters( double sigma, double initTemp, double coolExp, double KKexp, double useSeed);
    void calculate( int interations);
    
private:
    ListDigraph         *mLEGraph;
    igraph_t            g;
    double              mSigma, mInitTemp, mCoolExp, mKKExp, mUseSeed;
    igraph_vector_t     edgeVec;
    igraph_matrix_t     mLayoutMatrix;
    ListDigraph::NodeMap< double >      *mXCoord, *mYCoord;
    bool                mMapsAreSet;
    
    void initGraph();
};

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

layoutKamadaKawai::layoutKamadaKawai(ListDigraph *LEMON_Graph )
{
    mLEGraph = LEMON_Graph;
    mSigma      = countNodes( *mLEGraph ) / 4;
    mInitTemp   = 10.0;
    mCoolExp    = 0.99;
    mKKExp      = 1;
    mUseSeed    = 0;

    mMapsAreSet = false;
    
    initGraph();
}

layoutKamadaKawai::~layoutKamadaKawai(){
    igraph_matrix_destroy( &mLayoutMatrix );
    igraph_vector_destroy( &edgeVec );
    igraph_destroy( &g );
}


void layoutKamadaKawai::initGraph(){
    // 1.) Vector erstellen
    // 2.) Edges aus Lemon in den Vector
    // 3.) Graph erstellen
    
    igraph_vector_init( &edgeVec, countArcs( *mLEGraph)*2 );
    int i = 0;
    for (ListDigraph::ArcIt a( *mLEGraph ); a!=INVALID; ++a) {
        VECTOR( edgeVec )[ i++ ] = mLEGraph->id( mLEGraph->source( a ) );
        VECTOR( edgeVec )[ i++ ] = mLEGraph->id( mLEGraph->target( a ) );
    }
    igraph_create( &g, &edgeVec, countNodes( *mLEGraph ), 1);  // graph erstellen

    igraph_matrix_init( &mLayoutMatrix, 0, 0 );
}

void layoutKamadaKawai::setCoordinateMaps(ListDigraph::NodeMap<double> *xMap, ListDigraph::NodeMap<double> *yMap){
    mXCoord = xMap;
    mYCoord = yMap;
    
    mMapsAreSet = true;
}

void layoutKamadaKawai::setParameters(double sigma, double initTemp, double coolExp, double KKexp, double useSeed ){
    mSigma      = sigma;
    mInitTemp   = initTemp;
    mCoolExp    = coolExp;
    mKKExp      = KKexp;
    mUseSeed    = useSeed;
}


void layoutKamadaKawai::calculate( int iterations ){

    igraph_layout_kamada_kawai( &g,  &mLayoutMatrix,  iterations, mSigma, mInitTemp, mCoolExp, mKKExp, mUseSeed);

    
    if (mMapsAreSet) {
        // --- Node
        for (int i = 0; i < igraph_matrix_nrow( &mLayoutMatrix ); i++) {
            // --- X & Y Coordinate
            (*mXCoord)[ mLEGraph->nodeFromId( i ) ] =  MATRIX( mLayoutMatrix, i, 0);
            (*mYCoord)[ mLEGraph->nodeFromId( i ) ] =  MATRIX( mLayoutMatrix, i, 1);
        }
    }
    else{
        cout << "Maps are not assigned. Please call 'setCoordinateMaps'." << endl;
    }
}
#endif
