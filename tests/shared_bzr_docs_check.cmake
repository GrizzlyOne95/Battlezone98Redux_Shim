# Shared BZR document pin (run as a CTest script: cmake -DREPO_ROOT=<repo> -P).
#
# Docs/BZR_LUA_AGENT_REFERENCE.md and Docs/BZR_PLATFORM_COMPATIBILITY.md must
# stay byte-identical across ExtraUtilities, BZR-OpenShim, Campaign Reimagined
# and bzfile. Each repository pins the same SHA-256 hashes, so an edit made in
# one repository alone fails its CI instead of silently diverging. The same
# check lives in ExtraUtilities' tools/validate_hardening.py
# (check_shared_bzr_docs, GrizzlyOne95/ExtraUtilities#65).
#
# Hash rule: SHA-256 of the file bytes after replacing CRLF with LF, so Windows
# and Linux checkouts agree.

if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "shared_bzr_docs_check.cmake needs -DREPO_ROOT=<repository root>")
endif()

set(_shared_docs
    "Docs/BZR_LUA_AGENT_REFERENCE.md=ed560acf91206732bacb173e3b56ddb501db85f84393bc8f2e89b00ca4df6bca"
    "Docs/BZR_PLATFORM_COMPATIBILITY.md=b9af9f6452996080a046949f3164e102ec8aa4eefaa9d0c4b8d194e52b516fb3"
)

set(_failures "")
foreach(_entry IN LISTS _shared_docs)
    string(FIND "${_entry}" "=" _eq)
    string(SUBSTRING "${_entry}" 0 ${_eq} _rel)
    math(EXPR _hash_start "${_eq} + 1")
    string(SUBSTRING "${_entry}" ${_hash_start} -1 _expected)

    set(_path "${REPO_ROOT}/${_rel}")
    if(NOT EXISTS "${_path}")
        string(APPEND _failures "${_rel}: file is missing.\n")
        continue()
    endif()

    file(READ "${_path}" _content)
    string(REPLACE "\r\n" "\n" _content "${_content}")
    string(SHA256 _actual "${_content}")

    if(_actual STREQUAL _expected)
        message(STATUS "${_rel}: ${_actual} (matches pin)")
    else()
        string(APPEND _failures
            "${_rel}: SHA-256 is ${_actual}, expected ${_expected}. "
            "Make the same change in ExtraUtilities, BZR-OpenShim, Campaign Reimagined and bzfile, "
            "then update the pinned hashes in each repository's check.\n")
    endif()
endforeach()

if(_failures)
    message(FATAL_ERROR "Shared BZR document check failed:\n${_failures}")
endif()
