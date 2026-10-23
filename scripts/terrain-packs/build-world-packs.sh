#!/usr/bin/env bash
# Builds the automatic paint packs for the stock worlds (see Docs/terrain-paint.md,
# "World packs"). Each pack covers every Campaign Reimagined mission on that world
# plus the stock mission wherever CR changes its HG2 or MAT.
#
#   scripts/terrain-packs/build-world-packs.sh ART_DIR OUT_DIR [WORLDS...]
#
# ART_DIR holds the recipes' layer archives and matchMean DDS files; OUT_DIR gets one
# <world>-auto directory per world. GAME_DIR (default: the GOG install) and CR_DIR
# (default: the CR Workshop folder inside it) locate the maps; nothing is written there.
set -euo pipefail
ART=${1:?ART_DIR}; OUT=${2:?OUT_DIR}; shift 2
GAME=${GAME_DIR:-"/c/Program Files (x86)/GOG Galaxy/Games/Battlezone 98 Redux"}
CR=${CR_DIR:-"$GAME/mods/3686673790"}
STOCK="$GAME/StockODFFiles"
cd "$(dirname "$0")/../.."
declare -A MAPS=(
  [moon]="misn01 misn02 misn02b misn03 crsetup"
  [venus]="misn07 misn08 misn09"
  [io]="misn10 misn11 misns4"
  [europa]="misn12 misn13"
  [titan]="misn14 misn15 misn16 misn15b misn16b"
  [achilles]="misn17 misn18"
)
for w in ${@:-moon venus io europa titan achilles}; do
  args=()
  for m in ${MAPS[$w]}; do
    [ -f "$CR/$m.mat" ] && args+=(--map "$m=$CR/$m")
    # The stock map gets its own entry only when CR changed its height field or layout.
    if [ -f "$STOCK/$m.mat" ] && ! { [ -f "$CR/$m.hg2" ] && cmp -s "$CR/$m.hg2" "$STOCK/$m.hg2" && cmp -s "$CR/$m.mat" "$STOCK/$m.mat"; }; then
      args+=(--map "${m}_stock=$STOCK/$m")
    fi
  done
  echo "=== $w"
  python scripts/Build-TerrainAutoPaint.py --recipe "scripts/terrain-packs/$w-autopaint.json" --source-root "$ART" \
    --output "$OUT/$w-auto" --prefix "openshim_${w}_auto" --force "${args[@]}"
done
