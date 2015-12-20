/**
 Program:	Binary Search Tree Height Calculation
 Author:    Cheechee Lin
 Date:		December 1, 2015
 
 Description:
 This program computes the average height of BSTs with n nodes.
 
 */
#include "bst.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;


// shuffles numbers from 1 to n
void shuffleVector( vector<int>& );

/**
 Shuffles a vector with n entries.
 The algorithm:
 - For every index from 1 to n
 Generate random index r between 1 and n
	Exchange elements v[i] and v[r].
 */
void shuffleVector( vector<int>& v ){
    for ( int i=0 ; i < v.size() ; i++ ){
        int j = rand() % v.size() ; // <-- New random position
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}


//determine stopping condition of this program: if |prev_avg-new_avg| is significantly small (less than 0.01), terminate program and display average. used as a do-while loop in the main routine below
bool avg_is_constant (double prev_avg, double new_avg) {
    if (std::abs(prev_avg-new_avg)<=0.001 && std::abs(prev_avg-new_avg)!=0)
        return false;
    else {
        return true;
    }
}

//helper function for computing average height that takes in a binary tree as a parameter and computes the average
double compute_average_height_helper(vector< BSTree<int> > v){
    int total=0;
    for (int i=0; i<v.size(); i++){
        total+=v[i].height();
    }
    double avg= (double)total/v.size();
    return avg;
}


//the compute_average_height function takes in an int parameter of the number of nodes and continues running until the stopping condition implemented above. All the couts in this function are simply for reporting purposes and can be commented out for cleaner output.
//this function returns a double of the biggest number of trees averaged

double compute_average_height(int num_of_nodes){
    
    
    long int startingTime = static_cast<long int>( time( NULL ) );
    srand( startingTime );
    
    
    // A vector of trees!!! ( a forest )
    vector< BSTree<int> > forest;
    bool fortest;
    
    vector<double> storingAvg(0);
    
    
    do{
        
        vector<int> v(num_of_nodes);
        
        //update the average should this not be the first or second run
        if (storingAvg.size()!=0 && storingAvg.size()!=1)
            storingAvg.erase(storingAvg.begin());
        
        // populate the vector with numbers from 1 to num_of_nodes
        for (int i=0 ; i < v.size() ; i ++ )
            v[i] = i+1;
        
        // shuffle the vector
        shuffleVector( v );
        
        // Generate a BST with the elements of v
        BSTree<int> tree;
        for (int i=0 ; i < v.size() ; i ++ ){
            tree.insert(v[i]);
        }
        
        cout<<endl;
        
        //compare new tree to current trees in forest and discard if tree is a duplicate, check is only performed if there is more than one tree in the forest
        if (forest.size()>1) {
            bool not_same_tree= true;
            for (int i=0; i<forest.size(); i++){
                if (forest[i]==tree)
                    not_same_tree=false;
            }
            if(not_same_tree)
                forest.push_back(tree);
        }
        else forest.push_back(tree);
        
        cout << endl;
        
        // CAN COMMENT: Display statistics: heights of the trees
        for ( int i = 0 ; i < forest.size() ; i++ ){
            cout << "Tree " << i+1 << " has height: "
            << forest[i].height() << endl;
        }
        

    
        //computing the average height of the trees in the forest
        storingAvg.push_back(compute_average_height_helper(forest));
        
        //CAN COMMENT: Display current height average
        cout<<"The current height average is "<<compute_average_height_helper(forest)<<endl;
        
        
    }while(avg_is_constant(storingAvg[0], storingAvg[1]));
    
    
    return storingAvg[1];

}