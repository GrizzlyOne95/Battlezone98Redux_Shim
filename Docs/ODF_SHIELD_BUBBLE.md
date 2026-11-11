# Shield tower bubble (ODF)

OpenShim lets a `shieldtower` repel on every side instead of only along its
front axis. It is opt-in per ODF and is an OpenShim feature, not stock
behaviour. Status: host-tested math only; not yet live-qualified.

Like the team filter keys (`teamFilter`, `affectAllies`, `affectEnemies`,
listed in the shared `BZR_LUA_AGENT_REFERENCE.md`), these keys are read from any
section of the tower's ODF, usually `[ShieldTowerClass]`:

```ini
[ShieldTowerClass]
shieldPushMode = "radial"
shieldReflectSpeed = 120.0
```

Put no comment on the same line as these keys: the reader does not strip
inline `;` or `//` comments, so `shieldPushMode = "radial" ; x` falls back to
front mode and a commented `shieldReflectSpeed` falls back to 120.

`shieldPushMode` takes `"front"` (default), `"radial"`, `"outward"` or
`"bubble"`. `shieldReflectSpeed` is in m/s, applies in radial mode only, and
`0` turns ricochet off.

Ricochet and push follow the tower's team filter. Without one, the tower
also bounces its own side's shots (a friendly tank firing past the bubble
gets its shot back), so a radial tower normally sets `teamFilter = "enemies"`.

## `shieldPushMode`

- `"front"` (default, and any value OpenShim does not recognise): the stock
  push. Craft and ordnance inside the box are pushed along the tower's front
  axis by `objPush`/`ordPush` (a negative value pushes toward `-front`) and
  damped by `objDrag`/`ordDrag`. Behaviour is unchanged.
- `"radial"` (aliases `"outward"`, `"bubble"`): the push points horizontally
  from the tower to the target, with strength `|objPush|` / `|ordPush|`, so
  the stock negative values repel too. Drag is unchanged. Within 0.5 m of the
  tower's vertical axis the front axis is used instead.
- A shot slower than `shieldReflectSpeed` that is still heading inward has its
  inward velocity cancelled each frame, then gets the outward push, so it
  slides off rather than passing through. `ordPush = 0` turns that off, and
  ricochet too.
- Setting radial mode alone switches the tower onto OpenShim's re-implemented
  Simulate; no team filter is needed. Team filters still apply in radial mode.
- The field is still the stock box (`shieldMinX/Y/Z`, `shieldMaxX/Y/Z`, in the
  tower's local frame), and it still needs a power source. Make the box
  roughly square and centred on the tower for a round bubble.

## `shieldReflectSpeed`

Radial mode only. Blast cannon and bolt shots cross the box in a frame or two,
before the push can turn them. A shot at least this fast (|velocity|, default
120 m/s) that is heading inward and is inside the box now, or will be after
this frame's step (`pos + vel * dt`), is reflected about the outward normal:
`v' = v - 2 * dot(v, n) * n`. Its speed is kept, and it gets no push or drag
that frame. `0` or less turns ricochet off, so every shot uses the push.

Not done, by design or for lack of a verified offset:

- The shot is not moved out of the box; the reflected velocity carries it out
  on the next step.
- The shot's facing matrix is not re-oriented to the new velocity. Whether
  Redux draws trails and sprites from it or from the velocity is UNVERIFIED.

Code: `include/shield_push_mode.h` (math, host-tested by
`tests/shield_push_mode_tests.cpp`) and `RunShieldTowerFilteredSimulate` in
`src/patches/team_filter_mines.cpp`.
