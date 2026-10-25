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
  [mars]="misn04 misn05 misn06"
  [venus]="misn07 misn08 misn09"
  [io]="misn10 misn11 misns4"
  [europa]="misn12 misn13"
  [titan]="misn14 misn15 misn16 misn15b misn16b"
  [achilles]="misn17 misn18"
)
for w in ${@:-moon mars venus io europa titan achilles}; do
  args=()
  for m in ${MAPS[$w]}; do
    # CR may override only some of a map's files (misn05 ships just its HG2): take each from CR when present.
    # Git Bash leaves paths inside a comma list unconverted, so hand Windows Python mixed-form paths.
    pick() { local f="$STOCK/$m.$1"; [ -f "$CR/$m.$1" ] && f="$CR/$m.$1"; if command -v cygpath >/dev/null; then cygpath -m "$f"; else echo "$f"; fi; }
    if [ -f "$CR/$m.hg2" ] || [ -f "$CR/$m.mat" ]; then
      args+=(--map "$m=$(pick hg2),$(pick mat),$(pick trn)")
      # The stock map gets its own entry only when CR changed its height field or layout.
      cmp -s "$(pick hg2)" "$STOCK/$m.hg2" && cmp -s "$(pick mat)" "$STOCK/$m.mat" && continue
    fi
    [ -f "$STOCK/$m.mat" ] && args+=(--map "${m}_stock=$STOCK/$m")
  done
  echo "=== $w"
  python scripts/Build-TerrainAutoPaint.py --recipe "scripts/terrain-packs/$w-autopaint.json" --source-root "$ART" \
    --output "$OUT/$w-auto" --prefix "openshim_${w}_auto" --force "${args[@]}"
done
