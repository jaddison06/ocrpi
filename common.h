#pragma once

#ifdef OCRPI_BACKTRACE

// can't backtrace static functions!!!!!!
#define STATIC
#define INLINE

#else

#define STATIC static
#define INLINE inline

#endif