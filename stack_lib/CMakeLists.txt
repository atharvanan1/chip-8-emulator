project(stack_lib)

set(HEADER_FILES
        stack.h
        )

set(SOURCE_FILES
        stack.c
        )

add_library(stack_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
