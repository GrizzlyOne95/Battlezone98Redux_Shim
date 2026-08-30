cmake_minimum_required(VERSION 3.20)
project(BzrNetProtocolTests LANGUAGES CXX)

enable_testing()

add_executable(bzrnet_protocol_tests
    bzrnet_protocol_tests.cpp
    ../src/patches/bzrnet_protocol.cpp
)

target_include_directories(bzrnet_protocol_tests PRIVATE ../include)
target_compile_features(bzrnet_protocol_tests PRIVATE cxx_std_20)

add_executable(shim_log_tests
    shim_log_tests.cpp
    ../src/engine/shim_log.cpp
)

add_executable(trn_codec_tests
    trn_codec_tests.cpp
    ../src/patches/trn_codec.cpp
)

target_include_directories(trn_codec_tests PRIVATE ../include)
target_compile_features(trn_codec_tests PRIVATE cxx_std_20)

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

add_executable(chunk_batch_invalidation_tests
    chunk_batch_invalidation_tests.cpp
)

add_executable(sun_flash_tests
    sun_flash_tests.cpp
)

add_executable(terrain_tile_blend_tests
    terrain_tile_blend_tests.cpp
)

add_executable(resolve_table_tests
    resolve_table_tests.cpp
    ../src/engine/resolve_table.cpp
)

add_executable(openshim_update_manifest_tests
    openshim_update_manifest_tests.cpp
    ../src/patches/openshim_update_manifest.cpp
)

add_executable(ai_range_policy_tests
    ai_range_policy_tests.cpp
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
target_include_directories(chunk_batch_invalidation_tests PRIVATE ../include)
target_compile_features(chunk_batch_invalidation_tests PRIVATE cxx_std_20)
target_include_directories(sun_flash_tests PRIVATE ../include)
target_compile_features(sun_flash_tests PRIVATE cxx_std_20)
target_include_directories(terrain_tile_blend_tests PRIVATE ../include)
target_compile_features(terrain_tile_blend_tests PRIVATE cxx_std_20)
target_include_directories(resolve_table_tests PRIVATE ../include ../third_party)
target_compile_features(resolve_table_tests PRIVATE cxx_std_20)
target_include_directories(openshim_update_manifest_tests PRIVATE ../include)
target_compile_features(openshim_update_manifest_tests PRIVATE cxx_std_20)
target_include_directories(ai_range_policy_tests PRIVATE ../include)
target_compile_features(ai_range_policy_tests PRIVATE cxx_std_20)
# Point the test at the patches.json the game will actually load, so the
# migrated signatures are checked against the shipped artifact and not only
# against a copy embedded in the test.
target_compile_definitions(resolve_table_tests PRIVATE
    BZR_PATCHES_JSON="${CMAKE_CURRENT_SOURCE_DIR}/../scripts/patches.json")

if(MSVC)
    target_compile_options(bzrnet_protocol_tests PRIVATE /W4 /WX)
    target_compile_options(shim_log_tests PRIVATE /W4 /WX)
    target_compile_options(trn_codec_tests PRIVATE /W4 /WX)
    target_compile_options(numeric_locale_compat_tests PRIVATE /W4 /WX)
    target_compile_options(native_ui_validation_tests PRIVATE /W4 /WX)
    target_compile_options(enhanced_light_selection_tests PRIVATE /W4 /WX)
    target_compile_options(enhanced_light_selection_bench PRIVATE /W4 /WX)
    target_compile_options(weapon_convergence_tests PRIVATE /W4 /WX)
    target_compile_options(headlight_falloff_tests PRIVATE /W4 /WX)
    target_compile_options(chunk_batch_invalidation_tests PRIVATE /W4 /WX)
    target_compile_options(sun_flash_tests PRIVATE /W4 /WX)
    target_compile_options(terrain_tile_blend_tests PRIVATE /W4 /WX)
    target_compile_options(resolve_table_tests PRIVATE /W4 /WX)
    target_compile_options(openshim_update_manifest_tests PRIVATE /W4 /WX)
    target_compile_options(ai_range_policy_tests PRIVATE /W4 /WX)
else()
    target_compile_options(bzrnet_protocol_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(shim_log_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(trn_codec_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(numeric_locale_compat_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(native_ui_validation_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(enhanced_light_selection_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(enhanced_light_selection_bench PRIVATE -Wall -Wextra -Werror)
    target_compile_options(weapon_convergence_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(headlight_falloff_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(chunk_batch_invalidation_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(sun_flash_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(terrain_tile_blend_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(resolve_table_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(openshim_update_manifest_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(ai_range_policy_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_test(NAME bzrnet_protocol_tests COMMAND bzrnet_protocol_tests)
add_test(NAME shim_log_tests COMMAND shim_log_tests)
add_test(NAME trn_codec_tests COMMAND trn_codec_tests)
add_test(NAME numeric_locale_compat_tests COMMAND numeric_locale_compat_tests)
add_test(NAME native_ui_validation_tests COMMAND native_ui_validation_tests)
add_test(NAME enhanced_light_selection_tests COMMAND enhanced_light_selection_tests)
add_test(NAME weapon_convergence_tests COMMAND weapon_convergence_tests)
add_test(NAME headlight_falloff_tests COMMAND headlight_falloff_tests)
add_test(NAME chunk_batch_invalidation_tests COMMAND chunk_batch_invalidation_tests)
add_test(NAME sun_flash_tests COMMAND sun_flash_tests)
add_test(NAME terrain_tile_blend_tests COMMAND terrain_tile_blend_tests)
add_test(NAME resolve_table_tests COMMAND resolve_table_tests)
add_test(NAME openshim_update_manifest_tests COMMAND openshim_update_manifest_tests)
add_test(NAME ai_range_policy_tests COMMAND ai_range_policy_tests)

target_include_directories(render_profile_tests PRIVATE ../include)
target_compile_features(render_profile_tests PRIVATE cxx_std_20)
target_include_directories(request_apply_tracker_tests PRIVATE ../include)
target_compile_features(request_apply_tracker_tests PRIVATE cxx_std_20)
target_include_directories(render_profile_resources_tests PRIVATE ../include)
target_compile_features(render_profile_resources_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(render_profile_tests PRIVATE /W4 /WX)
    target_compile_options(request_apply_tracker_tests PRIVATE /W4 /WX)
    target_compile_options(render_profile_resources_tests PRIVATE /W4 /WX)
else()
    target_compile_options(render_profile_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(request_apply_tracker_tests PRIVATE -Wall -Wextra -Werror)
    target_compile_options(render_profile_resources_tests PRIVATE -Wall -Wextra -Werror)
endif()

add_test(NAME render_profile_tests COMMAND render_profile_tests)
add_test(NAME request_apply_tracker_tests COMMAND request_apply_tracker_tests)
add_test(NAME render_profile_resources_tests COMMAND render_profile_resources_tests)

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
