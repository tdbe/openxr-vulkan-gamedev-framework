add_library(boost INTERFACE)

# Boost header-only libraries. 
# I just lost hours in submodule and build-as-project weeds because we don't get a 101 simple "let me just import the x library into my own cpp project without bloat and weird workflows and assumptions".
target_include_directories(boost INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/bimap/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/config/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/detail/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/mpl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/preprocessor/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/utility/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/type_traits/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/concept_check/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/static_assert/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/multi_index/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/move/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/throw_exception/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/assert/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/tuple/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/functional/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/container_hash/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/describe/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/iterator/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/bind/include
    
	
	
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/unordered/include
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/container/include
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/algorithm/include
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/concept_check/include
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/type_traits/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/mp11/include
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/predef/include
    #${CMAKE_CURRENT_SOURCE_DIR}/libs/compat/include
)
