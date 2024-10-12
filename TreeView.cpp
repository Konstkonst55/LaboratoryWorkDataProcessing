
#include "TreeView.h"

#include "graphics.h"
#include <iostream>
#include <Windows.h>
#include <string>

#include <map>

void Draw(Vertex* node, int x, int y, int xOffset, double scale) {
    if (node == nullptr) return;

    const int circleRadius = 12;
    setcolor(WHITE);
    circle(x, y, circleRadius);

    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    int textWidth = textwidth((char*)(std::to_string(node->value)).c_str());

    outtextxy(x - textWidth / 2, y - textWidth / 2, (char*)(std::to_string(node->value) + ":" + std::to_string(node->balance)).c_str());

    if (node->left) {
        line(x, y + circleRadius, x - xOffset, y + 50 - circleRadius);
        Draw(node->left, x - xOffset, y + 50, xOffset / 2, scale);
    }

    if (node->right) {
        line(x, y + circleRadius, x + xOffset, y + 50 - circleRadius);
        Draw(node->right, x + xOffset, y + 50, xOffset / 2, scale);
    }
}

void DrawTree(Vertex* node, double scale, int offsetX, int offsetY) {
    cleardevice();

    int xStart = getmaxx() / 2 + offsetX;
    int yStart = 50 + offsetY;
    int xOffset = 200 * scale;

    Draw(node, xStart, yStart, xOffset, scale);
}