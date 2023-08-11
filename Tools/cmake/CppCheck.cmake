add_custom_target(
    CppCheck
    ALL
    COMMAND /usr/bin/cppcheck
    --enable=warning,performance,portability,style
    --std=c++11
    --verbose
    --quiet
    --error-exitcode=1
    ${CMAKE_SOURCE_DIR}/Source
    ${CMAKE_SOURCE_DIR}/Tests
)
