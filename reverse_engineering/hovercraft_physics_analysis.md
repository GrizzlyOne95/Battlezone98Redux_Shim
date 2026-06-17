# Battlezone 98 Redux — HoverCraft Physics Analysis

> Derived from decompiled `battlezone98redux.exe` (1.5 build) via Ghidra PDB-assisted decompilation.
> Source files: `reverse_engineering/decompilation_from_1.5_exe-pdb/clean_pdb_c/functions/0049/`

---

## 1. Parameters (`HoverCraftClass`)

These are loaded per-object from the `.odf` file via `ParameterDB::Get`. The constructor defaults shown below are the **engine defaults**; the values in your `.odf` override them.

| Parameter | Default (engine) | Your ODF | Description |
|---|---|---|---|
| `setAltitude` | `1.0` | `1.0` | Target hover height above terrain (metres) |
| `accelDragStop` | `4.0` | `4.0` | Drag deceleration multiplier when no throttle input |
| `accelDragFull` | `1.0` | `1.0` | Drag deceleration multiplier at full throttle |
| `alphaTrack` | `0.01` | `20.0` | Angular acceleration tracking gain (terrain tilt) |
| `alphaDamp` | `10.0` | `5.0` | Angular velocity damping |
| `pitchPitch` | `3.0` | `0.25` | Pitch authority from pitch input |
| `pitchThrust` | `0.3` | `0.1` | Nose pitch proportional to throttle |
| `rollStrafe` | `0.1` | `0.1` | Roll angle proportional to strafe input |
| `rollSteer` | `0.1` | `0.1` | Roll angle proportional to steer input |
| `velocForward` | `20.0` | `20.0` | Max forward speed (m/s) |
| `velocReverse` | `10.0` | `15.0` | Max reverse speed (m/s) |
| `velocStrafe` | `15.0` | `20.0` | Max strafe speed (m/s) |
| `accelThrust` | `25.0` | `20.0` | Forward/reverse thrust acceleration (m/s²) |
| `accelBrake` | `75.0` | `75.0` | Braking deceleration (m/s²) — active braking authority |
| `omegaSpin` | `4.0` | `3.5` | Max yaw angular velocity (rad/s) when spinning in place |
| `omegaTurn` | `1.5` | `1.5` | Max yaw rate while moving (rad/s) |
| `alphaSteer` | `5.0` | `5.0` | Yaw angular acceleration (torque gain) |
| `accelJump` | `0.1` | `20.0` | Jump thrust impulse magnitude |

---

## 2. Control Inputs (`VHCL_CONTROL`)

The control struct (accessed via `this->vhcl->control`) holds normalised input values written by player or AI:

| Field | Range | Meaning |
|---|---|---|
| `braccel` (offset `+0xBC`) | `[-1, 1]` | Forward/reverse throttle: +1 = full forward, -1 = full reverse |
| `steer` (offset `+0xC0`) | `[-1, 1]` | Yaw (turn left/right) |
| `strafe` (offset `+0xCC`)| `[-1, 1]` | Lateral strafe |
| `pitch` (offset `+0xC8`) | `[-1, 1]` | Pitch (nose up/down) |
| `jump` (offset `+0xD0`) | float | Jump trigger/magnitude |
| `eject` (offset `+0xD4`) | int | Eject flag |
| `deploy` (offset `+0xD8`) | int | Deploy flag |
| `abandon` (offset `+0xDC`) | int | Abandon flag |

The `steer`/`braccel` pair are confirmed live in the Steam build at `GechProcess::*`, accessed via:
```asm
mov ecx, [eax + 0xF4]   ; craft-side vehicle control block
addss xmm0, [eax + 0xBC] ; braccel
addss xmm0, [ecx + 0xC0] ; steer
```

---

## 3. `HoverCraft::Simulate(float dt)` — Step by Step

### 3.1 Initialisation & Parameter Fetch

