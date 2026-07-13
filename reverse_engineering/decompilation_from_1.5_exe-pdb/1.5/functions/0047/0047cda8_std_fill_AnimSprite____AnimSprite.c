/*
 * Entry: 0047cda8
 * Name: std::fill<AnimSprite_*_*,AnimSprite_*>
 * Namespace: std
 * Signature: void fill<AnimSprite_*_*,AnimSprite_*>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<AnimSprite_*_*,AnimSprite_*>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
