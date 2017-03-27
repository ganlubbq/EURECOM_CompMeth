short FIX_MPY(short x, short y){
  return ((short)(((int)x * (int)y)>>15));
}

short SAT_ADD16(short x,short y) {
  if ((int)x + (int)y > 32767)
    return(32767);
  else if ((int)x + (int)y < -32767)
    return(-32768);
  else
    return(x + y);
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
    return(x + y);
}


bfly[0].r = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].r, +x[N2+n2].r), +x[2*N2+n2].r), x[3*N2+n2].r);
bfly[0].i = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].i, +x[N2+n2].i), +x[2*N2+n2].i), x[3*N2+n2].i);

bfly[1].r = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].r, +x[N2+n2].i), -x[2*N2+n2].r), -x[3*N2+n2].i);
bfly[1].i = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].i, -x[N2+n2].r), -x[2*N2+n2].i), +x[3*N2+n2].r);

bfly[2].r = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].r, -x[N2+n2].r), +x[2*N2+n2].r), -x[3*N2+n2].r);
bfly[2].i = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].i, -x[N2+n2].i), +x[2*N2+n2].i), -x[3*N2+n2].i);

bfly[3].r = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].r, -x[N2+n2].i), -x[2*N2+n2].r), +x[3*N2+n2].i);
bfly[3].i = SAT_ADD16(SAT_ADD16(SAT_ADD16(x[n2].i, +x[N2+n2].r), -x[2*N2+n2].i), -x[3*N2+n2].r);

for (k1 = 0; k1 < N1; k1++) {
    twiddle_fixed(&W, N, (double)k1*(double)n2);
    x[n2 + N2*k1].r = SAT_ADD16(FIX_MPY(bfly[k1].r, W.r), -FIX_MPY(bfly[k1].i, W.i));
    x[n2 + N2*k1].i = SAT_ADD16(FIX_MPY(bfly[k1].i, W.r), +FIX_MPY(bfly[k1].r, W.i));
}


bfly[0].r = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].r, +x[N2+n2].r), +x[2*N2+n2].r), x[3*N2+n2].r);
bfly[0].i = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].i, +x[N2+n2].i), +x[2*N2+n2].i), x[3*N2+n2].i);

bfly[1].r = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].r, +x[N2+n2].i), -x[2*N2+n2].r), -x[3*N2+n2].i);
bfly[1].i = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].i, -x[N2+n2].r), -x[2*N2+n2].i), +x[3*N2+n2].r);

bfly[2].r = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].r, -x[N2+n2].r), +x[2*N2+n2].r), -x[3*N2+n2].r);
bfly[2].i = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].i, -x[N2+n2].i), +x[2*N2+n2].i), -x[3*N2+n2].i);

bfly[3].r = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].r, -x[N2+n2].i), -x[2*N2+n2].r), +x[3*N2+n2].i);
bfly[3].i = SAT_ADD25(SAT_ADD25(SAT_ADD25(x[n2].i, +x[N2+n2].r), -x[2*N2+n2].i), -x[3*N2+n2].r);

for (k1 = 0; k1 < N1; k1++) {
    twiddle_fixed_Q17(&W, N, (double)k1*(double)n2);
    x[n2 + N2*k1].r = SAT_ADD25(FIX_MPY25by18(bfly[k1].r, W.r), -FIX_MPY25by18(bfly[k1].i, W.i));
    x[n2 + N2*k1].i = SAT_ADD25(FIX_MPY25by18(bfly[k1].i, W.r), +FIX_MPY25by18(bfly[k1].r, W.i));
}

mean_error = 0.0;
mean_in = 0.0;

for (i=0;i<N;i++) {
  mean_in += data[i].r*data[i].r + data[i].i*data[i].i;
  mean_error += pow(data[i].r-(double)data32[i].r/32767.0,2) + pow(data[i].i-(double)data32[i].i/32767.0,2);
}

SNR = 10*log10(mean_in/mean_error);