```c
// Read velocity from physics state
float velX = obj->vel.x;  float velY = obj->vel.y;  float velZ = obj->vel.z;

// Read control inputs
float braccel = control->braccel;  // forward throttle [-1,1]
float steer   = control->steer;    // yaw [-1,1]
float strafe  = control->strafe;   // lateral [-1,1]
float pitch   = control->pitch;    // pitch [-1,1]
bool  jumping = (control->jump != 0);
bool  deploying = (control->deploy != 0);

// Gravity constant used everywhere
const float GRAVITY = 9.8f;

// Performance scalar — scales velocity and acceleration limits
float perf = GetPerformance(this);

// Scaled limits
float maxVelFwd  = velocForward  * perf;
float maxVelRev  = velocReverse  * perf;  // (local_b0)
float maxVelStrf = velocStrafe   * perf;  // (local_b8)
float maxAccThrs = accelThrust   * perf;  // (local_30) — overwritten for hover math
float maxAccBrk  = accelBrake    * perf;  // (local_a4)
float maxOmegSp  = omegaSpin     * perf;  // (local_a8)
float alphaSt    = alphaSteer    * perf;  // (local_bc)
float accJump    = accelJump     * perf;  // (local_cc)
float maxOmTurn  = omegaTurn;             // (local_c8) — NOT scaled in code
float acDragStop = accelDragStop;         // (local_28)
float acDragFull = accelDragFull;         // (local_20)
float alphaTrk   = alphaTrack;            // (local_8)
float alphaDp    = alphaDamp;             // (local_6c)
float pitchPit   = pitchPitch;            // (local_c4)
float pitchThr   = pitchThrust;           // (local_b4)
```

---

### 3.2 Dead State (unit destroyed / `0x200` flag set)

If the object is in the "dead" state (`flags & 0x200`), the simulation instead:

```c
// Simplified physics: gravity only, no hover thrust
accel += GRAVITY * groundNormal;   // normal gravity downward
// Friction against ground: damp velocity proportionally
vel -= vel * (drag * accelDragStop);
// No control inputs applied
throttle = -0.5f;
airBorne = 0.0f;
```

---

### 3.3 Live Hover Physics

#### A) Ground Distance & Normal

```c
// Raycast terrain below craft position to find floor height and surface normal
float floorHeight;
VECTOR_3D floorNormal;
Floor_GetFloor(pos, &floorHeight, &floorNormal);

float heightAboveFloor = pos.y - floorHeight;
```

#### B) Secondary Raycast (obstacle lookahead)

For terrain slope handling, a second floor query is done 0.5 × (forward_look_dir) ahead:
```c
// Look ahead to detect upcoming slopes
VECTOR_3D lookAheadPos = pos + forward * (vel.dot(forward) * 0.5f + 0.5f);
float aheadFloor;
VECTOR_3D aheadNormal;
Floor_GetFloor(lookAheadPos, &aheadFloor, &aheadNormal);

// Use the blended normal for thrust direction
VECTOR_3D blendedNormal = Normalize(floorNormal + aheadNormal);
heightAboveFloor = min(heightAboveFloor, aheadFloor);
```

#### C) Thrust Ratio (height-above-target falloff)

`thrustRatio` is a soft falloff curve — 1.0 at target altitude, dropping to ~0.1 as you go high:

```c
float h = heightAboveFloor / setAltitude;  // normalized height

if (h <= 1.0f)
    thrustRatio = 1.0f;
else
    thrustRatio = 0.9f / ((h-1.0f)*(h-1.0f)*0.25f + 1.0f) + 0.1f;
```

> **Key**: `thrustRatio` scales almost everything below. It's the hover engine's strength.

#### D) Hover Force (anti-gravity)

The hover motor pushes up along the surface normal to counteract gravity:

```c
// hover force = gravity - (PD controller on height error)
float hoverForce = GRAVITY
    - (h - 1.0f) * blendedNormal.y * GRAVITY * 2.0f   // proportional height error
    + dot(vel, blendedNormal) * thrustRatio * (-4.9f); // velocity damping along normal

if (hoverForce > 0.0f) {
    accel += vel_world + hoverForce * blendedNormal;
}
```

Breaking this down:
- `9.8` = base anti-gravity (must counteract Earth-g)
- `(h - 1.0) * blendedNormal.y * 19.6` = PD proportional term: if too high, reduce lift
- `dot(vel, blendedNormal) * thrustRatio * -4.9` = PD derivative term: damp oscillation

