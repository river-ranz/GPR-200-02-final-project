# example

file(
 GLOB_RECURSE FINALPROJECT_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE FINALPROJECT_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)

install(FILES ${FINALPROJECT_INC} DESTINATION include/projectFiles_finalProject)
add_executable(projectFiles_finalProject ${FINALPROJECT_SRC} ${FINALPROJECT_INC} ${FINALPROJECT_ASSETS})
target_link_libraries(projectFiles_finalProject PUBLIC core IMGUI)
target_include_directories(projectFiles_finalProject PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})
