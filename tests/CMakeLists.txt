cmake_minimum_required(VERSION 3.20)
project(BzrNetProtocolTests LANGUAGES CXX)

# Linux CMake/CTest harness for the engine-independent unit tests. Every
# target here is a self-contained executable (no game engine linkage) so the
# suite can be configured, built, and run with plain CMake + CTest:
#   cmake -S tests -B tests/build && cmake --build tests/build -j && ctest --test-dir tests/build --output-on-failure
enable_testing()

add_executable(bzrnet_protocol_tests
    bzrnet_protocol_tests.cpp
    ../src/patches/bzrnet_protocol.cpp
)

target_include_directories(bzrnet_protocol_tests PRIVATE ../include)
target_compile_features(bzrnet_protocol_tests PRIVATE cxx_std_20)

add_executable(shim_log_tests
    shim_log_tests.cpp
    ../src/engine/shim_log_sink.cpp
    ../src/engine/shim_log_client.cpp
    ../src/engine/game_log_path.cpp
)

add_executable(bzloader_catalog_tests
    bzloader_catalog_tests.cpp
    ../src/loader/bzloader_catalog.cpp
)
target_include_directories(bzloader_catalog_tests PRIVATE ../include)
target_compile_features(bzloader_catalog_tests PRIVATE cxx_std_20)

add_executable(trn_codec_tests
    trn_codec_tests.cpp
    ../src/patches/trn_codec.cpp
)

target_include_directories(trn_codec_tests PRIVATE ../include)
target_compile_features(trn_codec_tests PRIVATE cxx_std_20)

add_executable(bzn_analysis_tests
    bzn_analysis_tests.cpp
)

target_include_directories(bzn_analysis_tests PRIVATE ../include)
target_compile_features(bzn_analysis_tests PRIVATE cxx_std_20)

add_executable(bzn_filename_identity_tests
    bzn_filename_identity_tests.cpp
)
target_include_directories(bzn_filename_identity_tests PRIVATE ../include)
target_compile_features(bzn_filename_identity_tests PRIVATE cxx_std_20)

add_executable(bzn_save_path_tests
    bzn_save_path_tests.cpp
)

target_include_directories(bzn_save_path_tests PRIVATE ../include)
target_compile_features(bzn_save_path_tests PRIVATE cxx_std_20)

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

add_executable(numeric_locale_compat_tests
    numeric_locale_compat_tests.cpp
    ../src/patches/numeric_locale_compat.cpp
)

target_include_directories(numeric_locale_compat_tests PRIVATE ../include)
target_compile_features(numeric_locale_compat_tests PRIVATE cxx_std_20)

add_executable(native_ui_validation_tests
    native_ui_validation_tests.cpp
)

add_executable(enhanced_light_selection_tests
    enhanced_light_selection_tests.cpp
    ../src/engine/enhanced_light_selection.cpp
)

add_executable(enhanced_light_selection_bench
    enhanced_light_selection_bench.cpp
    ../src/engine/enhanced_light_selection.cpp
)

add_executable(weapon_convergence_tests
    weapon_convergence_tests.cpp
)

add_executable(headlight_falloff_tests
    headlight_falloff_tests.cpp
)

add_executable(shadow_far_distance_tests
    shadow_far_distance_tests.cpp
)

add_executable(chunk_batch_invalidation_tests
    chunk_batch_invalidation_tests.cpp
)

add_executable(sun_flash_tests
    sun_flash_tests.cpp
)

add_executable(terrain_tile_blend_tests
    terrain_tile_blend_tests.cpp
)

add_executable(terrain_atlas_rect_repair_tests
    terrain_atlas_rect_repair_tests.cpp
    ../src/patches/terrain_atlas_rect_repair.cpp
)

add_executable(resolve_table_tests
    resolve_table_tests.cpp
    ../src/engine/resolve_table.cpp
)

# Pins the GameObject/Ordnance field offsets that the runtime hooks read. Pure
# header constants, so it needs no engine code and runs on the Linux host lane.
add_executable(object_layout_tests
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
    BZR_PATCHER_CPP="${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/patcher.cpp"
    BZR_BZR_HOOKS_CPP="${CMAKE_CURRENT_SOURCE_DIR}/../src/patches/bzr_hooks.cpp"
    BZR_SDK_PROVIDER_CPP="${CMAKE_CURRENT_SOURCE_DIR}/../src/patches/openshim_sdk_provider.cpp")

