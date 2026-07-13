/*
 * Entry: 0049a8e6
 * Name: std::fill<Geizer_*_*,Geizer_*>
 * Namespace: std
 * Signature: void fill<Geizer_*_*,Geizer_*>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::fill<Geizer_*_*,Geizer_*>(Geizer **param_1,Geizer **param_2,Geizer **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
