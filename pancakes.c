//hi2
//pancakes
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
#define ValType double
#define IS_LESS(v1, v2)  (v1 < v2)



int compare (const void * a, const void * b)
{
  return ( *(double*)a - *(double*)b );
}

//void do_flip(int *list, int length, int num);

void do_flip(int *list, int length, int num)
{
  int swap;
  int i=0;
  for(i;i<--num;i++)
    {
      swap=list[i];
      list[i]=list[num];
      list[num]=swap;
    }
}

//void  quick_sort (int *a, int n, int *swap_count);

void quick_sort (double *a, int n) {
 
  if (n < 2)
    return;
  double p = a[n / 2];
  double *l = a;
  double *r = a + n - 1;
  while (l <= r) {
    while (*l < p)
      l++;
    while (*r > p)
      r--;
    if (l <= r) {
      double t = *l;
      *l++ = *r;
      *r-- = t;
    }
  }
  quick_sort(a, r - a + 1);
  quick_sort(l, a + n - l);
}

int pancake_sort(int *list, unsigned int length);

int pancake_sort(int *list, unsigned int length)
{
  //If it's less than 2 long, just return it as sorting isn't really needed...
  if(length<2)
    return 0;
 
  int i,a,max_num_pos,moves;
  moves=0;
 
  for(i=length;i>1;i--)
    {
      //Find position of the max number in pos(0) to pos(i)
      max_num_pos=0;
      for(a=0;a<i;a++)
        {
	  if(list[a]>list[max_num_pos])
	    max_num_pos=a;
          moves++;
        }
 
      if(max_num_pos==i-1)
	//It's where it need to be, skip
	continue;
 
 
      //Get the found max number to the beginning of the list (unless it already is)
      if(max_num_pos)
        {
	  moves++;
	  do_flip(list, length, max_num_pos+1);
        }
 
 
      //And then move it to the end of the range we're working with (pos(0) to pos(i))
      moves++;
      do_flip(list, length, i);
 
      //Then everything above list[i-1] is sorted and don't need to be touched
 
    }
 
  return moves;
}

void siftDown( ValType *a, int start, int count);
 
#define SWAP(r,s)  do{ValType t=r; r=s; s=t; } while(0)

void heapsort2( ValType *a, int count);

void heapsort2( ValType *a, int count)
{
  int start, end;
 
  /* heapify */
  for (start = (count-2)/2; start >=0; start--) {
    siftDown( a, start, count);
  }
 
  for (end=count-1; end > 0; end--) {
    SWAP(a[end],a[0]);
    siftDown(a, 0, end);
  }
}
 
void siftDown( ValType *a, int start, int end)
{
  int root = start;
 
  while ( root*2+1 < end ) {
    int child = 2*root + 1;
    if ((child + 1 < end) && IS_LESS(a[child],a[child+1])) {
      child += 1;
    }
    if (IS_LESS(a[root], a[child])) {
      SWAP( a[child], a[root] );
      root = child;
    }
    else
      return;
  }
}
void print_array(double *list, int n);

void print_array(double *list, int n)
{
  int i = 0;
  printf("Printing array: ");
  for ( i = 0; i < n; i++)
    {
      printf("%f ", list[i]);
    }
  printf("\n");

} 

int main(int argc, char **argv)
{
  //Just need some random numbers. I chose <100
  double  *list;
  double *list2;
  double *list3;
  int i;
  int x = atoi(argv[1]);
  srand((unsigned)time(NULL));
  /*for(i=0;i<900000;i++)
    {  list[i]=rand()%100;
     
    }*/
  list2 = (double *)malloc(x * sizeof(double));
  list3 = (double *)malloc(x * sizeof(double));
  list = (double *)malloc(x * sizeof(double));

 for (i=0;i<x;i++)
   list2[i]= 1000*(((double)rand()/(double)RAND_MAX));

  for (i=0;i<x;i++)
    list3[i]= list2[i];

  for (i=0;i<x;i++)
    list[i]= list2[i];

  //  printf("sample ints are %f %f %f",list2[2000],list2[20000],list2[200000]);
  //Print list, run code and print it again displaying number of moves
  // printf("\nOriginal: ");
  print_array(list, 100);
  time_t start,end;
  double diff;
 
  /*
  time (&start);
  int moves = pancake_sort(list, 170000);
  time (&end);

  diff = difftime (end,start);

  printf("\nSorted: ");
  //  print_array(list, 100000);
  printf(" Pancake Sort  - with a total of %d moves\n", moves);
  printf ("Pancake Sort takes  %f seconds \n", diff );
  */
  int swap_count = 0;
  int *sc;
  sc  = &swap_count;
  
  time (&start);
  quick_sort (list2,x);
  time (&end);  
  
  diff = difftime (end,start);

  printf("\nSorted: ");
  // print_array(list2, 100000);
  // printf(" Quick Sort  - with a total of %d moves\n", swap_count); 
  printf ("Quick Sort takes  %.2lf seconds \n", diff );


  time (&start);
  heapsort2(list3,x);
  time (&end);

  diff = difftime (end,start);

  printf("\nSorted: ");
  // print_array(list2, 100000);                                                                                           
  // printf(" Heap Sort  - with a total of %d moves\n", swap_count);
  printf ("Heap Sort takes  %.2lf seconds \n", diff );

 
  time (&start);
  qsort (list, x, sizeof(int), compare);
  time (&end);

  diff = difftime (end,start);

  printf("\nSorted: ");
  // print_array(list2, 100000);                                                                                          \
                                                                                                                           
  // printf(" Heap Sort  - with a total of %d moves\n", swap_count);                                                       
  printf ("System Quick Sort takes  %.2lf seconds \n", diff );



}
