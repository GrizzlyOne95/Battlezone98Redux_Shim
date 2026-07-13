/*
 * Entry: 0040414f
 * Name: std::_Construct<AiTask_*,AiTask_*>
 * Namespace: std
 * Signature: void _Construct<AiTask_*,AiTask_*>(AiTask * * param_1, AiTask * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AiTask_*,AiTask_*>(AiTask **param_1,AiTask **param_2)

{
  if (param_1 != (AiTask **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
