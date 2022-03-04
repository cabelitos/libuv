/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef UV_DARWIN_H
#define UV_DARWIN_H

#if defined(__APPLE__) && defined(__MACH__)
# include <mach/mach.h>
# include <mach/task.h>
# include <mach/semaphore.h>
# include <TargetConditionals.h>
# define UV_PLATFORM_SEM_T semaphore_t
#endif

#if !defined(_USE_ASYNC_ADDR_INFO) && !defined(_USE_ASYNC_GETNAME_INFO)
# define UV_IO_PRIVATE_PLATFORM_EXTRA_FIELDS /* empty */

#elif defined(_USE_ASYNC_ADDR_INFO) && defined(_USE_ASYNC_GETNAME_INFO)
# define UV_IO_PRIVATE_PLATFORM_EXTRA_FIELDS                                  \
  unsigned int  is_mach_port;                                                 \
  struct uv_getaddrinfo_s *getaddrinfo_req;                                   \
  struct uv_getnameinfo_s *getnameinfo_req;

#elif defined(_USE_ASYNC_ADDR_INFO) && !defined(_USE_ASYNC_GETNAME_INFO)
# define UV_IO_PRIVATE_PLATFORM_EXTRA_FIELDS                                  \
  unsigned int  is_mach_port;                                                 \
  struct uv_getaddrinfo_s *getaddrinfo_req;

#elif !defined(_USE_ASYNC_ADDR_INFO) && defined(_USE_ASYNC_GETNAME_INFO)
# define UV_IO_PRIVATE_PLATFORM_EXTRA_FIELDS                                  \
  unsigned int  is_mach_port;                                                 \
  struct uv_getnameinfo_s *getnameinfo_req;

#endif

#if defined(_USE_ASYNC_ADDR_INFO)
# define UV_GETADDRINFO_PLATFORM_PRIVATE_EXTRA_FIELDS                         \
    uv__io_t async_addrinfo_io;
#else
# define UV_GETADDRINFO_PLATFORM_PRIVATE_EXTRA_FIELDS /* empty */
#endif

#if defined(_USE_ASYNC_GETNAME_INFO)
# define UV_GETNAMEINFO_PLATFORM_PRIVATE_EXTRA_FIELDS                         \
    uv__io_t async_getnameinfo_io;
#else
# define UV_GETNAMEINFO_PLATFORM_PRIVATE_EXTRA_FIELDS /* empty */
#endif

#define UV_IO_PRIVATE_PLATFORM_FIELDS                                         \
  int rcount;                                                                 \
  int wcount;                                                                 \
  UV_IO_PRIVATE_PLATFORM_EXTRA_FIELDS                                         \

#define UV_PLATFORM_LOOP_FIELDS                                               \
  uv_thread_t cf_thread;                                                      \
  void* _cf_reserved;                                                         \
  void* cf_state;                                                             \
  uv_mutex_t cf_mutex;                                                        \
  uv_sem_t cf_sem;                                                            \
  void* cf_signals[2];                                                        \

#define UV_PLATFORM_FS_EVENT_FIELDS                                           \
  uv__io_t event_watcher;                                                     \
  char* realpath;                                                             \
  int realpath_len;                                                           \
  int cf_flags;                                                               \
  uv_async_t* cf_cb;                                                          \
  void* cf_events[2];                                                         \
  void* cf_member[2];                                                         \
  int cf_error;                                                               \
  uv_mutex_t cf_mutex;                                                        \

#define UV_STREAM_PRIVATE_PLATFORM_FIELDS                                     \
  void* select;                                                               \

#define UV_GETADDRINFO_PLATFORM_PRIVATE_FIELDS                                \
  UV_GETADDRINFO_PLATFORM_PRIVATE_EXTRA_FIELDS                                \

#define UV_GETNAMEINFO_PLATFORM_PRIVATE_FIELDS                                \
  UV_GETNAMEINFO_PLATFORM_PRIVATE_EXTRA_FIELDS                                \

#define UV_HAVE_KQUEUE 1

#endif /* UV_DARWIN_H */
