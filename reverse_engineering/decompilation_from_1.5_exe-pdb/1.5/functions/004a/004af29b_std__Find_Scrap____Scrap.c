/*
 * Entry: 004af29b
 * Name: std::_Find<Scrap_*_*,Scrap_*>
 * Namespace: std
 * Signature: Scrap * * _Find<Scrap_*_*,Scrap_*>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __cdecl std::_Find<Scrap_*_*,Scrap_*>(Scrap **param_1,Scrap **param_2,Scrap **param_3)

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
