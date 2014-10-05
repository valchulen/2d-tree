//
//  vec2.cpp
//  2D-tree
//
//  Created by Valentin Paz Marcolla on 30/09/14.
//  Copyright (c) 2014 Valentin Paz Marcolla. All rights reserved.
//

#include "vec2.h"
#include <algorithm>

using namespace std;

bool between (vec2 val, vec2 min, vec2 max)
{
    return (max.x >= val.x) && (max.y >= val.y) && (min.x <= val.x) && (min.y <= val.y);
}

bool compareX(vec2 a, vec2 b) {
    return a.x < b.x;
}

bool compareY(vec2 a, vec2 b) {
    return a.y < b.y;
}

void sortByX(vec2 * arr, int size) {
    sort(arr, arr+size, compareX);
}

void sortByY(vec2 * arr, int size) {
    sort(arr, arr+size, compareY);
}