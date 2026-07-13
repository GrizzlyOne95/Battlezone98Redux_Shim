/*
 * Entry: 004800b3
 * Name: std::_Construct<AudMsgInfo_*,AudMsgInfo_*>
 * Namespace: std
 * Signature: void _Construct<AudMsgInfo_*,AudMsgInfo_*>(AudMsgInfo * * param_1, AudMsgInfo * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AudMsgInfo_*,AudMsgInfo_*>(AudMsgInfo **param_1,AudMsgInfo **param_2)

{
  if (param_1 != (AudMsgInfo **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
