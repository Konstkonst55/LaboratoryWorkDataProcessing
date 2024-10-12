#pragma once

#ifndef TREE_VIEW
#define TREE_VIEW

#include "TreeUtils.h"

void Draw(Vertex* node, int x, int y, int xOffset, double scale);
void DrawTree(Vertex* node, double scale, int offsetX, int offsetY);

#endif // !TREE_VIEW