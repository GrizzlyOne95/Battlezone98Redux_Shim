/*
 * Entry: 0052e024
 * Name: std::_Construct<Explosion_*,Explosion_*>
 * Namespace: std
 * Signature: void _Construct<Explosion_*,Explosion_*>(Explosion * * param_1, Explosion * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<Explosion_*,Explosion_*>(Explosion **param_1,Explosion **param_2)

{
  if (param_1 != (Explosion **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
