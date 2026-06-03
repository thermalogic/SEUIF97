cmake_minimum_required(VERSION 3.15)
project(seuif97 VERSION 1.2.0 LANGUAGES C)

# Source files
set(SRC_FILES
    src/common/boundaries.c
    src/common/property_pair.c
    src/common/region.c
    src/common/seuif97.c
    src/common/thermodynamic_process.c
    src/common/transport.c
    src/algo/polynomial.c
    src/algo/polynomial_solo.c
    src/algo/root.c
    src/algo/rqm.c
    src/algo/sac.c
    src/r1/region1_T_phps.c
    src/r1/region1_gfe.c
    src/r1/region1_out.c
    src/r1/region1_pT.c
    src/r1/region1_pT_ext.c
    src/r1/region1_p_hs.c
    src/r1/region1_pair_ext.c
    src/r1/region1_solo_power.c
    src/r2/region2_T_ph.c
    src/r2/region2_T_ps.c
    src/r2/region2_gfe.c
    src/r2/region2_out.c
    src/r2/region2_pT.c
    src/r2/region2_pT_ext.c
    src/r2/region2_p_hs.c
    src/r2/region2_pair_ext.c
    src/r2/region2_solo_power.c
    src/r3/region3_Td.c
    src/r3/region3_Td_ext.c
    src/r3/region3_Tv_phps.c
    src/r3/region3_hfe.c
    src/r3/region3_out.c
    src/r3/region3_p_hs.c
    src/r3/region3_pair_ext.c
    src/r3/region3_solo_power.c
    src/r3/region3_v_pT.c
    src/r3/region3_v_pT_subregion_.c
    src/r4/region4_T_hs.c
    src/r4/region4_hxsx.c
    src/r4/region4_out.c
    src/r4/region4_pair_ext.c
    src/r4/region4_sat_pT.c
    src/r5/region5_gfe.c
    src/r5/region5_out.c
    src/r5/region5_pT.c
    src/r5/region5_pT_ext.c
    src/r5/region5_pair_ext.c
    src/r5/region5_ph_ps_hs.c
)

# Shared library
add_library(seuif97 SHARED ${SRC_FILES})

if(MSVC)
    # Use module definition file for __stdcall exports
    target_sources(seuif97 PRIVATE src/common/seuif97.def)
endif()

target_include_directories(seuif97 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/algo>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/r1>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/r2>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/r3>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/r4>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/r5>
    $<INSTALL_INTERFACE:include>
)

# Performance optimization flags
if(MSVC)
    # MSVC optimization flags
    target_compile_options(seuif97 PRIVATE /O2 /GL)
    target_link_options(seuif97 PRIVATE /LTCG)
else()
    # GCC/Clang optimization flags
    target_compile_options(seuif97 PRIVATE -O3 -march=native)
    if(APPLE)
        # macOS linker doesn't support -flto directly, handled by compiler
        target_compile_options(seuif97 PRIVATE -flto)
        target_link_options(seuif97 PRIVATE -flto)
    else()
        # Linux
        target_compile_options(seuif97 PRIVATE -flto)
        target_link_options(seuif97 PRIVATE -flto)
        target_link_libraries(seuif97 PRIVATE m)
    endif()
endif()

# Install rules
include(GNUInstallDirs)
install(TARGETS seuif97
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Demo executable (optional)
option(BUILD_DEMO "Build speed executable" OFF)
if(BUILD_DEMO)
    set(EXE_SOURCES ./demo/demo-c/speed.c)
    add_executable(speed ${EXE_SOURCES})
    target_include_directories(speed PRIVATE ${PROJECT_SOURCE_DIR}/demo/demo-c/include)
    target_link_libraries(speed PRIVATE seuif97)
    add_dependencies(speed seuif97)
    # Copy DLL to demo directory for runtime
    if(MSVC)
        add_custom_command(TARGET speed POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:seuif97>
                $<TARGET_FILE_DIR:speed>
        )
    endif()
endif()