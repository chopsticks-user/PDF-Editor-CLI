


add_executable(pdfeditor )

target_include_directories(pdfeditor PRIVATE
    # ${PROJECT_SOURCE_DIR}/Include
    # PRIVATE ${Container_INCLUDE_DIR}
    # $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
    # $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(pdfeditor 
    INTERFACE CompilerFlags
    # INTERFACE Container
)

# install(TARGETS ${PROJECT_NAME}
#         EXPORT ${PROJECT_NAME}Targets
#         PUBLIC_HEADER DESTINATION 
#             ${PROJECT_SOURCE_DIR}/Source/${PROJECT_NAME}
# )
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
#                                  VERSION ${PROJECT_VERSION}
#                                  COMPATIBILITY SameMajorVersion)
# configure_package_config_file(
#     "${PROJECT_SOURCE_DIR}/CMake/${PROJECT_NAME}Config.cmake.in"
#     "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
#     INSTALL_DESTINATION CMake/${PROJECT_NAME}
# )