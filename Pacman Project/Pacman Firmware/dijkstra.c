#define INT_MAX 50000

#define sgn(x) ((x<0)?-1:((x>0)?1:0))
void line_fast(int x1, int y1, int x2, int y2)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

 //VGA[(py<<8)+(py<<6)+px]=color;

  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      setpix(px,py);
    }
  }
  else /* the line is more vertical than horizontal */
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      setpix(px,py);
    }
  }
}

// Number of vertices 
// in the graph 
#define NoV 399
int vertexNo[NoV]; 

// A utility function to find the 
// vertex with minimum distance 
// value, from the set of vertices 
// not yet included in shortest 
// path tree 
int minDistance(int dist[], 
				int sptSet[]) 
{ 
	
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (int v = 0; v <NoV; v++) 
		if (sptSet[v] == 0 && 
				dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 

// Function to print shortest 
// path from source to j 
// using parent array 
int soln[NoV];
int solnlen;
int graph[NoV][NoV];

void printPath(int parent[], int j) 
{ 
	
	// Base Case : If j is source 
	if (!parent[j]||parent[j] == -1 || j ==parent[parent[j]]) 
		return; 
uprintf("parent[%d] = %d solnlen =%d\n",j,parent[j],solnlen);
	printPath(parent, parent[j]); 

	uprintf("set soln %d ", j);
        soln[solnlen++]=j; 
} 

// A utility function to print 
// the constructed distance 
// array 
/*int printSolution(int dist[], int n, 
					int parent[]) 
{ 
	int src = 0; 
	printf("Vertex\t Distance\tPath");
        int i=5; 
	//for (int i = 1; i <NoV; i++) 
	{ 
		printf("\n%d -> %d \t\t %d\t\t%d ", 
					src, i, dist[i], src); 
		printPath(parent, i); 
	} 
} 
*/
// Funtion that implements Dijkstra's 
// single source shortest path 
// algorithm for a graph represented 
// using adjacency matrix representation 
// The output array. dist[i] 
	// will hold the shortest 
	// distance from src to i 
	int dist[NoV]; 

	// sptSet[i] will true if vertex 
	// i is included / in shortest 
	// path tree or shortest distance 
	// from src to i is finalized 
	int sptSet[NoV]; 

	// Parent array to store 
	// shortest path tree 
	int parent[NoV]; 
void dijkstra(int graph[NoV][NoV], int src,int dest) 
{ 
	
	
	solnlen =0;
	// Initialize all distances as 
	// INFINITE and stpSet[] as false 
	for (int i = 0; i <NoV; i++) 
	{ 
		parent[0] = -1; 
		dist[i] = INT_MAX; 
		sptSet[i] = 0; 
	} 
//uprintf("here1\n");
	// Distance of source vertex 
	// from itself is always 0 
	dist[src] = 0; 

	// Find shortest path 
	// for all vertices 
	for (int count = 0; count <NoV - 1; count++) 
	{ 
		// Pick the minimum distance 
		// vertex from the set of 
		// vertices not yet processed. 
		// u is always equal to src 
		// in first iteration. 
		int u = minDistance(dist, sptSet); 
//uprintf("here2 count %d\n",count);
		// Mark the picked vertex 
		// as processed 
		sptSet[u] = 1; 
//uprintf("here3  \n");
		// Update dist value of the 
		// adjacent vertices of the 
		// picked vertex. 
		for (int v = 0; v <NoV; v++) 

			// Update dist[v] only if is 
			// not in sptSet, there is 
			// an edge from u to v, and 
			// total weight of path from 
			// src to v through u is smaller 
			// than current value of 
			// dist[v] 
			if (!sptSet[v] && graph[u][v] && 
				dist[u] + graph[u][v] < dist[v]) 
			{ 
				parent[v] = u; 
				dist[v] = dist[u] + graph[u][v]; 
			} 
	} 

	// print the constructed 
	// distance array 
	//printSolution(dist,NoV, parent);
//uprintf("here4  \n");
        printPath(parent, dest); 
        for (int i=0;i<solnlen;i++)
            uprintf("soln[%d] = %d ",i,soln[i]);
                
}
int mapIJtoVertex(i,j){
return j*Width+i;
}

