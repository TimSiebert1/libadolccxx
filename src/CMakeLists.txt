add_library(${PROJECT_NAME} SHARED TbadoubleModule.cpp TladoubleModule.cpp array_types.cpp)

#add_executable(${PROJECT_NAME} adolc_interface.cpp)
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC "${ADOLC_DIR}/include/"
    PUBLIC "${ADOLC_DIR}/include/adolc"
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC ${ADOLC_LIB}
    PUBLIC JlCxx::cxxwrap_julia
    )
