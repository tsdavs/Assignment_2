/**
 *	Angle related functions and constants
 */
#include <cmath>

#define ANG_2_DEGREES(x)    static_cast<float>((x*(180.0f/M_PI)))
#define ANG_2_RAD(x)        static_cast<float>((x*(M_PI/180.0f)))

#define SIN(x) sinf(x)
#define COS(x) cosf(x)
#define TAN(x) tanf(x)

#define SIN_D(x) ANG_2_DEGREES(sinf(x))
#define COS_D(x) ANG_2_DEGREES(cosf(x))
#define TAN_D(x) ANG_2_DEGREES(tanf(x))

#define ARSIN(x) asinf(x)
#define ARCOS(x) acosf(x) 
#define ARTAN(x) atanf(x)

#define ARSIN_D(x) ANG_2_DEGREES(asinf(x))
#define ARCOS_D(x) ANG_2_DEGREES(acosf(x)) 
#define ARTAN_D(x) ANG_2_DEGREES(atanf(x))
