# 添加接口库
add_library(smart_ptr INTERFACE)

# 设置库的头文件目录
target_include_directories(smart_ptr INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/smart_ptr>
)