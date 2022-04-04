#pragma once

#if defined MAKE_GAME_LIB
 #define GAME_LIB_EXPORT Q_DECL_EXPORT
#else
 #define GAME_LIB_EXPORT Q_DECL_IMPORT
#endif