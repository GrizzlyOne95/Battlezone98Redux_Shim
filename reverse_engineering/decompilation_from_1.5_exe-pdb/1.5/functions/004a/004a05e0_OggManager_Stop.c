/*
 * Entry: 004a05e0
 * Name: OggManager_Stop
 * Namespace: Global
 * Signature: int OggManager_Stop(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OggManager_Stop(int param_1)

{
  bool bVar1;
  
  bVar1 = OggManager::Stop(param_1);
  return (uint)bVar1;
}
