
#include "TreeView.h"

#include "graphics.h"
#include <iostream>
#include <Windows.h>
#include <string>

#include <map>

void DrawCodeTree(Vertex* root, double scale, int offsetX, int offsetY) {
    cleardevice();

    int xStart = getmaxx() / 2 + offsetX;
    int yStart = 50 + offsetY;
    int xOffset = 200 * scale;

    std::function<void(Vertex*, std::string, int, int, int)> DrawRecursive =
        [&](Vertex* node, std::string currentCode, int x, int y, int xOffset) {
        if (!node) return;

        const int circleRadius = 10;
        setcolor(WHITE);

        circle(x, y, circleRadius);

        std::string nodeText;
        if (node->left == nullptr && node->right == nullptr) {
            nodeText = std::string(1, static_cast<char>(node->value));
        }
        else {
            nodeText = currentCode.empty() ? "/\\" : currentCode.substr(currentCode.size() - 1);
        }

        settextstyle(SMALL_FONT, HORIZ_DIR, 5);
        int textWidth = textwidth((char*)nodeText.c_str());
        outtextxy(x - textWidth / 2, y - circleRadius / 2, (char*)nodeText.c_str());

        if (node->left) {
            line(x, y + circleRadius, x - xOffset, y + 50 - circleRadius);
            DrawRecursive(node->left, currentCode + "0", x - xOffset, y + 50, xOffset / 2);
        }

        if (node->right) {
            line(x, y + circleRadius, x + xOffset, y + 50 - circleRadius);
            DrawRecursive(node->right, currentCode + "1", x + xOffset, y + 50, xOffset / 2);
        }
    };

    DrawRecursive(root, "", xStart, yStart, xOffset);
}

void DrawTree(Vertex* root, double scale, int offsetX, int offsetY) {
    cleardevice();

    int xStart = getmaxx() / 2 + offsetX;
    int yStart = 50 + offsetY;
    int xOffset = 200 * scale; 

    std::function<void(Vertex*, int, int, int)> DrawRecursive = [&](Vertex* node, int x, int y, int xOffset) {
        if (!node) return;

        const int circleRadius = 20;
        setcolor(WHITE);
        circle(x, y, circleRadius);

        settextstyle(SMALL_FONT, HORIZ_DIR, 5);
        int textWidth = textwidth((char*)(std::to_string(node->value)).c_str());
        outtextxy(x - textWidth / 2, y - textWidth / 2, (char*)(std::to_string(node->value) + ":" + std::to_string(node->weight)).c_str());

        if (node->left) {
            line(x, y + circleRadius, x - xOffset, y + 50 - circleRadius);
            DrawRecursive(node->left, x - xOffset, y + 50, xOffset / 2);  
        }

        if (node->right) {
            line(x, y + circleRadius, x + xOffset, y + 50 - circleRadius);
            DrawRecursive(node->right, x + xOffset, y + 50, xOffset / 2);  
        }
    };

    DrawRecursive(root, xStart, yStart, xOffset);
}