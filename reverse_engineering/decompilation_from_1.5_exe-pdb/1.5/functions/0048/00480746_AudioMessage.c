/*
 * Entry: 00480746
 * Name: AudioMessage
 * Namespace: Global
 * Signature: int AudioMessage(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AudioMessage(char *param_1)

{
  int iVar1;
  
  iVar1 = AudioMessageMgr::Insert(&msgMgr,param_1);
  return iVar1;
}
