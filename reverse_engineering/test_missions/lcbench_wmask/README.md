# lcbench weaponMask same-class hardpoint matrix

Harness overlay for existing `lcbench` mission. Runner copies `rmwmask.lua` as `addon/lcbench/lcbench.lua` and installs selected ODFs, then launches `lcbench.bzn`.

## Cases

Howitzer (avartl base, mortar class MORT):

- hwh1 single ghartill mask 00001
- hwh2 diff class ghartill+gminigun mask 00011
- hwh3 same 2 ghartill+ghartila mask 00011
- hwh4 reversed ghartila+ghartill mask 00011
- hwh5 mask first  ghartill+ghartila mask 00001
- hwh6 mask second ghartill+ghartila mask 00010
- hwh7 mask both   ghartill+ghartila mask 00011
- hwh8 3 same ghartill+ghartila+ghartmp mask 00111

Minelayer (avmine base, dispenser):

- mnm1 single gproxmin mask 00001
- mnm2 diff class gproxmin+gminigun mask 00011
- mnm3 same 2 gproxmin+gboltmin mask 00011
- mnm4 reversed gboltmin+gproxmin mask 00011
- mnm5 mask first gproxmin+gboltmin mask 00001
- mnm6 mask second gproxmin+gboltmin mask 00010
- mnm7 mask both gproxmin+gboltmin mask 00011

Run:

pwsh -File reverse_engineering/run_lcroad_wmask.ps1 -Cases hwh3 -Repeats 1
pwsh -File reverse_engineering/run_lcroad_wmask.ps1 -All -Repeats 1

Each run logs weaponClass per slot, expectedMask, Attack/LayMines issue, POLL, and created ord counts (shell/shella/grenade/proxmine/boltmine).