#### E) Drag Along Normal Plane

Velocity components along the ground normal are damped:

```c
// damping in ground-normal direction
accel.x -= vel.x * accelDragStop;
accel.z -= vel.z * accelDragStop;
// (only horizontal components, not the vertical which hover handles)
```

Then a "turbo" boost if deploying is active adds an extra kick along the `accelJump` vector:
```c
if (deploying) {
    accel += deployDir * accelJump * thrustRatio;
}

#### F) Velocity Clamping / Speed Limits

Compute desired velocity change from inputs (braccel, strafe):

```c
// Determine which max accel to use based on direction of braccel
float thrustAcc = (braccel > 0) ? maxAccThrs : maxVelRev;

// Target velocity delta
VECTOR_3D dvForward = forward * (thrustAcc * braccel - forwardVelComponent);
VECTOR_3D dvStrafe  = right   * (maxVelStrf * strafe - strafeVelComponent);
VECTOR_3D dv        = CombineVectors(dvForward, dvStrafe);

// Scale to 1/dt (instantaneous accel request)
VECTOR_3D accelRequest = dv * (1.0f / dt);
```

Speed limit enforcement — if the requested new velocity magnitude exceeds the limit:

```c
// Compute max speed for this control state
float speedLimit = (blending between maxVelFwd and maxVelRev based on
                   input + thrustRatio modulation);

// If |accelRequest| within limit: add directly to velocity
// If over: normalize and cap at limit magnitude
if (|accelRequest|^2 <= speedLimit^2) {
    vel += accelRequest * dt;   // direct add
} else {
    vel += Normalize(accelRequest) * speedLimit;  // cap
}
```

The braking contribution is:
```c
// braking drag (decelerates when above speed limit)
float brakeDrag = max(0, -dot(vel, accelRequest) * |vel| * input_magnitude);
```

#### G) Yaw / Angular Velocity

Yaw (steering) is controlled via angular acceleration:

```c
// Target omega (yaw rate)
float omegaTarget = steer * omegaSpin * thrustRatio;

// Angular acceleration to get there
float alphaYaw = (omegaTarget - omega.y) * alphaSteer;

// Pitch/roll from terrain tracking + control:
// alphaDamp damps existing angular velocity
omega -= omega * alphaDamp * dt;

// alphaTrack pulls craft to match terrain normal
// (weighted by thrustRatio — less tracking if airborne)
alpha += (terrainNormal - craftUp) * alphaTrack;

// Control-driven pitching
alpha.x += braccel * pitchThrust * thrustRatio;   // nose pitches with throttle
alpha.x -= pitch   * pitchPitch  * thrustRatio;   // manual pitch input

// Roll from strafe and steering
roll += strafe * rollStrafe;
roll += steer  * rollSteer;
```

#### H) Jump

When `control->jump != 0`:
```c
float jumpVal = control->jump;
// jumpVal * accelJump * perf added as upward impulse
accel.y += jumpVal * accelJump * perf * thrustRatio;
```

> **Note**: `accelJump` in the ODF is the actual jump impulse strength (20.0 in your config).

---

### 3.4 Integration

Position and velocity are updated using a **semi-implicit Euler** integration at half-step:

```c
float half_dt = dt * 0.5f;

// Position updated at half-step (midpoint method)
pos += vel     * half_dt;
pos += accel   * half_dt;   // second half-step

// Orientation quaternion updated similarly
orient += omega * half_dt;
orient += alpha * half_dt;
```

---

## 4. `Craft::Simulate(float dt)` — Base Class

Called at the end of `HoverCraft::Simulate`. Handles:

- **Velocity sanity clamp**: If `|vel| > 1000.0`, scale down to 1000.
- **Terrain bounds clamping**: Position clamped to `[TerMinX..TerMaxX, TerMinZ..TerMaxZ]`.
- **Matrix orthonormalization**: Right/Up/Forward vectors re-orthonormalized each frame via `Cross_Product` + `Normalize_Vector`.
- **Death handling**: Eject flag, abandon flag, destruction explosion, fragment spawning.
- **AI callbacks**: `CallAI`, team slot management.

---

## 5. `HoverCraft::ControlSpeed(float desiredSpeed)` / `ControlForward()`

Helper functions the AI uses to set speed rather than raw braccel:

```c
// ControlSpeed: computes braccel from desired speed vs current speed
float currentFwdSpeed = dot(vel, forward);
float error = (desiredSpeed - currentFwdSpeed) * 0.2f;
control->braccel = Clamp(error, -1.0f, 1.0f);
control->strafe  = 0;   // clears strafe

