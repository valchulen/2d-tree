//
//  tree.cpp
//  2D-tree
//
//  Created by Valentin Paz Marcolla on 30/09/14.
//  Copyright (c) 2014 Valentin Paz Marcolla. All rights reserved.
//

#include "tree.h"
#include <cmath>
//#include <iostream>
//#include <fstream>

using namespace std;

//ofstream fout("build.out");

bool tree::equal(float a, float b) {
    return (abs(a-b) / (abs(a)+abs(b))) < EPSILON;
}

float tree::distance( const vec2 a, const vec2 b){
    return sqrt( pow(b.x-a.x, 2) + pow(b.y-a.y,  2) );
}

tree::tree(vec2 * arr, int size) { //lesto
    (*this).root = *build(0, arr, size);
}
//int indent = -1;
nodo* tree::build(int depth, vec2 *arr, int size) { //lesto
    //indent++;
    nodo* n = new nodo;
    
    if (size == 1) {
        n->left = NULL;
        n->right = NULL;
        n->p.x = arr[0].x;
        n->p.y = arr[0].y;
        //fout<<string(indent, ' ')<<"P ("<<n->p.x<<", "<<n->p.y<<") profundidad= "<<depth<<" es leaf;"<<endl;
        //indent--;
        return n;
    }
    
    vec2* lefts;
    vec2* rights;
    int med = size/2;
    
    if (depth % 2 == 0)
        sortByX(arr, size);
    else
        sortByY(arr, size);
    
    rights = arr;
    lefts = arr+med;
    
    //guardo el valor del nodo, para que no se modifique nunca (por las dudas)
    n->p.x = arr[med].x;
    n->p.y = arr[med].y;
    
    //fout<<string(indent, ' ')<<"P ("<<n->p.x<<", "<<n->p.y<<") profundidad= "<<depth<<", hijos: menores"<<endl<<string(indent, ' ')<<"{"<<endl;
    
    n->right = build(depth+1, rights, med);
    
    //fout<<string(indent, ' ')<<"}"<<endl<<string(indent, ' ')<<" mayores "<<endl<<string(indent, ' ')<<"{"<<endl;
    
    n->left = build(depth+1, lefts, med);
    
    //fout<<string(indent, ' ')<<"}"<<endl;
    
    //indent--;
    return n;
    
}

bool tree::searchFor( const vec2 val) { //lesto
     return _searchFor(0, &root, val);
}

bool tree::_searchFor(int depth, nodo* sub, const vec2 val) { //lesto
    if ((equal(sub->p.x, val.x) && equal(sub->p.y, val.y))) {
        return true;
    } else {
        nodo* subtree = NULL;
        float cmp = 0, cmpVal = 0;
        
        if (depth % 2 == 0) {
            cmp = sub->p.x;
            cmpVal = val.x;
        } else {
            cmp = sub->p.y;
            cmpVal = val.y;
        }
        
        if (cmpVal < cmp)
            subtree = sub->right;
        else
            subtree = sub->left;
        if (subtree ==  NULL)
            return false;
        
        //cout<<"("<<sub->p.x<<", "<<sub->p.y<<")"<<endl;
        return _searchFor(depth+1, subtree, val);
    }
}

void tree::add(const vec2 val) { //lesto
    _add(0, &root, val);
}

void tree::_add(int depth, nodo *sub, const vec2 val) { //lesto
    nodo* subtree = NULL;
    float cmp = 0, cmpVal = 0;
    
    if(depth % 2 == 0) {
        cmp = sub->p.x;
        cmpVal = val.x;
    } else {
        cmp = sub->p.y;
        cmpVal = val.y;
    }
    
    if (cmpVal < cmp){
        if (sub->right == NULL) {
            sub->right = new nodo;
            sub->right->right = NULL;
            sub->right->left = NULL;
            sub->right->p = val;
            return;
        } else
            subtree = sub->right;
    } else {
        if (sub->left == NULL) {
            sub->left = new nodo;
            sub->left->right = NULL;
            sub->left->left = NULL;
            sub->left->p = val;
            return;
        } else
            subtree = sub->left;
    }
    
    _add(depth+1, subtree, val);
}

vector<vec2> tree::rangeSearch(const vec2 start, const vec2 end) {
    inRange.clear();
    _rangeSearch(0, &root, start, end);
    return inRange;
}

void tree::_rangeSearch(int depth, nodo *sub, const vec2 min, const vec2 max) {
    float cmp = 0, cmpMin = 0, cmpMax = 0;
    if (depth % 2 == 0) {
        cmp = sub->p.x;
        cmpMin = min.x;
        cmpMax = max.x;
    } else {
        cmp = sub->p.y;
        cmpMin = min.y;
        cmpMax = max.y;
    }
    
    if ((cmp > cmpMin) && (cmp > cmpMax) && sub->right)
        _rangeSearch(depth+1, sub->right, min, max);
    else if ((cmp > cmpMin) && (cmp < cmpMax)) {
        if (sub->right)
            _rangeSearch(depth+1, sub->right, min, max);
        if (sub->left)
            _rangeSearch(depth+1, sub->left, min, max);
    } else if ((cmp < cmpMin) && (cmp < cmpMax) && sub->left)
        _rangeSearch(depth+1, sub->left, min, max);
    
    if (between(sub->p, min, max))
        inRange.push_back(sub->p);
}

vec2 tree::closest(const vec2 val) { //lesto
    minP = root.p;
    minDistance = distance(minP, val);
    _closest(0, &root, val);
    return minP;
}

void tree::_closest(int depth, nodo *sub, const vec2 val) { //lesto
    if ((equal(sub->p.x, val.x) && equal(sub->p.y, val.y))) {
        return;
    } else {
        float dis = distance(sub->p, val);
        if (minDistance > dis)
        {
            //cout<<"Distancia: "<<dis<<endl;
            minDistance = dis;
            minP.x = sub->p.x;
            minP.y = sub->p.y;
        }
        nodo* subtree = NULL;
        float cmp = 0, cmpVal = 0;
        if (depth % 2 == 0) {
            cmp = sub->p.x;
            cmpVal = val.x;
        } else {
            cmp = sub->p.y;
            cmpVal = val.y;
        }
        if (cmp > cmpVal)
            subtree = sub->right;
        else
            subtree = sub->left;
        if (subtree ==  NULL)
            return;
        _closest(depth+1, subtree, val);
    }
}

