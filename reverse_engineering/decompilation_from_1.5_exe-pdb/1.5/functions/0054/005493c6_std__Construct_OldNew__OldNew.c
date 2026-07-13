/*
 * Entry: 005493c6
 * Name: std::_Construct<OldNew_*,OldNew_*>
 * Namespace: std
 * Signature: void _Construct<OldNew_*,OldNew_*>(OldNew * * param_1, OldNew * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<OldNew_*,OldNew_*>(OldNew **param_1,OldNew **param_2)

{
  if (param_1 != (OldNew **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
