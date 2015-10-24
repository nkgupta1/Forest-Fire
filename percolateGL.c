// 
// Torbert, 30 October 2013
// 
// gcc -lGLU -lglut glshell.c
// 
#include <stdio.h>
#include <GL/glut.h>
// 
#define N 600 
// 
int count =  0 ; 
int ascii = 48 ;
char t[N][N];
double prob = .6;
//
double r()
{
	return ( 1.0 * rand() ) / RAND_MAX ;
}
int inBounds(int i, int j)
{
	if (0<= i && i < N && 0 <= j && j < N) return 1;
	return 0;
}
int burnStep(void)
{
   int i,j;
   int count = 0;
   for( i = 0; i < N; i++)
   {
      for( j = 0; j < N; j++)
      {
         if(t[i][j] == 2)
         {
      // printf("%d, %d\n", i, j);
            if(inBounds(i-1,j) && t[i-1][j] == 1)
               t[i-1][j] = 3;    //intermediate
            if(inBounds(i+1,j) && t[i+1][j] == 1){
               t[i+1][j] = 3;
            }
            if(inBounds(i,j-1) && t[i][j-1] == 1)
               t[i][j-1] = 3;
            if(inBounds(i,j+1) && t[i][j+1] == 1){
               t[i][j+1] = 3;
            }
            t[i][j] = 0;
         }
      }
   }

   for( i = 0; i < N; i++)
   {
      for( j = 0; j < N; j++)
      {
         if(t[i][j] == 3)
         {
            count++;
            t[i][j] = 2;
         }
      }

   }
   return count;
}
void defineForest(void)
{
	int j,k;
	srand(1234);
	for(j=0;j<N;j++)
		for(k=0;k<N;k++)
		{
			if (1.0*r() < prob) t[j][k] = 1;
			else t[j][k] = 0;
		}
     for(j=0;j<N;j++)
       if(t[j][0] == 1) t[j][0] = 2;
 }
 void idlefunc(void)
 {
   if(burnStep())
      glutPostRedisplay() ;
   else
   {
    defineForest();
   }
}
//
void displayfunc(void)
{
   int x , y ;
   //
   glClear(GL_COLOR_BUFFER_BIT);
   //
   for(x = 0; x < N; x++)
      for(y = 0; y < N; y++)
      {
         glBegin(GL_POINTS);
         glColor3f(0,0,0);
         if(t[x][y] == 0) glVertex2f(x,y);
         glColor3f(0,1.0,0);
         if(t[x][y] == 1) glVertex2f(x,y);
         glColor3f(1.0,0,0);
         if(t[x][y] == 2) glVertex2f(x,y);
         glEnd();
      }
   //
      glutSwapBuffers() ;
   }
   void reshapefunc(int wscr,int hscr)
   {
      glViewport(0,0,(GLsizei)N,(GLsizei)N);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0,1.0*N,0.0,1.0*N);
      glMatrixMode(GL_MODELVIEW);
   }
   void mousefunc(int button,int state,int xscr,int yscr)
   {
      if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
      {
         printf("Left mouse clicked.\n");
      }
      else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
      {
         printf("Right mouse clicked.\n");
      }
   }
   void motionfunc(int xscr,int yscr)
   {
      printf("Motion ( %d , %d ).\n" , xscr , yscr ) ;
   }
   void keyfunc(unsigned char key,int xscr,int yscr)
   {
      printf("Key %c pressed.\n" , key);
   }
   void specialfunc(int key,int xscr,int yscr)
   {
      if( key == GLUT_KEY_UP )
      {
         printf("Up arrow pressed.\n");
      }
   }
   void closefunc(void)
   {
      printf("Window closed.\n");
   }
   int main(int argc,char* argv[])
   {  
      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(N,N);
      glutInitWindowPosition(100,50);
      glutCreateWindow("");
      glClearColor(1.0,1.0,1.0,0.0);
      glShadeModel(GL_SMOOTH);
   //
   //define forest
      defineForest();
      glutIdleFunc(idlefunc);
      glutDisplayFunc(displayfunc);
      glutReshapeFunc(reshapefunc);
   // glutMouseFunc(mousefunc);
   // glutMotionFunc(motionfunc);
   // glutKeyboardFunc(keyfunc);
   // glutSpecialFunc(specialfunc);
      glutWMCloseFunc(closefunc);
   //
      glutMainLoop();
   //
      return 0;
   }
// 
// end of file
// 
