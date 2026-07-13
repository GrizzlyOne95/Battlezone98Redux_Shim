/*
 * Entry: 004c7ca8
 * Name: std::_Construct<DisplayInterface_*,DisplayInterface_*>
 * Namespace: std
 * Signature: void _Construct<DisplayInterface_*,DisplayInterface_*>(DisplayInterface * * param_1, DisplayInterface * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Construct<DisplayInterface_*,DisplayInterface_*>
          (DisplayInterface **param_1,DisplayInterface **param_2)

{
  if (param_1 != (DisplayInterface **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
