add_library(${PROJECT_NAME} SHARED AdoubleModule.cpp TladoubleModule.cpp array_types.cpp)

#add_executable(${PROJECT_NAME} adolc_interface.cpp)
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC "${ADOLC_DIR}/include/"
    PUBLIC "${ADOLC_DIR}/include/adolc"
)


if(MATH_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${MATH_LIBRARY})
endif()

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE JlCxx::cxxwrap_julia
    PRIVATE ${ADOLC_LIB}
    m
)
