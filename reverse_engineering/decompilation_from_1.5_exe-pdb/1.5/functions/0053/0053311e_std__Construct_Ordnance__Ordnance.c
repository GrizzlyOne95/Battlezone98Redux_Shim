/*
 * Entry: 0053311e
 * Name: std::_Construct<Ordnance_*,Ordnance_*>
 * Namespace: std
 * Signature: void _Construct<Ordnance_*,Ordnance_*>(Ordnance * * param_1, Ordnance * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<Ordnance_*,Ordnance_*>(Ordnance **param_1,Ordnance **param_2)

{
  if (param_1 != (Ordnance **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
