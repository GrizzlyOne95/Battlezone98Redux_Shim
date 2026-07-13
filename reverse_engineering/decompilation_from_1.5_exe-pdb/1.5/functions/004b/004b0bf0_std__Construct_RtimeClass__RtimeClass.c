/*
 * Entry: 004b0bf0
 * Name: std::_Construct<RtimeClass_*,RtimeClass_*>
 * Namespace: std
 * Signature: void _Construct<RtimeClass_*,RtimeClass_*>(RtimeClass * * param_1, RtimeClass * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<RtimeClass_*,RtimeClass_*>(RtimeClass **param_1,RtimeClass **param_2)

{
  if (param_1 != (RtimeClass **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