// ControlForward: if moving backwards, apply full forward to flip direction
if (dot(vel, forward) < -0.1f) {
    control->braccel = 1.0f;   // 0x3f800000 = 1.0f in hex
    control->strafe  = 0;
    return true;
}
```

---

## 6. Summary — Port-to-Another-Engine Checklist

| System | Formula | Key Parameters |
|---|---|---|
| **Hover height** | PD controller: `F = g - K_p*(h-1)*ny - K_d*dot(v,n)*tratio` | `setAltitude`, `GRAVITY=9.8` |
| **Thrust ratio falloff** | `tratio = 0.9/(((h-1)^2 * 0.25)+1) + 0.1` (when h>1), else 1.0 | `setAltitude` |
| **Forward accel** | `accelThrust * perf * braccel` (m/s²) | `accelThrust`, `velocForward` |
| **Reverse accel** | `velocReverse * perf * braccel` (m/s²) | `velocReverse` |
| **Strafe accel** | `velocStrafe * perf * strafe` (m/s²) | `velocStrafe` |
| **Speed cap** | Velocity normalized + capped per-axis per input | `velocForward/Reverse/Strafe` |
| **Braking drag** | Proportional drag, scaled by `accelDragStop` (no throttle) or `accelDragFull` (full throttle) | `accelDragStop`, `accelDragFull` |
| **Yaw rate** | `omegaSpin * tratio * steer` → driven via `alphaSteer` angular accel | `omegaSpin`, `omegaTurn`, `alphaSteer` |
| **Terrain normal tracking** | Angular impulse toward terrain normal, scaled by `alphaTrack` | `alphaTrack`, `alphaDamp` |
| **Nose pitch** | `braccel * pitchThrust + pitch_input * pitchPitch` | `pitchThrust`, `pitchPitch` |
| **Roll** | `strafe * rollStrafe + steer * rollSteer` | `rollStrafe`, `rollSteer` |
| **Jump** | `accelJump * perf * jump_input` upward impulse | `accelJump` |
| **Integration** | Semi-implicit Euler, half-step: `pos += vel*dt*0.5 + accel*dt*0.5` | `dt` |
| **Gravity** | Hard-coded `9.8 m/s²` downward | — |

### Hover PD Constants (hardcoded, not in ODF)

| Constant | Value | Role |
|---|---|---|
| Gravity | `9.8` | Baseline lift requirement |
| Height PD K_p | `19.6` (= 2×g) | Proportional height correction |
| Height PD K_d | `-4.9` (= -0.5×g) | Velocity damping along normal |
| Braking drag scale | `12.0` (at/below floor) → `2.0` (airborne) | Ground contact braking |
| Speed limit blend | `0.9 / (x²*0.25 + 1) + 0.1` | Soft cap curve |

---

## 7. Object Struct Layout (partial, from probe data)

```
VHCL_CONTROL (accessed via obj->vhcl->control):
  +0xBC  steer    (float)   — confirmed live
  +0xC0  braccel  (float)   — confirmed live
  +0xC4  (pad/flags)
  +0xC8  pitch    (float)
  +0xCC  strafe   (float)
  +0xD0  jump     (float)
  +0xD4  eject    (int)
  +0xD8  deploy   (int)
  +0xDC  abandon  (int)

HoverCraft additional fields:
  throttle   — float, reported to HoverInterface (0 = idle, 3 = deploy)
  airBorne   — float [0,1], 1.0 = fully airborne (1-thrustRatio clamped)
  thrustRatio — float [0.1, 1.0], hover engine strength
  hi         — HoverInterface*, if non-null gets a debug/telemetry snapshot each frame

Pointer chain for AI control:
  obj->vhcl->control  [direct control struct]
  obj + 0xF4          [pointer to second craft/vehicle state block consumed by GechProcess AI]
```
