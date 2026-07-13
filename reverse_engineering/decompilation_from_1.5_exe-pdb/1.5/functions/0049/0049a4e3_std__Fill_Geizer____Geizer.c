/*
 * Entry: 0049a4e3
 * Name: std::_Fill<Geizer_*_*,Geizer_*>
 * Namespace: std
 * Signature: void _Fill<Geizer_*_*,Geizer_*>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Fill<Geizer_*_*,Geizer_*>(Geizer **param_1,Geizer **param_2,Geizer **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
