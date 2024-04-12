cmake_minimum_required(VERSION 3.16)

set(project_name ipc_study)

project(${project_name})

set(LINK_LIBRARIES
    stdc++
)

link_directories(
  /usr/lib
)

set(COMPILE_OPTIONS
  $ENV{CMAKE_CXX_FLAGS}
  -Wall
  -fexceptions
  -DGIT_HASH=\"${COMMIT_HASH}\"
)

set(LINK_OPTIONS
    $ENV{CMAKE_EXE_LINKER_FLAGS}
)

set(INCLUDE_PATH
    ${CMAKE_SOURCE_DIR}/
)

#######################################################################################
macro(add_custom_exe TARGET_NAME)
    message("+------------------------------------------------------------+")
    message("| --> Add executable: <<< ${TARGET_NAME} >>>")
    # message("+------------------------------------------------------------+")
    # message(${ARGV})
    add_executable(${TARGET_NAME}
        ${ARGV}
    )

    target_include_directories(${TARGET_NAME} PRIVATE
        ${INCLUDE_PATH}
        ${CMAKE_CURRENT_BINARY_DIR}
    )

    target_link_libraries(${TARGET_NAME} PRIVATE
        ${LINK_LIBRARIES}
    )
    target_compile_options(${TARGET_NAME} PRIVATE
        ${COMPILE_OPTIONS}
        # --coverage
        -g
        -Wno-variadic-macros
        -Wno-unused-parameter
        -Wno-error
    )
    target_compile_features(${TARGET_NAME} PRIVATE
        cxx_std_17
    )
    target_link_options(${TARGET_NAME} PRIVATE
        ${LINK_OPTIONS}
    )
endmacro()

add_custom_exe(fifo_server
    ${CMAKE_SOURCE_DIR}/fifo_server.c
)

add_custom_exe(fifo_client
    ${CMAKE_SOURCE_DIR}/fifo_client.c
)

add_custom_exe(select_with_fd_server
    ${CMAKE_SOURCE_DIR}/select_with_fd_server.c
)

add_custom_exe(select_with_fd_client
    ${CMAKE_SOURCE_DIR}/select_with_fd_client.c
)
