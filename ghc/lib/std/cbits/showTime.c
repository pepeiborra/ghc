/* 
 * (c) The GRASP/AQUA Project, Glasgow University, 1994-1998
 *
 * $Id: showTime.c,v 1.4 1999/09/30 12:42:26 sof Exp $
 *
 * ClockTime.showsPrec Runtime Support
 */

#include "Rts.h"
#include "stgio.h"

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

StgAddr
showTime(I_ size, StgByteArray d, I_ maxsize, StgByteArray buf)
{
    time_t t;
    struct tm *tm;

    switch(size) {
	case 0:
	    t = 0;
	    break;
	case -1:
	    t = - (time_t) ((StgInt *)d)[0];
	    break;
	case 1:
	    t = (time_t) ((StgInt *)d)[0];
	    break;
	default:
	    return (-1);
	}
    tm = localtime(&t);
    if (tm != NULL && strftime(buf, maxsize, "%a %b %d %T %Z %Y", tm) > 0) {
       return 1;
    } else {
       return (-1);
    }
}
