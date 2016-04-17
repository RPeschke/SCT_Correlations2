FIND_PACKAGE( ROOT REQUIRED)
FIND_PACKAGE(RapidXML REQUIRED)
FIND_PACKAGE(LCIO )
INCLUDE_DIRECTORIES( . inc ${ROOT_INCLUDE_DIR} )




file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/core_lib/src/*.cc)


set(SCT_ROOT_HEADERS 
  ${PROJECT_SOURCE_DIR}/core_lib/includes/sct/collection.h
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/axis.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/EUTFile.h 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/generic_plane.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/processor.h 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/ProcessorCollection.h 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/processorPlaneVSPlane.h  
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/hit.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/plane.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/legacy/setup_description.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/legacy/s_cuts.h 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/legacy/xml_input_file.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/legacy/Draw.h  
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/xy_pro.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/find_nearest.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/find_nearest_strip.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/truehitExtractor.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/DUT_2_Track_correlator.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/fitterFile.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/FileProcessors/FileProcessors_standard.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/FileProcessors/FileProcessorsBase.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/legacy/SCT_helpers.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/converters.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/analysis/efficiency.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/analysis/residual_efficiency.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/analysis/instrip_efficiency.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/legacy/Cluster_strip.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lcio/lcio_reader.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/internal/strong_types.h
 )


set(LINKDEF_FILE  ${PROJECT_SOURCE_DIR}/core_lib/includes/sct/rootl_link/sct_LinkDef.h)
 SET(MY_INCLUDE_DIRECTORIES
     ${PROJECT_SOURCE_DIR}/core_lib/includes/
    )
 
 set(SCT_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/SCT_DICTIONARY.cxx) 
 
 set(SCT_DICTIONARY_handle ${CMAKE_CURRENT_BINARY_DIR}/SCT_DICTIONARY_handle.cxx) 




FILE(WRITE ${SCT_DICTIONARY_handle} "#ifndef _DEBUG \n")
FILE(APPEND ${SCT_DICTIONARY_handle} "#include \"")
FILE(APPEND ${SCT_DICTIONARY_handle} ${SCT_DICTIONARY})
FILE(APPEND ${SCT_DICTIONARY_handle} "\" \n")
FILE(APPEND ${SCT_DICTIONARY_handle} "#endif // !_DEBUG \n")

ADD_CUSTOM_COMMAND(OUTPUT ${SCT_DICTIONARY_handle}
      COMMAND ${ROOT_CINT_EXECUTABLE}
      ARGS -f ${SCT_DICTIONARY} -c -p -I${MY_INCLUDE_DIRECTORIES} ${SCT_ROOT_HEADERS} ${LINKDEF_FILE} 
)

ADD_LIBRARY( ${PROJECT_NAME} SHARED ${SOURCES} ${SCT_DICTIONARY_handle})

INCLUDE_DIRECTORIES(${RAPIDXML_INCLUDE_DIRS})


IF(LCIO_FOUND)
 
    INCLUDE_DIRECTORIES(${RAPIDXML_INCLUDE_DIRS} ${LCIO_INCLUDE_DIRS})
    add_definitions(-DUSE_LCIO)
    target_link_libraries(${PROJECT_NAME}  ${ROOT_LIBRARIES} ${ADDITIONAL_LIBRARIES}  ${LCIO_LIBRARIES})
MESSAGE(STATUS "using LCIO")
ELSE(LCIO_FOUND)
    INCLUDE_DIRECTORIES(${RAPIDXML_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}  ${ROOT_LIBRARIES} ${ADDITIONAL_LIBRARIES}  )
MESSAGE(STATUS "not using LCIO")

ENDIF(LCIO_FOUND)





INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
