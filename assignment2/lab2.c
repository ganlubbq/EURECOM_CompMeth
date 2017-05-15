// Include files for SSE4
#include "emmintrin.h"
#include "xmmintrin.h"
#include "time_meas.h"
#include "smmintrin.h"
#include <immintrin.h>


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define ITER 1000000


void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z, uint16_t N);

#if defined(__SSE3__) || defined(__SSE4__)
void componentwise_multiply_real_sse4(int16_t *x, int16_t *y, int16_t *z, uint16_t N);
#endif

#if defined(__AVX2__) && defined(__AVX__)
void componentwise_multiply_real_avx2(int16_t *x, int16_t *y, int16_t *z, uint16_t N);
#endif


int test_routines(uint16_t N, int seed);

int main(int argc, char **argv) {

    test_routines(atoi(argv[1]), 1234);

    return 0;
}

void print128_num(__m128i var)
{
    int16_t *val = (int16_t*) &var;
    printf("%d %d %d %d %d %d %d %d \n",
           val[0], val[1], val[2], val[3], val[4], val[5],
           val[6], val[7]);
}


void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z, uint16_t N) {
    int i;
    for(i = 0; i < N; i+=8){
        z[i] = x[i] * y[i];
        z[i+1] = x[i+1] * y[i+1];
        z[i+2] = x[i+2] * y[i+2];
        z[i+3] = x[i+3] * y[i+3];
        z[i+4] = x[i+4] * y[i+4];
        z[i+5] = x[i+5] * y[i+5];
        z[i+6] = x[i+6] * y[i+6];
        z[i+7] = x[i+7] * y[i+7];
    }
}

#if defined(__SSE3__) || defined(__SSE4__)
void componentwise_multiply_real_sse4(int16_t *x, int16_t *y, int16_t *z, uint16_t N) {

    __m128i *x128 = (__m128i *)x;
    __m128i *y128 = (__m128i *)y;
    __m128i *z128 = (__m128i *)z;

    int i = 0;
    for(i = 0; i < (N>>3); i+=8){
        z128[i]   = _mm_mullo_epi16(x128[i],   y128[i]);
        z128[i+1] = _mm_mullo_epi16(x128[i+1], y128[i+1]);
        z128[i+2] = _mm_mullo_epi16(x128[i+2], y128[i+2]);
        z128[i+3] = _mm_mullo_epi16(x128[i+3], y128[i+3]);
        z128[i+4] = _mm_mullo_epi16(x128[i+4], y128[i+4]);
        z128[i+5] = _mm_mullo_epi16(x128[i+5], y128[i+5]);
        z128[i+6] = _mm_mullo_epi16(x128[i+6], y128[i+6]);
        z128[i+7] = _mm_mullo_epi16(x128[i+7], y128[i+7]);
    }
    z = (int16_t*)z128;
}
#endif

#if defined(__AVX2__) && defined(__AVX__)
void componentwise_multiply_real_avx2(int16_t *x, int16_t *y, int16_t *z, uint16_t N) {
    __m256i *x256 = (__m256i *)x;
    __m256i *y256 = (__m256i *)y;
    __m256i *z256 = (__m256i *)z;

    int i = 0;
    for(i = 0; i < (N>>4); i+=8){
        z256[i]   = _mm256_mullo_epi16(x256[i],   y256[i]);
        z256[i+1] = _mm256_mullo_epi16(x256[i+1], y256[i+1]);
        z256[i+2] = _mm256_mullo_epi16(x256[i+2], y256[i+2]);
        z256[i+3] = _mm256_mullo_epi16(x256[i+3], y256[i+3]);
        z256[i+4] = _mm256_mullo_epi16(x256[i+4], y256[i+4]);
        z256[i+5] = _mm256_mullo_epi16(x256[i+5], y256[i+5]);
        z256[i+6] = _mm256_mullo_epi16(x256[i+6], y256[i+6]);
        z256[i+7] = _mm256_mullo_epi16(x256[i+7], y256[i+7]);
    }
    z = (int16_t*)z256;
}
#endif

