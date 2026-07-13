/*
 * Entry: 0047c7c2
 * Name: std::_Find<AnimSprite_*_*,AnimSprite_*>
 * Namespace: std
 * Signature: AnimSprite * * _Find<AnimSprite_*_*,AnimSprite_*>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __cdecl
std::_Find<AnimSprite_*_*,AnimSprite_*>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3)

{
  if (param_1 != param_2) {
    do {
      if (*param_1 == *param_3) {
        return param_1;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return param_1;
}
