#ifndef LOV_ATTR_H
#define LOV_ATTR_H

#if defined(__GNUC__) || defined(__clang__)
#define LOV_INLINE __attribute__((__always_inline__)) static inline
#define LOV_ALIGNED(a) __attribute__((__aligned__(a)))
#elif defined(_MSC_VER)
#define LOV_INLINE static __forceinline
#define LOV_ALIGNED(a) __declspec(align(a))
#else
#define LOV_INLINE
#define LOV_ALIGNED(a)
#endif /* Compilers */

#if defined(__GNUC__) || defined(__clang__)
#define VGM_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#define VGM_LIKELY(expr) __builtin_expect(!!(expr), 1)
#else
#define VGM_UNLIKELY(expr) (expr)
#define VGM_LIKELY(expr) (expr)
#endif /* __GNUC__ || __clang__ */

#endif /* LOV_ATTR_H */
