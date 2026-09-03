#!/usr/bin/env bash
#
# One-time developer environment setup for BZR OpenShim.
#
# Performs a sparse checkout of the upstream Ogre 1.10.0 headers used as
# compile-time reference declarations by OpenShim renderer/Ogre work.
#
# The headers are placed under:
#     third_party/ogre-1.10.0-bzr/_work
#
# OpenShim does NOT build or load a replacement OgreMain.dll. Runtime code
# continues to operate against Battlezone 98 Redux's already-loaded
# OgreMain.dll through validated exports, module-relative offsets, and hooks.
#
# The shipped BZR Ogre binary is known to contain ABI drift from pristine
# upstream Ogre 1.10.0. Treat these headers as a source/API reference, not as
# proof that an arbitrary upstream class layout or exported signature is safe.
#
# Notes:
#   - The _work/ directory is gitignored.
#   - The pinned commit matches the Ogre 1.10.0 source reference already used
#     by ExtraUtilities.
#   - Run this script again safely; it is idempotent once the headers exist.

set -euo pipefail

ogre_commit="f1f1937fd6cbad05a4b9170b9882da91f42f53a5"
ogre_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/third_party/ogre-1.10.0-bzr/_work"
header_sentinel="$ogre_dir/OgreMain/include/OgreEntity.h"

if [ -f "$header_sentinel" ]; then
    echo "Ogre reference headers already present at: $ogre_dir"
    echo "Setup complete."
    exit 0
fi

echo "Fetching Ogre 1.10.0 reference headers (sparse checkout)..."
echo "Pinned commit: $ogre_commit"
echo "Target: $ogre_dir"

if ! command -v git >/dev/null 2>&1; then
    echo "error: git was not found on PATH" >&2
    exit 1
fi

if [ ! -d "$ogre_dir" ]; then
    mkdir -p "$ogre_dir"
fi

if [ ! -d "$ogre_dir/.git" ]; then
    git -C "$ogre_dir" init
    git -C "$ogre_dir" remote add origin https://github.com/OGRECave/ogre.git
fi

git -C "$ogre_dir" sparse-checkout init --cone
git -C "$ogre_dir" sparse-checkout set OgreMain/include Components/Overlay/include

git -C "$ogre_dir" fetch --filter=blob:none --depth 1 origin "$ogre_commit"
git -C "$ogre_dir" checkout "$ogre_commit"

echo ""
echo "Done. Ogre reference headers are ready at: $ogre_dir"