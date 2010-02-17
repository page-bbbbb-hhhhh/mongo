/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2008 WiredTiger Software.
 *	All rights reserved.
 *
 * $Id$
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* Debug byte value */
#define	WT_DEBUG_BYTE	0xab

/*
 * Our private free function clears the underlying address atomically so there's
 * no chance of racing threads looking an intermediate results while a structure
 * is being free'd.   That's a non-standard "free" API, and the resulting bug is
 * a mother to find -- make sure we get it right, don't make the caller remember
 * to put the & on the pointer.
 */
#define	__wt_free(a, b, c)	__wt_free_worker(a, &(b), c)

#ifdef HAVE_DIAGNOSTIC
#define	WT_ASSERT(env, e)						\
	((e) ? (void)0 : __wt_assert(env, #e, __FILE__, __LINE__))
#else
#define	WT_ASSERT(ienv, e)
#endif

/*
 * The __wt_msg interface appends a <newline> to each message (which is correct,
 * we don't want output messages interspersed in the application's log file.
 * The following structures and macros allow routines to build messages and then
 * dump them to the application's logging file/function.
 */
typedef struct __wt_mbuf {
	ENV	 *env;			/* Enclosing environment */

	char  *first;			/* Allocated message buffer */
	char  *next;			/* Next available byte of the buffer */
	size_t len;			/* Allocated length of the buffer */
} WT_MBUF;

/*
 * Quiet a compiler warning by writing, and then reading, a variable.
 */
#define	WT_CC_QUIET(var, value)	do {				        \
	(var) = (value);					        \
	(var) = (var);						        \
} while (0)

#if defined(__cplusplus)
}
#endif
