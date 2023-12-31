#ifndef __GOT_IT_H
#define __GOT_IT_H

/**
 * @brief get the min value between with two inputs
 * @note  copy from https://github.com/torvalds/linux/blob/HEAD/arch/powerpc/boot/types.h
 */
#define min(x,y)    ({                          \
                        typeof(x) _x = (x);     \
                        typeof(y) _y = (y);     \
                        (void) (&_x == &_y);    \
                        _x < _y ? _x : _y;      \
                    })

#define max(x,y)    ({                          \
                        typeof(x) _x = (x);     \
                        typeof(y) _y = (y);     \
                        (void) (&_x == &_y);    \
                        _x > _y ? _x : _y;      \
                    })

#define min_t(type, a, b) min(((type) a), ((type) b))
#define max_t(type, a, b) max(((type) a), ((type) b))

#endif
