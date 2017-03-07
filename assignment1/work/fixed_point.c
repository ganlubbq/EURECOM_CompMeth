//Q15 multiply
// x and y are 16-bit integers (Q15)
#define FIX_MPY(x,y)  ((short)(((int)x * (int)y)>>15))


//25-bit by 18-bit multiply, with output scaled to 25-bits, Q24xQ17
// x is 25-bits stored as 32, y is 18-bits stored as 32
int FIX_MPY25by18(int x,int y) {

  return ((int)(((long long)x * (long long)y)>>17));
}

//Saturated addition for Q15
short SAT_ADD16(short x,short y) {

  if ((int)x + (int)y > 32767)
    return(32767);
  else if ((int)x + (int)y < -32767)
    return(-32768);
  else
    return(x+y);
}

//Saturated addition for Q24
int SAT_ADD25(int x,int y) {

  if ((int)x + (int)y > (1<<24)-1)
    return((1<<24)-1);
  else if ((int)x + (int)y < -(1<<24))
    return(-(1<<24));
  else
    return(x+y);
}
