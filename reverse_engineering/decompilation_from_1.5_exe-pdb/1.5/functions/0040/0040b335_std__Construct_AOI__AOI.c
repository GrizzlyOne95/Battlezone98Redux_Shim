/*
 * Entry: 0040b335
 * Name: std::_Construct<AOI_*,AOI_*>
 * Namespace: std
 * Signature: void _Construct<AOI_*,AOI_*>(AOI * * param_1, AOI * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AOI_*,AOI_*>(AOI **param_1,AOI **param_2)

{
  if (param_1 != (AOI **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
