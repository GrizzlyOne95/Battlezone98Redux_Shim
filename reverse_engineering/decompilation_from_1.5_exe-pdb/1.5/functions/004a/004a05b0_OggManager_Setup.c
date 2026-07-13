/*
 * Entry: 004a05b0
 * Name: OggManager_Setup
 * Namespace: Global
 * Signature: int OggManager_Setup(char * param_1, uint param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OggManager_Setup(char *param_1,uint param_2,int param_3)

{
  int iVar1;
  
  iVar1 = OggManager::Setup(param_1,param_2,param_3 != 0);
  return iVar1;
}
