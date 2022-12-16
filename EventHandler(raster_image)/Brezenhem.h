#pragma once

void Brezenhem(char** z, int x0, int y0, int x1, int y1, char ch)
{
    int A, B, sign;
    A = y1 - y0;
    B = x0 - x1;
    if (abs(A) > abs(B)) sign = 1;
    else sign = -1;
    int signa, signb;
    if (A < 0) signa = -1;
    else signa = 1;
    if (B < 0) signb = -1;
    else signb = 1;
    int f = 0;
    z[y0][x0] = ch;
    int x = x0, y = y0;
    if (sign == -1)
    {
        do {
            f += A * signa;
            if (abs(f) > abs(f - abs(B)))
            {
                f -= B * signb;
                y += signa;
            }
            x -= signb;
            z[y][x] = ch;
        } while (x != x1 || y != y1);
    }
    else
    {
        do {
            f += B * signb;
            if (abs(f) > abs(f - abs(A))) {
                f -= A * signa;
                x -= signb;
            }
            y += signa;
            z[y][x] = ch;
        } while (x != x1 || y != y1);
    }
}