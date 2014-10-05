//
//  vec2.h
//  2D-tree
//
//  Created by Valentin Paz Marcolla on 30/09/14.
//  Copyright (c) 2014 Valentin Paz Marcolla. All rights reserved.
//

#ifndef ___D_tree__vec2__
#define ___D_tree__vec2__

typedef struct {
    float x, y;
} vec2;

bool between(vec2 val, vec2 min, vec2 max);

bool compareX( vec2 a, vec2 b);

bool compareY( vec2 a, vec2 b);

void sortByX(vec2 * arr, int size);

void sortByY(vec2 * arr, int size);

#endif /* defined(___D_tree__vec2__) */
