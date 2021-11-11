#include<GL/glut.h>


void Intersection(float x1,float y1,float x2,float y2,int *LE,int *RE)
{
    float x,M;
    int t,y;
    
    // Swapping to ensure we start at the lower ordinate
    if(y1>y2)
    {
        t = x1;
        x1 = x2;
        x2 = t;

        t = y1;
        y1 = y2;
        y2 = t;
    }

    // Avoiding division by zero
    if((y2-y1)==0)
        M = (x2-x1);
    else
        M = (x2-x1)/(y2-y1);

    // Saves compute as we know that the scan line will intersect x first as it has the lower ordinate
    x = x1;

    for(y=y1; y<=y2; y++)
    {
        // Check if point is inside the window
        if(x<(float)LE[y])
            LE[y]=(int)x;
        if(x>(float)RE[y])
            RE[y]=(int)x;

        // Go to next scanline
        x = x + M;
    }
}


void Draw()
{
    int x,y,i;
    int LE[500],RE[500]; // Scanline coordinates

    // Irregular quadrilateral
    // GLint P1[2] = {90, 300}, \
    //     P2[2] = {420, 270}, \
    //     P3[2] = {380, 10}, \
    //     P4[2] = {50, 100};

    // Regular Pentagon
    // GLint P1[2] = {440, 188}, \
    //     P2[2] = {368, 412}, \
    //     P3[2] = {132, 412}, \
    //     P4[2] = {60, 188}, \
    //     P5[2] = {250, 50};

    // Regular Decagon
    GLint P1[2] = {312, 60}, \
        P2[2] = {188, 60}, \
        P3[2] = {88, 132}, \
        P4[2] = {50, 250}, \
        P5[2] = {88, 368}, \
        P6[2] = {188, 440}, \
        P7[2] = {312, 440}, \
        P8[2] = {412, 368}, \
        P9[2] = {450, 250}, \
        P10[2] = {412, 132};


    glClear(GL_COLOR_BUFFER_BIT);

    for(i=0;i<500;i++)
    {
        LE[i] = 500;
        RE[i] = 0;
    }

    // Draw the Edges
    glColor3f(1.0,0.0,0.0); // Red
    glBegin(GL_LINE_LOOP);
    glVertex2iv(P1);
    glVertex2iv(P2);
    glVertex2iv(P3);
    glVertex2iv(P4);
    glVertex2iv(P5);
    glVertex2iv(P6);
    glVertex2iv(P7);
    glVertex2iv(P8);
    glVertex2iv(P9);
    glVertex2iv(P10);
    glEnd();


    // Compute the intersections of all the edges
    Intersection(P1[0],P1[1],P2[0],P2[1],LE,RE);
    Intersection(P2[0],P2[1],P3[0],P3[1],LE,RE);
    Intersection(P3[0],P3[1],P4[0],P4[1],LE,RE);
    Intersection(P4[0],P4[1],P5[0],P5[1],LE,RE);
    Intersection(P5[0],P5[1],P6[0],P6[1],LE,RE);
    Intersection(P6[0],P6[1],P7[0],P7[1],LE,RE);
    Intersection(P7[0],P7[1],P8[0],P8[1],LE,RE);
    Intersection(P8[0],P8[1],P9[0],P9[1],LE,RE);
    Intersection(P9[0],P9[1],P10[0],P10[1],LE,RE);
    Intersection(P10[0],P10[1],P1[0],P1[1],LE,RE);


    // Draw the Fill
    for(y=0;y<500;y++)
    {
        // Iterates through the saved points and draws a point at each coordinate
        for(x=LE[y];x<RE[y];x++)
        // The for loop draws points BETWEEN a ranged set of coordinates, 
        // these coordinates are the intersection points of the scanline to the specified edge.
        {
            glColor3f(1.0,1.0,0.0); // Yellow
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            glFlush(); // To animate the points
        }
    }
    glFlush();
}


void MyInit()
{
    glMatrixMode(GL_PROJECTION); // ProjectionView is the matrix that represents your camera's lens (aperture, far-field, near-field, etc)
    glLoadIdentity();
    gluOrtho2D(0,500,0,500); // The gluOrtho2D function sets up a two-dimensional orthographic viewing region.
    glMatrixMode(GL_MODELVIEW); // ModelView is the matrix that represents your camera (position, pointing, and up vector).
}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Shows RGB Colours and single buffering
    glutCreateWindow("Polygon Fill using Scan Line Algorithm");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
