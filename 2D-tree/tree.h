//
//  tree.h
//  2D-tree
//
//  Created by Valentin Paz Marcolla on 30/09/14.
//  Copyright (c) 2014 Valentin Paz Marcolla. All rights reserved.
//

#ifndef ___D_tree__tree__
#define ___D_tree__tree__

#ifndef EPSILON
#define EPSILON 0.001
#endif

#include "vec2.h"
#include <vector>

typedef struct node{
    vec2 p;
    node * left;
    node * right;
} nodo;

class tree {
    nodo root;
    
public:
    tree (vec2 * arr, int size);
    bool searchFor(vec2 val);
    void add (vec2 val);
    std::vector<vec2> rangeSearch(vec2 start, vec2 end);
    vec2 closest (vec2 val);
private:
    nodo* build(int depth, vec2 * arr, int size);
    bool _searchFor(int depth, nodo* sub, vec2 val);
    void _rangeSearch(int depth, nodo* sub, vec2 min, vec2 max);
    bool equal(float a, float b);
    void _add(int depth, nodo* sub, vec2 val);
    void _closest(int depth, nodo* sub, vec2 val);
    float distance(vec2 a, vec2 b);
    
    float minDistance;
    vec2 minP;
    std::vector<vec2> inRange;
};

#endif /* defined(___D_tree__tree__) */
