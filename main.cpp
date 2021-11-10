#include<GL/glu.h>
#include<GL/glut.h>

// Scanline coordinates
int LE[500], RE[500];

void Intersection(GLint x1,GLint y1,GLint x2,GLint y2)
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
        if(x<LE[y])
            LE[y]=x;
        if(x>RE[y])
            RE[y]=x;

        // Go to next scanline
        x = x + M;
    }
}



void Draw()
{
    int x,y,i;
    GLint P1[2] = {391,109}, \
        P2[2] = {109,109}, \
        P3[2] = {109,391}, \
        P4[2] = {391,391};

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
    glEnd();


    // Compute the intersections of all 4 edges
    Intersection(P1[0],P1[1],P2[0],P2[1]);
    Intersection(P2[0],P2[1],P3[0],P3[1]);
    Intersection(P3[0],P3[1],P4[0],P4[1]);
    Intersection(P4[0],P4[1],P1[0],P1[1]);


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
