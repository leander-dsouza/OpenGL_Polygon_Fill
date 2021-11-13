#include<GL/glut.h>

// Polygonal declaration

// Irregular Quadrilateral
// const int num_of_sides = 4;
// int coords[num_of_sides][2] = { \
//                                 {90, 300}, \
//                                 {420, 270}, \
//                                 {380, 10}, \
//                                 {50, 100}, \
//                             };


// Regular Pentagon
// const int num_of_sides = 5;
// int coords[num_of_sides][2] = { \
//                                 {440, 188}, \
//                                 {368, 412}, \
//                                 {132, 412}, \
//                                 {60, 188}, \
//                                 {250, 50}, \
//                             };

// Regular Decagon
const int num_of_sides = 10;
int coords[num_of_sides][2] = { \
                                {312, 60}, \
                                {188, 60}, \
                                {88, 132}, \
                                {50, 250}, \
                                {88, 368}, \
                                {188, 440}, \
                                {312, 440}, \
                                {412, 368}, \
                                {450, 250}, \
                                {412, 132}, \
                            };


// Concave Pentagon - FAIL CASE
// const int num_of_sides = 5;
// int coords[num_of_sides][2] = { \
//                                 {300, 60}, \
//                                 {100, 60}, \
//                                 {50, 300}, \
//                                 {200, 190}, \
//                                 {400, 300}, \
//                             };



void Intersection(float x1,float y1,float x2,float y2,int *LE,int *RE)
{
    float x,M;
    int t,y,flag = 0;
    
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
    int x,y,i,flag=0;
    int LE[500],RE[500]; // Scanline coordinates

    glClear(GL_COLOR_BUFFER_BIT);

    for(i=0;i<500;i++)
    {
        LE[i] = 500;
        RE[i] = 0;
    }

    // Draw the Edges
    glColor3f(1.0,0.0,0.0); // Red
    glBegin(GL_LINE_LOOP);

    for (int i=0; i<num_of_sides; i++)
    {
        glVertex2iv(coords[i]);
    }
    glEnd();

    for (int i=0; i<num_of_sides; i++)
    {
        // Compute the intersections of all the edges
        // modulus to ensure roundtheabout pairs are taken
        Intersection(coords[i][0],coords[i][1],\
            coords[(i+1)%num_of_sides][0],coords[(i+1)%num_of_sides][1],LE,RE); 
    }


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
