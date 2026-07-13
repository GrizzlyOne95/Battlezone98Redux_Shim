/*
 * Entry: 00535373
 * Name: std::fill<OrdnanceClass_*_*,OrdnanceClass_*>
 * Namespace: std
 * Signature: void fill<OrdnanceClass_*_*,OrdnanceClass_*>(OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<OrdnanceClass_*_*,OrdnanceClass_*>
          (OrdnanceClass **param_1,OrdnanceClass **param_2,OrdnanceClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
