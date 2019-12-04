//------------------------------------------------------------------------------
// GB_unaryop:  hard-coded functions for each built-in unary operator
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2019, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// If this file is in the Generated/ folder, do not edit it (auto-generated).

#include "GB.h"
#ifndef GBCOMPACT
#include "GB_control.h"
#include "GB_iterator.h"
#include "GB_unaryop__include.h"

// C=unop(A) is defined by the following types and operators:

// op(A)  function:  GB_unop__identity_fp32_fp64
// op(A') function:  GB_tran__identity_fp32_fp64

// C type:   float
// A type:   double
// cast:     float cij = (float) aij
// unaryop:  cij = aij

#define GB_ATYPE \
    double

#define GB_CTYPE \
    float

// aij = Ax [pA]
#define GB_GETA(aij,Ax,pA)  \
    double aij = Ax [pA]

#define GB_CX(p) Cx [p]

// unary operator
#define GB_OP(z, x)   \
    z = x ;

// casting
#define GB_CASTING(z, x)   \
    float z = (float) x ;

// cij = op (cast (aij))
#define GB_CAST_OP(pC,pA)           \
{                                   \
    /* aij = Ax [pA] */             \
    GB_GETA (aij, Ax, pA) ;         \
    /* Cx [pC] = op (cast (aij)) */ \
    GB_CASTING (x, aij) ;           \
    GB_OP (GB_CX (pC), x) ;         \
}

// disable this operator and use the generic case if these conditions hold
#define GB_DISABLE \
    (GxB_NO_IDENTITY || GxB_NO_FP32 || GxB_NO_FP64)

//------------------------------------------------------------------------------
// Cx = op (cast (Ax)): apply a unary operator
//------------------------------------------------------------------------------

GrB_Info GB_unop__identity_fp32_fp64
(
    float *GB_RESTRICT Cx,
    const double *GB_RESTRICT Ax,
    int64_t anz,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int64_t p ;
    #pragma omp parallel for num_threads(nthreads) schedule(static)
    for (p = 0 ; p < anz ; p++)
    {
        GB_CAST_OP (p, p) ;
    }
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// C = op (cast (A')): transpose, typecast, and apply a unary operator
//------------------------------------------------------------------------------

GrB_Info GB_tran__identity_fp32_fp64
(
    GrB_Matrix C,
    const GrB_Matrix A,
    int64_t *GB_RESTRICT *Rowcounts,
    GBI_single_iterator Iter,
    const int64_t *GB_RESTRICT A_slice,
    int naslice
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #define GB_PHASE_2_OF_2
    #include "GB_unaryop_transpose.c"
    return (GrB_SUCCESS) ;
    #endif
}

#endif

