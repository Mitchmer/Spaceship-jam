file(GLOB_RECURSE APP CONFIGURE_DEPENDS ./*.cpp)

add_library(engine_lib ${APP})
target_link_libraries(engine_lib PUBLIC raylib)
