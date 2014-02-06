#ifndef _CONSTANT_H_
#define _CONSTANT_H_
namespace lily{
/*const float */#define FLOAT_MAX        3.402823466e+38f          //;/* max value */
/*const float */#define FLOAT_MIN        1.175494351e-38f          //;/* min positive value */
/*const float */#define FLOAT_EPSILON    1.192092896e-07f          //;/* smallest such that 1.0+FLT_EPSILON != 1.0 */
/*const double*/#define DOUBLE_MAX       1.7976931348623158e+308   //;/* max value */
/*const double*/#define DOUBLE_MIN       2.2250738585072014e-308   //;/* min positive value */
/*const double*/#define DOUBLE_EPSILON   2.2204460492503131e-016   //;/* smallest such that 1.0+DBL_EPSILON != 1.0 */
/*const float */#define PI               3.1415926f                //;
                #define INVPI			 0.318310
                #define INV2PI			 0.159154
/*const float */#define DEGREE_TO_RADIAN 0.017453f                 //;
                #define SQRT_3			 1.7320508f
                #define DEG2RAD			 0.017453294f
                #define INT_MAX_POSITIVE 0x7FFFFFFF
                #define INT_MAX_NEGATIVE -0x7FFFFFFF
                #define UINT_MAX_POSITVE 0xFFFFFFFF
}
#endif