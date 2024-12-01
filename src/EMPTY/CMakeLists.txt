# Project name, default is the directory name
GET_DIR_NAME(DIRNAME)
SET(TARGET_NAME "${TARGET_PREFIX}${DIRNAME}")
# Use ';' to separate multiple directories
FILE(GLOB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hxx"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.inl"
)

LIST(APPEND SOURCES "${CMAKE_SOURCE_DIR}/include/template/TypeList.hxx")
LIST(APPEND SOURCES "${CMAKE_SOURCE_DIR}/include/template/List.hxx")
LIST(APPEND SOURCES "${CMAKE_SOURCE_DIR}/include/template/Name.hxx")

# Use ';' to separate multiple libraries
SET(LIBRARIES "")
ADD_TARGET(MODE "EXE" NAME ${TARGET_NAME} SOURCES ${SOURCES} LIBS ${LIBRARIES})
