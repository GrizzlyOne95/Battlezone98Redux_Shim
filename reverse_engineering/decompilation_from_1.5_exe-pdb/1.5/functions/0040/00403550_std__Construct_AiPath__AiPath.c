/*
 * Entry: 00403550
 * Name: std::_Construct<AiPath_*,AiPath_*>
 * Namespace: std
 * Signature: void _Construct<AiPath_*,AiPath_*>(AiPath * * param_1, AiPath * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AiPath_*,AiPath_*>(AiPath **param_1,AiPath **param_2)

{
  if (param_1 != (AiPath **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
