cmake_minimum_required(VERSION 3.10)
project(StarKirby)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 查找SFML库
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# 包含头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/src  # 用于core/GameLoop.h形式的包含
    src/core                 # 用于直接包含头文件
    src/entity/Character
)

# 添加可执行文件
add_executable(StarKirby 
    main.cpp
    src/core/GameLoop.cpp
    src/core/KirbyManager.cpp
    src/core/EnemyManager.cpp
    src/core/ScoreManager.cpp
    src/scene/Background.cpp
    src/scene/Barrier.cpp
    src/entity/Character/MyKirby.cpp
    src/entity/Enemy/SparkEnemy.cpp
    src/entity/Enemy/FlyEnemy.cpp
    src/entity/Enemy/PlantEnemy.cpp
    src/entity/Enemy/Enemy.cpp
    src/animation/Animation.cpp
)

# 链接SFML库
target_link_libraries(StarKirby 
    sfml-graphics 
    sfml-window 
    sfml-system
)


# 复制 assets 文件夹到构建目录
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# 复制动态库到输出目录(仅Windows需要)
if(WIN32)
    add_custom_command(TARGET StarKirby POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "D:/c++/lib/SFML-2.6.2/bin"
            $<TARGET_FILE_DIR:StarKirby>
    )
endif()
