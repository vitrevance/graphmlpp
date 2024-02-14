add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# pugixml
include(FetchContent)
FetchContent_Declare(
  pugixml
  URL https://github.com/zeux/pugixml/archive/b2b466403084667c90a0f0cc4e960405cfc8117a.zip
)
FetchContent_MakeAvailable(pugixml)
target_link_libraries(${PROJECT_NAME} INTERFACE pugixml)

# string-view-lite
include(FetchContent)
FetchContent_Declare(
  string_view_lite
  URL https://github.com/martinmoene/string-view-lite/archive/6e5e519d69b4ea99c3095d85d8e1e3ff4d54bbaa.zip
)
FetchContent_MakeAvailable(string_view_lite)
target_link_libraries(${PROJECT_NAME} INTERFACE "string-view-lite")