cmake_minimum_required(VERSION 2.8)

project(exo-GT)
add_executable(${PROJECT_NAME} 
    main.cpp

    src/vector.cpp
    src/fcn.cpp
    src/vec.cpp

    include/vector.h
    include/fcn.h
    include/vec.h

    )
target_link_libraries(${PROJECT_NAME}
    pthread)
