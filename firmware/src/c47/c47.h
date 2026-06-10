/********************************************
 * \file c47.h
 * \brief Master include for the C47 library.
 *        Include this single header in every C47 source file.
 ***********************************************/

#pragma once

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
// #include <libgen.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
// #include <unistd.h>

// GMP

#include <gmp.h>

#include "defines.h"

#include "decContext.h"
#include "decNumber.h"
#include "decQuad.h"
#include "decimal128.h"

#include "mathematics/pcg_basic.h"

// prevent reordering on save:
#include "realType.h"
//
#include "typeDefinitions.h"
//
#include "longIntegerType.h"

extern pcg32_random_t pcg32_global;
extern uint8_t significantDigits;
extern uint8_t fractionDigits;

extern realContext_t ctxtReal4;  //   Limited digits: used for high speed internal calcs
extern realContext_t ctxtReal34; //   34 digits
extern realContext_t ctxtReal39; //   39 digits: used for 34 digits intermediate calculations
extern realContext_t ctxtReal51; //   51 digits: used for 34 digits intermediate calculations
extern realContext_t ctxtReal75; //   75 digits: used in SLVQ

extern char *errorMessage;

#include "_generated/constantPointers.h"
#include "comparisonReals.h"
#include "registerValueConversions.h"

/* ── C47 mathematics headers ─────────────────────────────────────────────── */
#include "mathematics/10pow.h"
#include "mathematics/exp.h"
#include "mathematics/wp34s.h"
