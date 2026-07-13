/*
 * Entry: 00535081
 * Name: std::_Fill<OrdnanceClass_*_*,OrdnanceClass_*>
 * Namespace: std
 * Signature: void _Fill<OrdnanceClass_*_*,OrdnanceClass_*>(OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<OrdnanceClass_*_*,OrdnanceClass_*>
          (OrdnanceClass **param_1,OrdnanceClass **param_2,OrdnanceClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
