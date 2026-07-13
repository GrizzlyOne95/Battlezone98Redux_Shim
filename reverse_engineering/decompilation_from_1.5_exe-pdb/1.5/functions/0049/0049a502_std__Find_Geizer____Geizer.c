/*
 * Entry: 0049a502
 * Name: std::_Find<Geizer_*_*,Geizer_*>
 * Namespace: std
 * Signature: Geizer * * _Find<Geizer_*_*,Geizer_*>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __cdecl
std::_Find<Geizer_*_*,Geizer_*>(Geizer **param_1,Geizer **param_2,Geizer **param_3)

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
