cmake_minimum_required(VERSION 3.16)

set(project_name select_study)

project(${project_name})

set(LINK_LIBRARIES
    stdc++
)

link_directories(
  $ENV{SDKTARGETSYSROOT}/usr/lib
)

set(COMPILE_OPTIONS
  $ENV{CMAKE_CXX_FLAGS}
  -Wall
  -fexceptions
  -DGIT_HASH=\"${COMMIT_HASH}\"
#   -DAA_ENABLE
)

## リンクオプションの指定（共通）
set(LINK_OPTIONS
    $ENV{CMAKE_EXE_LINKER_FLAGS}
    -Wl,-Bdynamic
    -Wl,-z,relro,-z,lazy
    -Wl,-Map,${exe_name}.map
)

set(INCLUDE_PATH
    ## 本ソース
    ${CMAKE_SOURCE_DIR}/
)

#######################################################################################
# Set Macro For Add Test Executable.
macro(add_custom_exe TARGET_NAME)
    # message(${ARGV})
    message("+------------------------------------------------------------+")
    message("| --> Add executable: <<< ${TARGET_NAME} >>>")

    # message("+------------------------------------------------------------+")
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
        -DUNIT_TEST
        -DPRIVATE_FUNC_TEST
        -Wno-error
    )
    target_compile_features(${TARGET_NAME} PRIVATE
        cxx_std_17
    )
    target_link_options(${TARGET_NAME} PRIVATE
        ${LINK_OPTIONS}
    )
endmacro()

add_custom_exe(simple_pipe
    ${CMAKE_SOURCE_DIR}/simple_pipe.c
)

add_custom_exe(pipe_with_child_process
    ${CMAKE_SOURCE_DIR}/pipe_with_child_process.c
)

add_custom_exe(twoway_pipe
    ${CMAKE_SOURCE_DIR}/twoway_pipe.c
)

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