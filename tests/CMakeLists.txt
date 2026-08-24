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
