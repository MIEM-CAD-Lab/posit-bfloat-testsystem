#pragma once
#include "test.h"
#include "test_set.h"
#include "test_data.h"

FloatDataGenerator generator;

/*

Пример подключения типов

#include <posit/posit>
#include <float/float.h>

using bfloat16 = format::float_type::Float<7, 8>;
using Float32 = format::float_type::Float<23, 8>;
using Posit16 = format::posit_type::Posit16;
using Posit32 = format::posit_type::Posit32;
*/