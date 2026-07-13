/*
 * Entry: 00401f73
 * Name: std::_Construct<AiProcess_*,AiProcess_*>
 * Namespace: std
 * Signature: void _Construct<AiProcess_*,AiProcess_*>(AiProcess * * param_1, AiProcess * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AiProcess_*,AiProcess_*>(AiProcess **param_1,AiProcess **param_2)

{
  if (param_1 != (AiProcess **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
