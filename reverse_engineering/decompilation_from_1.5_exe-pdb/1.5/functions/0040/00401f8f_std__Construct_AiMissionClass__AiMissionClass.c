/*
 * Entry: 00401f8f
 * Name: std::_Construct<AiMissionClass_*,AiMissionClass_*>
 * Namespace: std
 * Signature: void _Construct<AiMissionClass_*,AiMissionClass_*>(AiMissionClass * * param_1, AiMissionClass * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Construct<AiMissionClass_*,AiMissionClass_*>
          (AiMissionClass **param_1,AiMissionClass **param_2)

{
  if (param_1 != (AiMissionClass **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
