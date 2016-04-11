FIND_PACKAGE( ROOT REQUIRED)
FIND_PACKAGE(RapidXML REQUIRED)

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
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lagacy/setup_description.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lagacy/s_cuts.h 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lagacy/xml_input_file.hh 
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lagacy/Draw.h  
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/xy_pro.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/find_nearest.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/find_nearest_strip.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/truehitExtractor.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/DUT_2_Track_correlator.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/predef/fitterFile.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/FileProcessors/FileProcessors_standard.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/FileProcessors/FileProcessorsBase.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lagacy/SCT_helpers.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/xy_processors/converters.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/analysis/efficiency.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/analysis/residual_efficiency.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/analysis/instrip_efficiency.hh
${PROJECT_SOURCE_DIR}/core_lib/includes/sct/lagacy/Cluster_strip.hh
 )


set(LINKDEF_FILE  ${PROJECT_SOURCE_DIR}/core_lib/includes/sct/rootl_link/sct_LinkDef.h)
 SET(MY_INCLUDE_DIRECTORIES
     ${PROJECT_SOURCE_DIR}/core_lib/includes/
    )
 
 set(SCT_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/SCT_DICTIONARY.cxx) 
 


ADD_CUSTOM_COMMAND(OUTPUT ${SCT_DICTIONARY}
      COMMAND ${ROOT_CINT_EXECUTABLE}
      ARGS -f ${SCT_DICTIONARY} -c -p -I${MY_INCLUDE_DIRECTORIES} ${SCT_ROOT_HEADERS} ${LINKDEF_FILE} 
)

ADD_LIBRARY( ${PROJECT_NAME} SHARED ${SOURCES} ${SCT_DICTIONARY})

INCLUDE_DIRECTORIES(${RAPIDXML_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}  ${ROOT_LIBRARIES} ${ADDITIONAL_LIBRARIES}  ${RAPIDXML_INCLUDE_DIRS})


INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
