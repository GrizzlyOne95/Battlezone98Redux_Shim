/*
 * Entry: 004a05ee
 * Name: OggManager_Pause
 * Namespace: Global
 * Signature: int OggManager_Pause(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OggManager_Pause(int param_1)

{
  bool bVar1;
  
  bVar1 = OggManager::Pause(param_1);
  return (uint)bVar1;
}
