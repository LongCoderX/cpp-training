# 添加可执行文件
add_executable(test_smart_ptr shape.cpp test_smart_ptr.cpp)

# 链接 smart_ptr 库
target_link_libraries(test_smart_ptr PRIVATE smart_ptr)

# 设置测试目标的头文件搜索路径
target_include_directories(test_smart_ptr PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include/smart_ptr
)

install(TARGETS test_smart_ptr
    DESTINATION run/tests)