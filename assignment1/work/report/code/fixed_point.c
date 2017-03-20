short FIX_MPY(short x, short y){
  return ((short)(((int)x * (int)y)>>15));
}

short SAT_ADD16(short x,short y) {

  if ((int)x + (int)y > 32767)
    return(32767);
  else if ((int)x + (int)y < -32767)
    return(-32768);
  else
    return(x+y);
}

int FIX_MPY25by18(int x,int y) {

  return ((int)(((long long)x * (long long)y) >> 17));
}

int SAT_ADD25(int x,int y) {

  if ((int)x + (int)y > (1<<24)-1)
    return((1<<24)-1);
  else if ((int)x + (int)y < -(1<<24))
    return(-(1<<24));
  else
    return(x+y);
}
