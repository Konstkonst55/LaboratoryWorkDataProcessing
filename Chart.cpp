
#include "Chart.h"
#include "graphics.h"

void DrawChartWithPoints(vector<Point> points, const double xScale, const double yScale, const bool allowDataLabels, int labelsDensity, const int color, const int pattern, const int thickness)
{
	int mX = getmaxx() - 40, mY = getmaxy() - 40, i = 0, border = 10;

	setfillstyle(0, color);
    setcolor(color);
    setlinestyle(pattern, 0, thickness);
    settextstyle(SMALL_FONT, HORIZ_DIR, 4);

	for(i; i < points.size() - 1; i++)
	{
		line(points[i].x * xScale + border, mY - points[i].y * yScale + border, points[i + 1].x * xScale + border, mY - points[i + 1].y * yScale + border);
		fillellipse(points[i].x * xScale + border, mY - points[i].y * yScale + border, 2, 2);

        if (i % labelsDensity == 0 && allowDataLabels) outtextxy(points[i + 1].x * xScale + border * 2, mY - points[i + 1].y * yScale + border * 2, (char *)('[' + to_string(points[i + 1].x) + ';' + to_string(points[i + 1].y) + ']').c_str());
	}

	fillellipse(points[i].x * xScale + border, mY - points[i].y * yScale + border, 2, 2);
}

void DrawAxis(AxisType aType, string xAxisLabel, string yAxisLabel, double xStep, double yStep, const int axisMarkSize, const bool allowArows, const bool allowMarks) {
    int mX = getmaxx(), mY = getmaxy(), cX = mX / 2, cY = mY / 2;
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setlinestyle(SOLID_LINE, 0, 2);

    if (aType == CENTER_CENTER) {
        line(cX, 0, cX, mY); // ��� Y
        line(0, cY, mX, cY); // ��� X

        if (allowArows) {
            line(mX - 10, cY, mX - 15, cY - 5); // ��������� ��� ��� �
            line(mX - 10, cY, mX - 15, cY + 5); // ������ ����� ���������

            line(cX, 0, cX - 5, 5); // ��������� ��� ��� �
            line(cX, 0, cX + 5, 5); // ������ ����� ���������
        }

        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

        if (allowMarks) {
            for (int i = xStep; i <= cX; i += xStep) {
                line(cX + i, cY - axisMarkSize, cX + i, cY + axisMarkSize); // �������� ��� �
                line(cX - i, cY - axisMarkSize, cX - i, cY + axisMarkSize); // �������� ��� x
            }

            for (int i = yStep; i <= cX; i += yStep) {
                line(cX - axisMarkSize, cY + i, cX + axisMarkSize, cY + i); // �������� ��� �
                line(cX - axisMarkSize, cY - i, cX + axisMarkSize, cY - i); // �������� ��� �
            }
        }

        outtextxy(mX - 30, cY + 10, (char *)xAxisLabel.c_str()); // ������� ��� �
        outtextxy(cX + 10, 10, (char *)yAxisLabel.c_str()); // ������� ��� �
    }
    else if (aType == BOTTOM_LEFT) {
        int xEnd = mX - 20, yStart = mY - 20, border = 10, yEnd = border, xStart = border;

        line(border, border, border, yStart); // ��� Y
        line(border, yStart, xEnd, yStart); // ��� X

        if (allowArows) {
            line(xEnd, yStart, xEnd - 5, yStart - 5); // ��������� ��� ��� �
            line(xEnd, yStart, xEnd - 5, yStart + 5); // ������ ����� ���������

            line(border, border, border + 5, border + 5); // ��������� ��� ��� �
            line(border, border, border - 5, border + 5); // ������ ����� ���������
        }

        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

        if (allowMarks) {
            for (double i = xStep; i <= xEnd; i += xStep) {
                line(border + i, yStart - axisMarkSize, border + i, yStart + axisMarkSize); // �������� ��� �
            }

            if (yStep < mY / 200) yStep *= 100;

            for (double i = yStart - yStep; i >= yEnd; i -= yStep) {
                line(border - axisMarkSize, i, border + axisMarkSize, i); // �������� ��� �
            }
        }

        outtextxy(xEnd - 20, yStart - 30, (char*)xAxisLabel.c_str()); // ������� ��� �
        outtextxy(border + 15, border, (char*)yAxisLabel.c_str()); // ������� ��� �
    }
}


void OutChartText(int x, int y, int color, char* text) {
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(color);
    outtextxy(x, y, text);
}