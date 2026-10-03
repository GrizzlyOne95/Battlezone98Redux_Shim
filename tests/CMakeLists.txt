cmake_minimum_required(VERSION 3.20)
project(BzrNetProtocolTests LANGUAGES CXX)

# Linux CMake/CTest harness for the engine-independent unit tests. Every
# target here is a self-contained executable (no game engine linkage) so the
# suite can be configured, built, and run with plain CMake + CTest:
#   cmake -S tests -B tests/build && cmake --build tests/build -j && ctest --test-dir tests/build --output-on-failure
enable_testing()

# Qualification tooling has pure host seams. Neither test requires the private
# executable, Windows process APIs, Frida, pefile or capstone.
find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
    add_test(NAME weapon_presentation_live_capture_tests
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../reverse_engineering/test_weapon_presentation_live.py")
endif()
find_program(OPENSHIM_NODE_EXECUTABLE NAMES node nodejs)
if(OPENSHIM_NODE_EXECUTABLE)
    add_test(NAME weapon_presentation_probe_tests
        COMMAND "${OPENSHIM_NODE_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../reverse_engineering/test_weapon_presentation_probe.js")
endif()

# The common case: the listed sources, ../include, one C++ standard, warnings
# as errors on both compilers, and a CTest entry named after the target.
# Targets that need anything else (definitions, libraries, a Windows-only
# guard) are written out in full below.
function(openshim_add_test name)
    cmake_parse_arguments(ARG "" "STD" "SOURCES" ${ARGN})
    add_executable(${name} ${ARG_SOURCES})
    target_include_directories(${name} PRIVATE ../include)
    target_compile_features(${name} PRIVATE cxx_std_${ARG_STD})
    if(MSVC)
        target_compile_options(${name} PRIVATE /W4 /WX)
    else()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Werror)
    endif()
    add_test(NAME ${name} COMMAND ${name})
endfunction()

openshim_add_test(native_chunk_mesh_tests STD 20 SOURCES
    native_chunk_mesh_tests.cpp
    ../src/patches/native_chunk_mesh.cpp
    ../src/patches/native_chunk_cache.cpp
)

openshim_add_test(bzrnet_protocol_tests STD 20 SOURCES
    bzrnet_protocol_tests.cpp
    ../src/patches/bzrnet_protocol.cpp
)

openshim_add_test(shim_log_tests STD 20 SOURCES
    shim_log_tests.cpp
    ../src/engine/shim_log_sink.cpp
    ../src/engine/shim_log_client.cpp
    ../src/engine/game_log_path.cpp
)

openshim_add_test(bzloader_catalog_tests STD 20 SOURCES
    bzloader_catalog_tests.cpp
    ../src/loader/bzloader_catalog.cpp
)

openshim_add_test(trn_codec_tests STD 20 SOURCES
    trn_codec_tests.cpp
    ../src/patches/trn_codec.cpp
)

openshim_add_test(bzn_analysis_tests STD 20 SOURCES
    bzn_analysis_tests.cpp
)

openshim_add_test(bzn_filename_identity_tests STD 20 SOURCES
    bzn_filename_identity_tests.cpp
)

openshim_add_test(bzn_save_path_tests STD 20 SOURCES
    bzn_save_path_tests.cpp
)

