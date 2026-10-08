file(GLOB_RECURSE APP CONFIGURE_DEPENDS ./*.cpp)

add_library(gameobjects_lib ${APP})
target_link_libraries(gameobjects_lib PUBLIC raylib)
