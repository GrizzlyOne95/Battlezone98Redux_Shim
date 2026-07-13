/*
 * Entry: 004a060a
 * Name: OggManager_Release
 * Namespace: Global
 * Signature: int OggManager_Release(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OggManager_Release(int param_1)

{
  bool bVar1;
  
  bVar1 = OggManager::Release(param_1);
  return (uint)bVar1;
}
