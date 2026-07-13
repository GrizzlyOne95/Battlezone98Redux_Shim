/*
 * Entry: 0048067e
 * Name: SaveAudioMessage
 * Namespace: Global
 * Signature: bool SaveAudioMessage(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl SaveAudioMessage(_iobuf *param_1)

{
  if (!missionSave) {
    AudioMessageMgr::Save(&msgMgr,param_1);
  }
  return true;
}
