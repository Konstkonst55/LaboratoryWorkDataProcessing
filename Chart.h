#pragma once

#ifndef CHART_H
#define CHART_H

#include "Point.h"
#include <vector>
#include <string>
#include "AxisType.h"

using namespace std;

void DrawChartWithPoints(vector<Point> points, const double xScale = 20, const double yScale = 20, const bool allowDataLabels = true, int labelsDensity = 2, const int color = 15, const int pattern = 0, const int thickness = 2);
void DrawAxis(AxisType aType, string xAxisLabel = "X", string yAxisLabel = "Y", double xStep = 100, double yStep = 100, const int axisMarkSize = 4, const bool allowArows = true, const bool allowMarks = true);
//void DrawChartWithFunction(double (*fun)(double), const double start = 0, const double end = 0, const double step = 0.2, const double scale = 100, const int color = 15);
void OutChartText(int x, int y, int color, char* text);

#endif // !CHART_H