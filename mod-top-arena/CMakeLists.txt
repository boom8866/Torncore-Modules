AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/Top_Arena_NPC.cpp")
AC_ADD_SCRIPT_LOADER("MyTopArena" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/my_customArenaTop.conf.dist")