if(WIN32 AND MSVC)
    # file_io_hooks.cpp (included directly by the test) is the runtime half of
    # the file-I/O seam, so the bootstrap half has to be linked with it. Note
    # game_log_path.cpp is deliberately NOT linked: the test supplies its own
    # GetGameLogPath stub, which keeps it from creating a real logs directory.
    add_executable(editor_save_dialog_win32_tests
        editor_save_dialog_win32_tests.cpp
        ../src/patches/trn_codec.cpp
        ../src/patches/terrain_atlas_rect_repair.cpp
        ../src/engine/bootstrap_file_io.cpp)
    target_include_directories(editor_save_dialog_win32_tests PRIVATE ../include)
    target_compile_features(editor_save_dialog_win32_tests PRIVATE cxx_std_20)
    target_compile_definitions(editor_save_dialog_win32_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(editor_save_dialog_win32_tests PRIVATE /W4 /WX)
    target_link_libraries(editor_save_dialog_win32_tests PRIVATE user32)
    add_test(NAME editor_save_dialog_win32_tests COMMAND editor_save_dialog_win32_tests)
endif()

if(WIN32 AND MSVC)
    # The shared import-table and COM-vtable patchers. The IAT cases patch this
    # executable's own GetTickCount import and call through it.
    add_executable(hook_patch_win32_tests hook_patch_win32_tests.cpp)
    target_include_directories(hook_patch_win32_tests PRIVATE ../include)
    target_compile_features(hook_patch_win32_tests PRIVATE cxx_std_20)
    target_compile_options(hook_patch_win32_tests PRIVATE /W4 /WX)
    add_test(NAME hook_patch_win32_tests COMMAND hook_patch_win32_tests)
endif()

openshim_add_test(numeric_locale_compat_tests STD 20 SOURCES
    numeric_locale_compat_tests.cpp
    ../src/patches/numeric_locale_compat.cpp
)

add_executable(native_ui_validation_tests
    native_ui_validation_tests.cpp
)

openshim_add_test(enhanced_light_selection_tests STD 20 SOURCES
    enhanced_light_selection_tests.cpp
    ../src/engine/enhanced_light_selection.cpp
)

add_executable(enhanced_light_selection_bench
    enhanced_light_selection_bench.cpp
    ../src/engine/enhanced_light_selection.cpp
)

openshim_add_test(weapon_convergence_tests STD 20 SOURCES
    weapon_convergence_tests.cpp
)

openshim_add_test(weapon_presentation_tests STD 20 SOURCES
    weapon_presentation_tests.cpp
    ../src/patches/weapon_presentation.cpp
)

openshim_add_test(weapon_presentation_native_policy_tests STD 20 SOURCES
    weapon_presentation_native_policy_tests.cpp
    ../src/patches/weapon_presentation.cpp
)

if(WIN32 AND MSVC AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    openshim_add_test(weapon_presentation_bridges_win32_tests STD 20 SOURCES
        weapon_presentation_bridges_win32_tests.cpp
        ../src/patches/weapon_presentation_call_bridges.cpp
    )
endif()

openshim_add_test(headlight_falloff_tests STD 20 SOURCES
    headlight_falloff_tests.cpp
)

# Built as C++14: the reorder core and the output-cap header are shared with
# translation units that must stay C++14-compatible.
openshim_add_test(net_reorder_core_tests STD 14 SOURCES
    net_reorder_core_tests.cpp
)

openshim_add_test(diagnostic_output_cap_tests STD 14 SOURCES
    diagnostic_output_cap_tests.cpp
)

add_executable(shadow_far_distance_tests
    shadow_far_distance_tests.cpp
)

openshim_add_test(chunk_batch_invalidation_tests STD 20 SOURCES
    chunk_batch_invalidation_tests.cpp
)

openshim_add_test(sun_flash_tests STD 20 SOURCES
    sun_flash_tests.cpp
)

openshim_add_test(env_switch_table_tests STD 20 SOURCES
    env_switch_table_tests.cpp
)

openshim_add_test(terrain_semantic_tests STD 20 SOURCES
    terrain_semantic_tests.cpp
    ../src/patches/terrain_semantic.cpp
)

# These three used to run only from scripts/run_*_tests.ps1, which no CI lane
# calls (audit P2-7).
openshim_add_test(backend_selection_tests STD 20 SOURCES
    backend_selection_tests.cpp
    ../src/engine/backend_selection.cpp
)

openshim_add_test(ui_decor_tests STD 20 SOURCES
    ui_decor_tests.cpp
    ../src/engine/ui_decor.cpp
)

openshim_add_test(ogre_profiler_algorithms_tests STD 17 SOURCES
    ogre_profiler_algorithms_tests.cpp
)

openshim_add_test(bool_token_tests STD 20 SOURCES
    bool_token_tests.cpp
)

openshim_add_test(map_filter_extras_tests STD 14 SOURCES
    map_filter_extras_tests.cpp
)

openshim_add_test(memory_access_tests STD 20 SOURCES
    memory_access_tests.cpp
)

openshim_add_test(stable_id_list_tests STD 20 SOURCES
    stable_id_list_tests.cpp
)

openshim_add_test(terrain_tile_blend_tests STD 20 SOURCES
    terrain_tile_blend_tests.cpp
)

openshim_add_test(terrain_atlas_rect_repair_tests STD 20 SOURCES
    terrain_atlas_rect_repair_tests.cpp
    ../src/patches/terrain_atlas_rect_repair.cpp
)

add_executable(resolve_table_tests
    resolve_table_tests.cpp
    ../src/engine/resolve_table.cpp
)

# Pins the GameObject/Ordnance field offsets that the runtime hooks read. Pure
# header constants, so it needs no engine code and runs on the Linux host lane.
openshim_add_test(object_layout_tests STD 20 SOURCES
    object_layout_tests.cpp
)

# Cross-checks that a patch is registered in every place it has to be. Pure
# text over the repository's own sources, so it needs no engine code.
add_executable(patch_registration_tests
    patch_registration_tests.cpp
)
target_include_directories(patch_registration_tests PRIVATE ../include)
target_compile_features(patch_registration_tests PRIVATE cxx_std_20)
target_compile_definitions(patch_registration_tests PRIVATE
    BZR_PATCHES_JSON="${CMAKE_CURRENT_SOURCE_DIR}/../scripts/patches.json"
    BZR_PATCHES_H="${CMAKE_CURRENT_SOURCE_DIR}/../include/patches.h"
    BZR_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../src")

# Pins the x86-32 length decoder that InstallInlineDetour32 uses to refuse
# steals that split an instruction. Pure byte tables, no engine code.
openshim_add_test(x86_length_tests STD 20 SOURCES
    x86_length_tests.cpp
    ../src/engine/x86_length.cpp
)

openshim_add_test(openshim_update_manifest_tests STD 20 SOURCES
    openshim_update_manifest_tests.cpp
    ../src/patches/openshim_update_manifest.cpp
)
openshim_add_test(openshim_update_support_tests STD 20 SOURCES
    openshim_update_support_tests.cpp
    ../src/patches/openshim_update_support.cpp
)

# The OPENSHIM_*/BZR_* environment redirect: which openshim.ini key each
# legacy name reads, how values are normalised, and the INI-before-launch-
# environment order (audit P2-7). The Win32 readers stay in
# openshim_env_config.cpp; this links only the decision half.
openshim_add_test(openshim_env_mapping_tests STD 20 SOURCES
    openshim_env_mapping_tests.cpp
    ../src/patches/openshim_env_mapping.cpp
)

# The non-throwing scripts/patches.json readers the patch thread relies on.
# Pure nlohmann over the document, so it runs on the Linux host lane, and it
# walks the shipped patches.json to prove the readers accept every entry.
# resolve_table.cpp supplies the IDA pattern parser the fallback-site checks
# feed with the shipped patterns.
add_executable(patch_config_parse_tests
    patch_config_parse_tests.cpp
    ../src/engine/patch_config_parse.cpp
    ../src/engine/resolve_table.cpp
)
target_include_directories(patch_config_parse_tests PRIVATE ../include)
target_compile_features(patch_config_parse_tests PRIVATE cxx_std_20)
target_compile_definitions(patch_config_parse_tests PRIVATE
    BZR_PATCHES_JSON="${CMAKE_CURRENT_SOURCE_DIR}/../scripts/patches.json")

openshim_add_test(ai_range_policy_tests STD 20 SOURCES
    ai_range_policy_tests.cpp
)

openshim_add_test(lcbench_safety_policy_tests STD 20 SOURCES
    lcbench_safety_policy_tests.cpp
)

openshim_add_test(autosave_gate_tests STD 20 SOURCES
    autosave_gate_tests.cpp
)

openshim_add_test(native_save_flag_tests STD 20 SOURCES
    native_save_flag_tests.cpp
)

openshim_add_test(render_profile_tests STD 20 SOURCES
    render_profile_tests.cpp
    ../src/engine/render_profile.cpp
)

openshim_add_test(request_apply_tracker_tests STD 20 SOURCES
    request_apply_tracker_tests.cpp
)

openshim_add_test(render_profile_resources_tests STD 20 SOURCES
    render_profile_resources_tests.cpp
    ../src/engine/render_profile_resources.cpp
)

add_executable(dx11_legacy_material_compat_tests
    dx11_legacy_material_compat_tests.cpp
    ../src/engine/dx11_legacy_material_compat.cpp
)

openshim_add_test(openshim_assets_tests STD 20 SOURCES
    openshim_assets_tests.cpp
    ../src/engine/openshim_assets.cpp
    ../src/engine/render_profile_resources.cpp
    ../src/engine/shim_log_sink.cpp
    ../src/engine/shim_log_client.cpp
    ../src/engine/game_log_path.cpp
)

target_compile_features(native_ui_validation_tests PRIVATE cxx_std_20)
target_include_directories(enhanced_light_selection_bench PRIVATE ../include)
target_compile_features(enhanced_light_selection_bench PRIVATE cxx_std_20)
target_include_directories(shadow_far_distance_tests PRIVATE ../include)
target_compile_features(shadow_far_distance_tests PRIVATE cxx_std_20)
target_include_directories(resolve_table_tests PRIVATE ../include ../third_party)
target_compile_features(resolve_table_tests PRIVATE cxx_std_20)
# Point the test at the patches.json the game will actually load, so the
# migrated signatures are checked against the shipped artifact and not only
# against a copy embedded in the test.
target_compile_definitions(resolve_table_tests PRIVATE
    BZR_PATCHES_JSON="${CMAKE_CURRENT_SOURCE_DIR}/../scripts/patches.json")

if(MSVC)
    target_compile_options(native_ui_validation_tests PRIVATE /W4 /WX)
    target_compile_options(enhanced_light_selection_bench PRIVATE /W4 /WX)
    target_compile_options(shadow_far_distance_tests PRIVATE /W4 /WX)
    target_compile_options(resolve_table_tests PRIVATE /W4 /WX)
    target_compile_options(patch_registration_tests PRIVATE /W4 /WX)
else()
    target_compile_options(native_ui_validation_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(enhanced_light_selection_bench PRIVATE -Wall -Wextra -Werror)
    target_compile_options(resolve_table_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(patch_registration_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_test(NAME shadow_far_distance_tests COMMAND shadow_far_distance_tests)
add_test(NAME native_ui_validation_tests COMMAND native_ui_validation_tests)
add_test(NAME resolve_table_tests COMMAND resolve_table_tests)
add_test(NAME patch_registration_tests COMMAND patch_registration_tests)
add_test(NAME patch_config_parse_tests COMMAND patch_config_parse_tests)

target_include_directories(dx11_legacy_material_compat_tests PRIVATE ../include)
target_compile_features(dx11_legacy_material_compat_tests PRIVATE cxx_std_20)
target_compile_definitions(dx11_legacy_material_compat_tests PRIVATE
    _CRT_SECURE_NO_WARNINGS
    BZR_FIXEDFUNC_PROGRAM="${CMAKE_CURRENT_SOURCE_DIR}/../resources/renderer/enhanced/openshim_dx11_fixedfunc.program"
    BZR_FIXEDFUNC_HLSL="${CMAKE_CURRENT_SOURCE_DIR}/../resources/renderer/enhanced/openshim_dx11_fixedfunc-sm4.hlsl")

if(MSVC)
    target_compile_options(dx11_legacy_material_compat_tests PRIVATE /W4 /WX)
else()
    target_compile_options(dx11_legacy_material_compat_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_test(NAME dx11_legacy_material_compat_tests COMMAND dx11_legacy_material_compat_tests)

# CLI parser parity defect model (PR #69). This test is engine-independent:
# it models Redux's strtok comma defect and the pristine-snapshot repair
# without linking any engine patch implementation. Its primary compatibility
# target is the canonical "-shellmap:216,178" form; equals/quoted/whitespace
# tolerant forms are exercised as optional OpenShim extensions, not as proven
# 1.5 parity, per the RE report's evidence grading.
add_executable(cli_parser_tests
    cli_parser_tests.cpp
)
target_compile_features(cli_parser_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(cli_parser_tests PRIVATE /W4 /WX)
else()
    target_compile_options(cli_parser_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME cli_parser_tests COMMAND cli_parser_tests)

openshim_add_test(player_kill_trace_tests STD 20 SOURCES
    player_kill_trace_tests.cpp
)

openshim_add_test(fog_wake_tests STD 20 SOURCES
    fog_wake_tests.cpp
    ../src/engine/fog_wake.cpp
)

openshim_add_test(fog_wake_runtime_tests STD 20 SOURCES
    fog_wake_runtime_tests.cpp
    ../src/engine/fog_wake_runtime.cpp
    ../src/engine/fog_wake.cpp
)

openshim_add_test(odf_compat_tests STD 20 SOURCES
    odf_compat_tests.cpp
    ../src/patches/odf_compat.cpp
)

openshim_add_test(enhanced_resource_bootstrap_tests STD 20 SOURCES
    enhanced_resource_bootstrap_tests.cpp
    ../src/engine/enhanced_resource_bootstrap.cpp
)

# Regression: the ODF item-hook trampoline must relocate whole instructions.
# Relocating five bytes split `mov eax,[ebp+8]` and made the trampoline eat its
# own return jump, which broke every engine item read and stopped the game
# loading any mission. Header-only and engine-free, so it runs anywhere.
openshim_add_test(odf_item_prologue_tests STD 20 SOURCES
    odf_item_prologue_tests.cpp
)

# Lock arithmetic of the ODF item detours against a fake engine (audit P1-7):
# a cached UseItem hit must still reach the engine, so the one-for-one
# UnlockItem forwards never drive its lock count below zero, and every holder
# served while a feature is armed has a record to release. Windows-only: the
# detours are __cdecl over SEH-guarded engine calls.
if(WIN32 AND MSVC)
    add_executable(odf_item_hooks_tests
        odf_item_hooks_tests.cpp
        ../src/patches/odf_item_hooks.cpp
        ../src/patches/odf_compat.cpp
        ../src/engine/shim_log_sink.cpp
        ../src/engine/shim_log_client.cpp)
    target_include_directories(odf_item_hooks_tests PRIVATE ../include)
    target_compile_features(odf_item_hooks_tests PRIVATE cxx_std_20)
    target_compile_definitions(odf_item_hooks_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(odf_item_hooks_tests PRIVATE /W4 /WX)
    add_test(NAME odf_item_hooks_tests COMMAND odf_item_hooks_tests)
endif()
# Render-effect intent (the EXU-facing renderer boundary). Engine-independent
# by construction: the whole requested/supported/effective decision lives in
# src/engine/render_effect_intent.cpp with no Windows, D3D11 or Ogre in it, and
# the test drives it through a fake provider.
# The published SDK export contract. Pure text over the repository, so it runs
# on the Linux lane: winmm.def, the generated thunk list, and the recorded
# export baseline of a shipped winmm.dll must all agree.
add_executable(openshim_sdk_export_contract_tests
    openshim_sdk_export_contract_tests.cpp
)
target_compile_features(openshim_sdk_export_contract_tests PRIVATE cxx_std_20)
target_compile_definitions(openshim_sdk_export_contract_tests PRIVATE
    BZR_WINMM_DEF="${CMAKE_CURRENT_SOURCE_DIR}/../src/winmm.def"
    BZR_SDK_EXPORTS_INC="${CMAKE_CURRENT_SOURCE_DIR}/../include/openshim_sdk_exports.inc"
    BZR_EXPORT_BASELINE="${CMAKE_CURRENT_SOURCE_DIR}/winmm_export_baseline.txt")
if(MSVC)
    target_compile_options(openshim_sdk_export_contract_tests PRIVATE /W4 /WX)
else()
    target_compile_options(openshim_sdk_export_contract_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME openshim_sdk_export_contract_tests COMMAND openshim_sdk_export_contract_tests)

# Runtime behaviour of the generated export thunks. Windows-only: it links the
# real thunks, which are Win32 calling conventions over Win32 types.
if(WIN32 AND MSVC)
    add_executable(openshim_sdk_thunk_tests
        openshim_sdk_thunk_tests.cpp
        ../src/engine/openshim_sdk_thunks.cpp
        ../src/engine/openshim_sdk_bridge.cpp
        ../src/engine/shim_log_sink.cpp
    ../src/engine/shim_log_client.cpp
        ../src/engine/game_log_path.cpp)
    target_include_directories(openshim_sdk_thunk_tests PRIVATE ../include ../third_party)
    target_compile_features(openshim_sdk_thunk_tests PRIVATE cxx_std_20)
    # BZRO_API must be dllexport here, matching how the shim builds these
    # translation units; otherwise the namespaced thunks are declared
    # dllimport and defined locally.
    target_compile_definitions(openshim_sdk_thunk_tests PRIVATE
        BZROPENSHIM_EXPORTS _CRT_SECURE_NO_WARNINGS)
    target_compile_options(openshim_sdk_thunk_tests PRIVATE /W4 /WX)
    add_test(NAME openshim_sdk_thunk_tests COMMAND openshim_sdk_thunk_tests)
endif()

# The SDK record copy honours the caller's declared capacity (audit P1-8):
# pollEvent and captureDeveloperSnapshot must never write past the record the
# caller's header defined and must say how much they filled. Pins the v2
# layouts (120 / 96 bytes). Windows-only because include/BZROpenShim.h
# carries __declspec.
if(WIN32 AND MSVC)
    add_executable(openshim_sdk_record_copy_tests
        openshim_sdk_record_copy_tests.cpp)
    target_include_directories(openshim_sdk_record_copy_tests PRIVATE ../include)
    target_compile_features(openshim_sdk_record_copy_tests PRIVATE cxx_std_20)
    target_compile_definitions(openshim_sdk_record_copy_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(openshim_sdk_record_copy_tests PRIVATE /W4 /WX)
    add_test(NAME openshim_sdk_record_copy_tests COMMAND openshim_sdk_record_copy_tests)
endif()

# The bootstrap file-I/O seam, end to end and offline. Patches the test's own
# import table with the real wrappers, then drives the lifecycle the game will
# see: opens with no provider installed, then the same opens once OpenShim's
# policy is in place. Windows-only -- it is Win32 import tables and handles.
if(WIN32 AND MSVC)
    add_executable(bootstrap_file_io_tests
        bootstrap_file_io_tests.cpp
        ../src/engine/bootstrap_file_io.cpp
        ../src/engine/game_log_path.cpp)
    target_include_directories(bootstrap_file_io_tests PRIVATE ../include)
    target_compile_features(bootstrap_file_io_tests PRIVATE cxx_std_20)
    target_compile_definitions(bootstrap_file_io_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(bootstrap_file_io_tests PRIVATE /W4 /WX)
    add_test(NAME bootstrap_file_io_tests COMMAND bootstrap_file_io_tests)
endif()

# The bootstrap startup renderer seam with nothing else alive. This is the
# case the renderer split exists for: the decision must be complete before the
# intercepted ConfigFile::load returns, so "a plugin will supply it later" is
# not an option. Windows-only: Win32 file APIs and the real transport.
if(WIN32 AND MSVC)
    add_executable(startup_backend_seam_tests
        startup_backend_seam_tests.cpp
        ../src/engine/startup_backend_seam.cpp
        ../src/engine/startup_seam_wire.cpp
        ../src/engine/backend_selection.cpp
        ../src/engine/render_profile.cpp
        ../src/engine/shim_log_sink.cpp
    ../src/engine/shim_log_client.cpp
        ../src/engine/game_log_path.cpp)
    target_include_directories(startup_backend_seam_tests PRIVATE ../include)
    target_compile_features(startup_backend_seam_tests PRIVATE cxx_std_20)
    target_compile_definitions(startup_backend_seam_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(startup_backend_seam_tests PRIVATE /W4 /WX)
    add_test(NAME startup_backend_seam_tests COMMAND startup_backend_seam_tests)
endif()

# The private bootstrap service table and the two bridges over it. After the
# DLL split these are the only calls from the plugin back into winmm.dll.
if(WIN32 AND MSVC)
    add_executable(openshim_bootstrap_api_tests
        openshim_bootstrap_api_tests.cpp
        ../src/engine/openshim_bootstrap_api.cpp
        ../src/engine/startup_backend_seam.cpp
        ../src/engine/startup_seam_wire.cpp
        ../src/engine/bootstrap_file_io.cpp
        ../src/engine/openshim_sdk_bridge.cpp
        ../src/patches/cli_multiparam_parser.cpp
        ../src/engine/backend_selection.cpp
        ../src/engine/render_profile.cpp
        ../src/engine/shim_log_sink.cpp
        ../src/engine/shim_log_client.cpp
        ../src/engine/game_log_path.cpp)
    target_include_directories(openshim_bootstrap_api_tests PRIVATE ../include)
    target_compile_features(openshim_bootstrap_api_tests PRIVATE cxx_std_20)
    target_compile_definitions(openshim_bootstrap_api_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(openshim_bootstrap_api_tests PRIVATE /W4 /WX)
    # cli_multiparam_parser reads the executable's version resource.
    target_link_libraries(openshim_bootstrap_api_tests PRIVATE version)
    add_test(NAME openshim_bootstrap_api_tests COMMAND openshim_bootstrap_api_tests)
endif()

openshim_add_test(render_effect_intent_tests STD 20 SOURCES
    render_effect_intent_tests.cpp
    ../src/engine/render_effect_intent.cpp
)

# Scene-depth qualification bookkeeping (Phase A of the DX11 scene-depth
# work). The hooks live in src/patches/dx11_scene_depth.cpp and need D3D11;
# the part that decides whether a COM address seen before is the same depth
# surface or a recycled allocation does not, so it lives in src/engine and
# runs on the host lane.
openshim_add_test(scene_depth_facts_tests STD 20 SOURCES
    scene_depth_facts_tests.cpp
    ../src/engine/scene_depth_facts.cpp
)

# The frustum-cull / restored-bounds table (audit P1-3): an entry leaves when
# its mesh is destroyed, a reused address with a different identity starts
# over, and deletion is backward-shift so probe chains and headroom survive.
# Header-only and engine-free, so it runs on both lanes.
openshim_add_test(remembered_mesh_bounds_table_tests STD 20 SOURCES
    remembered_mesh_bounds_table_tests.cpp
)

# Shared BZR document pin. Docs/BZR_LUA_AGENT_REFERENCE.md and
# Docs/BZR_PLATFORM_COMPATIBILITY.md must stay byte-identical across
# ExtraUtilities, OpenShim, Campaign Reimagined and bzfile; this fails when the
# local copies drift from the hashes every repository pins. A CMake script, so
# it runs on both CI lanes without a compiler or extra interpreter.
add_test(NAME shared_bzr_docs_check
    COMMAND ${CMAKE_COMMAND} -DREPO_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/..
            -P ${CMAKE_CURRENT_SOURCE_DIR}/shared_bzr_docs_check.cmake
)

# Native meter geometry/provider before build-specific hook qualification.
openshim_add_test(native_hud_layout_tests STD 20 SOURCES
    native_hud_layout_tests.cpp
    ../src/engine/native_hud_layout.cpp
    ../src/patches/native_hud_runtime.cpp
)

if(WIN32 AND MSVC)
    openshim_add_test(live_reticle_team_tests STD 20 SOURCES
        live_reticle_team_tests.cpp
    )
endif()
