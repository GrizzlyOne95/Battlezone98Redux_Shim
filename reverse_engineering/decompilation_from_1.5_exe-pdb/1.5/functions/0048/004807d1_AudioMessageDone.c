/*
 * Entry: 004807d1
 * Name: AudioMessageDone
 * Namespace: Global
 * Signature: int AudioMessageDone(_gas_object * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AudioMessageDone(_gas_object *param_1,long param_2)

{
  int iVar1;
  
  iVar1 = AudioMessageMgr::MessageDone((AudioMessageMgr *)param_1->user,param_1);
  return iVar1;
}
