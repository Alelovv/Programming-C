#include <X11/Xlib.h>
void rasterCircle(int x0, int y0, int radius)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  XDrawPoint(dis,win,gc,x0, y0 + radius);
  XDrawPoint(dis,win,gc,x0, y0 - radius);
  XDrawPoint(dis,win,gc,x0 + radius, y0);
  XDrawPoint(dis,win,gc,x0 - radius, y0);
 
  while(x < y)
  {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    XDrawPoint(dis,win,gc,x0 + x, y0 + y);
    XDrawPoint(dis,win,gc,x0 - x, y0 + y);
    XDrawPoint(dis,win,gc,x0 + x, y0 - y);
    XDrawPoint(dis,win,gc,x0 - x, y0 - y);
    XDrawPoint(dis,win,gc,x0 + y, y0 + x);
    XDrawPoint(dis,win,gc,x0 - y, y0 + x);
    XDrawPoint(dis,win,gc,x0 + y, y0 - x);
    XDrawPoint(dis,win,gc,x0 - y, y0 - x);
  }
}

