/*
 * Entry: 005493b5
 * Name: std::_Construct<Addr_*,Addr_*>
 * Namespace: std
 * Signature: void _Construct<Addr_*,Addr_*>(Addr * * param_1, Addr * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<Addr_*,Addr_*>(Addr **param_1,Addr **param_2)

{
  if (param_1 != (Addr **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
