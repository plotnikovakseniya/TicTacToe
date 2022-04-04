#pragma once

#if defined MAKE_NET_LIB
 #define NET_LIB_EXPORT Q_DECL_EXPORT
#else
 #define NET_LIB_EXPORT Q_DECL_IMPORT
#endif
