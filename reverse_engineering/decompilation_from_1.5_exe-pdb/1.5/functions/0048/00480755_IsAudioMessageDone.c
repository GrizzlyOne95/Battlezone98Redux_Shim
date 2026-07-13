/*
 * Entry: 00480755
 * Name: IsAudioMessageDone
 * Namespace: Global
 * Signature: bool IsAudioMessageDone(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsAudioMessageDone(int param_1)

{
  bool bVar1;
  
  bVar1 = AudioMessageMgr::IsDone(&msgMgr,param_1);
  return bVar1;
}
