/*
 * Entry: 00480698
 * Name: LoadAudioMessage
 * Namespace: Global
 * Signature: bool LoadAudioMessage(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl LoadAudioMessage(_iobuf *param_1)

{
  if ((!missionSave) && (0x3ff < version)) {
    AudioMessageMgr::Load(&msgMgr,param_1);
  }
  return true;
}