# Pins the x86-32 length decoder that InstallInlineDetour32 uses to refuse
# steals that split an instruction. Pure byte tables, no engine code.
add_executable(x86_length_tests
    x86_length_tests.cpp
    ../src/engine/x86_length.cpp
)
target_include_directories(x86_length_tests PRIVATE ../include)
target_compile_features(x86_length_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(x86_length_tests PRIVATE /W4 /WX)
else()
    target_compile_options(x86_length_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_executable(openshim_update_manifest_tests
    openshim_update_manifest_tests.cpp
    ../src/patches/openshim_update_manifest.cpp
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

add_executable(ai_range_policy_tests
    ai_range_policy_tests.cpp
)

add_executable(lcbench_safety_policy_tests
    lcbench_safety_policy_tests.cpp
)

add_executable(autosave_gate_tests
    autosave_gate_tests.cpp
)

add_executable(native_save_flag_tests
    native_save_flag_tests.cpp
)

add_executable(render_profile_tests
    render_profile_tests.cpp
    ../src/engine/render_profile.cpp
)

add_executable(request_apply_tracker_tests
    request_apply_tracker_tests.cpp
)

add_executable(render_profile_resources_tests
    render_profile_resources_tests.cpp
    ../src/engine/render_profile_resources.cpp
)

add_executable(dx11_legacy_material_compat_tests
    dx11_legacy_material_compat_tests.cpp
    ../src/engine/dx11_legacy_material_compat.cpp
)

add_executable(openshim_assets_tests
    openshim_assets_tests.cpp
    ../src/engine/openshim_assets.cpp
    ../src/engine/render_profile_resources.cpp
    ../src/engine/shim_log_sink.cpp
    ../src/engine/shim_log_client.cpp
    ../src/engine/game_log_path.cpp
)

target_include_directories(shim_log_tests PRIVATE ../include)
target_compile_features(shim_log_tests PRIVATE cxx_std_20)
target_compile_features(native_ui_validation_tests PRIVATE cxx_std_20)
target_include_directories(enhanced_light_selection_tests PRIVATE ../include)
target_include_directories(enhanced_light_selection_bench PRIVATE ../include)
target_compile_features(enhanced_light_selection_tests PRIVATE cxx_std_20)
target_compile_features(enhanced_light_selection_bench PRIVATE cxx_std_20)
target_include_directories(weapon_convergence_tests PRIVATE ../include)
target_compile_features(weapon_convergence_tests PRIVATE cxx_std_20)
target_include_directories(headlight_falloff_tests PRIVATE ../include)
target_compile_features(headlight_falloff_tests PRIVATE cxx_std_20)
target_include_directories(shadow_far_distance_tests PRIVATE ../include)
target_compile_features(shadow_far_distance_tests PRIVATE cxx_std_20)
target_include_directories(chunk_batch_invalidation_tests PRIVATE ../include)
target_compile_features(chunk_batch_invalidation_tests PRIVATE cxx_std_20)
target_include_directories(sun_flash_tests PRIVATE ../include)
target_compile_features(sun_flash_tests PRIVATE cxx_std_20)
target_include_directories(terrain_tile_blend_tests PRIVATE ../include)
target_compile_features(terrain_tile_blend_tests PRIVATE cxx_std_20)
target_include_directories(terrain_atlas_rect_repair_tests PRIVATE ../include)
target_compile_features(terrain_atlas_rect_repair_tests PRIVATE cxx_std_20)
target_include_directories(resolve_table_tests PRIVATE ../include ../third_party)
target_compile_features(resolve_table_tests PRIVATE cxx_std_20)
target_include_directories(object_layout_tests PRIVATE ../include)
target_compile_features(object_layout_tests PRIVATE cxx_std_20)
target_include_directories(openshim_update_manifest_tests PRIVATE ../include)
target_compile_features(openshim_update_manifest_tests PRIVATE cxx_std_20)
target_include_directories(ai_range_policy_tests PRIVATE ../include)
target_compile_features(ai_range_policy_tests PRIVATE cxx_std_20)
target_include_directories(lcbench_safety_policy_tests PRIVATE ../include)
target_compile_features(lcbench_safety_policy_tests PRIVATE cxx_std_20)
target_include_directories(autosave_gate_tests PRIVATE ../include)
target_compile_features(autosave_gate_tests PRIVATE cxx_std_20)
target_include_directories(native_save_flag_tests PRIVATE ../include)
target_compile_features(native_save_flag_tests PRIVATE cxx_std_20)
# Point the test at the patches.json the game will actually load, so the
# migrated signatures are checked against the shipped artifact and not only
# against a copy embedded in the test.
target_compile_definitions(resolve_table_tests PRIVATE
    BZR_PATCHES_JSON="${CMAKE_CURRENT_SOURCE_DIR}/../scripts/patches.json")

if(MSVC)
    target_compile_options(bzrnet_protocol_tests PRIVATE /W4 /WX)
    target_compile_options(shim_log_tests PRIVATE /W4 /WX)
    target_compile_options(bzloader_catalog_tests PRIVATE /W4 /WX)
    target_compile_options(trn_codec_tests PRIVATE /W4 /WX)
    target_compile_options(bzn_save_path_tests PRIVATE /W4 /WX)
    target_compile_options(bzn_analysis_tests PRIVATE /W4 /WX)
    target_compile_options(bzn_filename_identity_tests PRIVATE /W4 /WX)
    target_compile_options(numeric_locale_compat_tests PRIVATE /W4 /WX)
    target_compile_options(native_ui_validation_tests PRIVATE /W4 /WX)
    target_compile_options(enhanced_light_selection_tests PRIVATE /W4 /WX)
    target_compile_options(enhanced_light_selection_bench PRIVATE /W4 /WX)
    target_compile_options(weapon_convergence_tests PRIVATE /W4 /WX)
    target_compile_options(headlight_falloff_tests PRIVATE /W4 /WX)
    target_compile_options(shadow_far_distance_tests PRIVATE /W4 /WX)
    target_compile_options(chunk_batch_invalidation_tests PRIVATE /W4 /WX)
    target_compile_options(sun_flash_tests PRIVATE /W4 /WX)
    target_compile_options(terrain_tile_blend_tests PRIVATE /W4 /WX)
    target_compile_options(terrain_atlas_rect_repair_tests PRIVATE /W4 /WX)
    target_compile_options(resolve_table_tests PRIVATE /W4 /WX)
    target_compile_options(object_layout_tests PRIVATE /W4 /WX)
    target_compile_options(patch_registration_tests PRIVATE /W4 /WX)
    target_compile_options(openshim_update_manifest_tests PRIVATE /W4 /WX)
    target_compile_options(ai_range_policy_tests PRIVATE /W4 /WX)
    target_compile_options(lcbench_safety_policy_tests PRIVATE /W4 /WX)
    target_compile_options(autosave_gate_tests PRIVATE /W4 /WX)
    target_compile_options(native_save_flag_tests PRIVATE /W4 /WX)
else()
    target_compile_options(bzrnet_protocol_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(shim_log_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(bzloader_catalog_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(trn_codec_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(bzn_save_path_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(bzn_analysis_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(bzn_filename_identity_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(numeric_locale_compat_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(native_ui_validation_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(enhanced_light_selection_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(enhanced_light_selection_bench PRIVATE -Wall -Wextra -Werror)
    target_compile_options(weapon_convergence_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(headlight_falloff_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(chunk_batch_invalidation_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(sun_flash_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(terrain_tile_blend_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(terrain_atlas_rect_repair_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(resolve_table_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(object_layout_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(patch_registration_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(openshim_update_manifest_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(ai_range_policy_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(lcbench_safety_policy_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(autosave_gate_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(native_save_flag_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_test(NAME bzrnet_protocol_tests COMMAND bzrnet_protocol_tests)
add_test(NAME shim_log_tests COMMAND shim_log_tests)
add_test(NAME bzloader_catalog_tests COMMAND bzloader_catalog_tests)
add_test(NAME shadow_far_distance_tests COMMAND shadow_far_distance_tests)
add_test(NAME trn_codec_tests COMMAND trn_codec_tests)
add_test(NAME bzn_save_path_tests COMMAND bzn_save_path_tests)
add_test(NAME bzn_analysis_tests COMMAND bzn_analysis_tests)
add_test(NAME bzn_filename_identity_tests COMMAND bzn_filename_identity_tests)
add_test(NAME numeric_locale_compat_tests COMMAND numeric_locale_compat_tests)
add_test(NAME native_ui_validation_tests COMMAND native_ui_validation_tests)
add_test(NAME enhanced_light_selection_tests COMMAND enhanced_light_selection_tests)
add_test(NAME weapon_convergence_tests COMMAND weapon_convergence_tests)
add_test(NAME headlight_falloff_tests COMMAND headlight_falloff_tests)
add_test(NAME chunk_batch_invalidation_tests COMMAND chunk_batch_invalidation_tests)
add_test(NAME sun_flash_tests COMMAND sun_flash_tests)
add_test(NAME terrain_tile_blend_tests COMMAND terrain_tile_blend_tests)
add_test(NAME terrain_atlas_rect_repair_tests COMMAND terrain_atlas_rect_repair_tests)
add_test(NAME resolve_table_tests COMMAND resolve_table_tests)
add_test(NAME object_layout_tests COMMAND object_layout_tests)
add_test(NAME patch_registration_tests COMMAND patch_registration_tests)
add_test(NAME openshim_update_manifest_tests COMMAND openshim_update_manifest_tests)
add_test(NAME patch_config_parse_tests COMMAND patch_config_parse_tests)
add_test(NAME ai_range_policy_tests COMMAND ai_range_policy_tests)
add_test(NAME lcbench_safety_policy_tests COMMAND lcbench_safety_policy_tests)
add_test(NAME autosave_gate_tests COMMAND autosave_gate_tests)
add_test(NAME native_save_flag_tests COMMAND native_save_flag_tests)
add_test(NAME x86_length_tests COMMAND x86_length_tests)

target_include_directories(render_profile_tests PRIVATE ../include)
target_compile_features(render_profile_tests PRIVATE cxx_std_20)
target_include_directories(request_apply_tracker_tests PRIVATE ../include)
target_compile_features(request_apply_tracker_tests PRIVATE cxx_std_20)
target_include_directories(render_profile_resources_tests PRIVATE ../include)
target_compile_features(render_profile_resources_tests PRIVATE cxx_std_20)
target_include_directories(dx11_legacy_material_compat_tests PRIVATE ../include)
target_compile_features(dx11_legacy_material_compat_tests PRIVATE cxx_std_20)
target_include_directories(openshim_assets_tests PRIVATE ../include)
target_compile_features(openshim_assets_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(render_profile_tests PRIVATE /W4 /WX)
    target_compile_options(request_apply_tracker_tests PRIVATE /W4 /WX)
    target_compile_options(render_profile_resources_tests PRIVATE /W4 /WX)
    target_compile_options(dx11_legacy_material_compat_tests PRIVATE /W4 /WX)
    target_compile_options(openshim_assets_tests PRIVATE /W4 /WX)
else()
    target_compile_options(render_profile_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(request_apply_tracker_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(render_profile_resources_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(dx11_legacy_material_compat_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(openshim_assets_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_test(NAME render_profile_tests COMMAND render_profile_tests)
add_test(NAME request_apply_tracker_tests COMMAND request_apply_tracker_tests)
add_test(NAME render_profile_resources_tests COMMAND render_profile_resources_tests)
add_test(NAME dx11_legacy_material_compat_tests COMMAND dx11_legacy_material_compat_tests)
add_test(NAME openshim_assets_tests COMMAND openshim_assets_tests)

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

add_executable(player_kill_trace_tests
    player_kill_trace_tests.cpp
)
target_compile_features(player_kill_trace_tests PRIVATE cxx_std_20)
target_include_directories(player_kill_trace_tests PRIVATE ../include)
if(MSVC)
    target_compile_options(player_kill_trace_tests PRIVATE /W4 /WX)
else()
    target_compile_options(player_kill_trace_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME player_kill_trace_tests COMMAND player_kill_trace_tests)

add_executable(fog_wake_tests
    fog_wake_tests.cpp
    ../src/engine/fog_wake.cpp
)
target_compile_features(fog_wake_tests PRIVATE cxx_std_20)
target_include_directories(fog_wake_tests PRIVATE ../include)
if(MSVC)
    target_compile_options(fog_wake_tests PRIVATE /W4 /WX)
else()
    target_compile_options(fog_wake_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME fog_wake_tests COMMAND fog_wake_tests)

add_executable(fog_wake_runtime_tests
    fog_wake_runtime_tests.cpp
    ../src/engine/fog_wake_runtime.cpp
    ../src/engine/fog_wake.cpp
)
target_compile_features(fog_wake_runtime_tests PRIVATE cxx_std_20)
target_include_directories(fog_wake_runtime_tests PRIVATE ../include)
if(MSVC)
    target_compile_options(fog_wake_runtime_tests PRIVATE /W4 /WX)
else()
    target_compile_options(fog_wake_runtime_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME fog_wake_runtime_tests COMMAND fog_wake_runtime_tests)

add_executable(odf_compat_tests
    odf_compat_tests.cpp
    ../src/patches/odf_compat.cpp
)
target_compile_features(odf_compat_tests PRIVATE cxx_std_20)
target_include_directories(odf_compat_tests PRIVATE ../include)
if(MSVC)
    target_compile_options(odf_compat_tests PRIVATE /W4 /WX)
else()
    target_compile_options(odf_compat_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME odf_compat_tests COMMAND odf_compat_tests)

add_executable(enhanced_resource_bootstrap_tests
    enhanced_resource_bootstrap_tests.cpp
    ../src/engine/enhanced_resource_bootstrap.cpp
)

target_include_directories(enhanced_resource_bootstrap_tests PRIVATE ../include)
target_compile_features(enhanced_resource_bootstrap_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(enhanced_resource_bootstrap_tests PRIVATE /W4 /WX)
else()
    target_compile_options(enhanced_resource_bootstrap_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME enhanced_resource_bootstrap_tests COMMAND enhanced_resource_bootstrap_tests)

# Regression: the ODF item-hook trampoline must relocate whole instructions.
# Relocating five bytes split `mov eax,[ebp+8]` and made the trampoline eat its
# own return jump, which broke every engine item read and stopped the game
# loading any mission. Header-only and engine-free, so it runs anywhere.
add_executable(odf_item_prologue_tests
    odf_item_prologue_tests.cpp
)
target_include_directories(odf_item_prologue_tests PRIVATE ../include)
target_compile_features(odf_item_prologue_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(odf_item_prologue_tests PRIVATE /W4 /WX)
else()
    target_compile_options(odf_item_prologue_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME odf_item_prologue_tests COMMAND odf_item_prologue_tests)
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

add_executable(render_effect_intent_tests
    render_effect_intent_tests.cpp
    ../src/engine/render_effect_intent.cpp
)
target_include_directories(render_effect_intent_tests PRIVATE ../include)
target_compile_features(render_effect_intent_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(render_effect_intent_tests PRIVATE /W4 /WX)
else()
    target_compile_options(render_effect_intent_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME render_effect_intent_tests COMMAND render_effect_intent_tests)

# Scene-depth qualification bookkeeping (Phase A of the DX11 scene-depth
# work). The hooks live in src/patches/dx11_scene_depth.cpp and need D3D11;
# the part that decides whether a COM address seen before is the same depth
# surface or a recycled allocation does not, so it lives in src/engine and
# runs on the host lane.
add_executable(scene_depth_facts_tests
    scene_depth_facts_tests.cpp
    ../src/engine/scene_depth_facts.cpp
)
target_include_directories(scene_depth_facts_tests PRIVATE ../include)
target_compile_features(scene_depth_facts_tests PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(scene_depth_facts_tests PRIVATE /W4 /WX)
else()
    target_compile_options(scene_depth_facts_tests PRIVATE -Wall -Wextra -Werror)
endif()
add_test(NAME scene_depth_facts_tests COMMAND scene_depth_facts_tests)