int test_routines(uint16_t N, int seed){

    srand(seed);
    time_stats_t time_stat;
    int16_t *x, *y, *z_scal, *z_sse4, *z_avx2;

    x = (int16_t*)malloc(sizeof(int16_t) * N);
    y = (int16_t*)malloc(sizeof(int16_t) * N);
    z_scal = (int16_t*)malloc(sizeof(int16_t) * N);
    z_sse4 = (int16_t*)malloc(sizeof(int16_t) * N);
    z_avx2 = (int16_t*)malloc(sizeof(int16_t) * N);

    if (x == NULL || y == NULL || z_scal == NULL || z_sse4 == NULL || z_avx2 == NULL)
        return -1;

    int i;
    for(i = 0; i < N; i++){
        x[i] = 1;
        y[i] = (int16_t)rand();
    }


    #ifdef __DEBUG__
    printf("Starting initial evaluation...\n");
    #endif

    componentwise_multiply_real_scalar(x, y, z_scal, N);

    #if defined(__SSE3__) || defined(__SSE4__)
    componentwise_multiply_real_sse4(x, y, z_sse4, N);
    #endif

    #if defined(__AVX2__) && defined(__AVX__)
    componentwise_multiply_real_avx2(x, y, z_avx2, N);
    #endif

    for(i = 0; i < N; i++){
        #if defined(__SSE3__) || defined(__SSE4__)
        if(z_scal[i] != z_sse4[i]) {
            #ifdef __DEBUG__
            printf("Inconsistent result in position %d\n Aborting!\n\n", i);
            #endif
            return -1;
        }
        #endif

        #if defined(__AVX2__) && defined(__AVX__)
        if(z_scal[i] != z_avx2[i]) {
            #ifdef __DEBUG__
            printf("Inconsistent result in position %d\n Aborting!\n\n", i);
            #endif
            return -1;
        }
        #endif
    }
    #ifdef __DEBUG__
    printf("Initial evaluation completed.\n");

    printf("\nStarting scalar implementation evaluation...\n");
    #endif

    reset_meas(&time_stat);
    for(i = 0; i < ITER; i++){
        start_meas(&time_stat);
        componentwise_multiply_real_scalar(x, y, z_scal, N);
        stop_meas(&time_stat);
    }
    #ifdef __DEBUG__
    printf("Diff..: %lld (ckt)\nMax...: %lld (ckt)\nTrials: %d (times)\nAvg...: %d\n",
            time_stat.diff, time_stat.max, time_stat.trials, (int)(time_stat.diff/time_stat.trials));
    #elif __PYTHON__
    printf("Scalar, %d, %lld, %lld, %d, %d\n",
            N, time_stat.diff, time_stat.max, time_stat.trials, (int)(time_stat.diff/time_stat.trials));
    #endif

    #if defined(__SSE3__) || defined(__SSE4__)
    #ifdef __DEBUG__
    printf("\nStarting SSE4 implementation evaluation...\n");
    #endif
    reset_meas(&time_stat);
    for(i = 0; i < ITER; i++){
        start_meas(&time_stat);
        componentwise_multiply_real_sse4(x, y, z_sse4, N);
        stop_meas(&time_stat);
    }
    #ifdef __DEBUG__
    printf("Diff..: %lld (ckt)\nMax...: %lld (ckt)\nTrials: %d (times)\nAvg...: %d\n",
            time_stat.diff, time_stat.max, time_stat.trials, (int)(time_stat.diff/time_stat.trials));
    #elif __PYTHON__
    printf("SSE4, %d, %lld, %lld, %d, %d\n",
            N, time_stat.diff, time_stat.max, time_stat.trials, (int)(time_stat.diff/time_stat.trials));
    #endif
    #endif

    #if defined(__AVX2__) && defined(__AVX__)
    #ifdef __DEBUG__
    printf("\nStarting AVX2 implementation evaluation...\n");
    #endif
    reset_meas(&time_stat);
    for(i = 0; i < ITER; i++){
        start_meas(&time_stat);
        componentwise_multiply_real_avx2(x, y, z_avx2, N);
        stop_meas(&time_stat);
    }
    #ifdef __DEBUG__
    printf("Diff..: %lld (ckt)\nMax...: %lld (ckt)\nTrials: %d (times)\nAvg...: %d\n",
            time_stat.diff, time_stat.max, time_stat.trials, (int)(time_stat.diff/time_stat.trials));
    #elif __PYTHON__
    printf("SSE4, %d, %lld, %lld, %d, %d\n",
            N, time_stat.diff, time_stat.max, time_stat.trials, (int)(time_stat.diff/time_stat.trials));
    #endif
    #endif
    return 0;
}
