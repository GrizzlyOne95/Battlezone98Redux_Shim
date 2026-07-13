/*
 * Entry: 004868c4
 * Name: std::_Find<Craft_*_*,Craft_*>
 * Namespace: std
 * Signature: Craft * * _Find<Craft_*_*,Craft_*>(Craft * * param_1, Craft * * param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl std::_Find<Craft_*_*,Craft_*>(Craft **param_1,Craft **param_2,Craft **param_3)

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
