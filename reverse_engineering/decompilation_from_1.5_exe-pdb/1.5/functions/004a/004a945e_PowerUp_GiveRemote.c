/*
 * Entry: 004a945e
 * Name: PowerUp_GiveRemote
 * Namespace: Global
 * Signature: void PowerUp_GiveRemote(char * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PowerUp_GiveRemote(char *param_1,uint param_2)

{
  GameObject *pGVar1;
  GameObject *pGVar2;
  int iVar3;
  
  if (7 < param_2) {
    pGVar1 = DistributedObject::GetGameObject(*(ulong *)param_1);
    pGVar2 = DistributedObject::GetGameObject(*(ulong *)(param_1 + 4));
    if (((pGVar1 != (GameObject *)0x0) && (pGVar2 != (GameObject *)0x0)) &&
       (iVar3 = (**(code **)(pGVar1->_padding_ + 0x30))(), *(int *)(iVar3 + 0xac) == 3)) {
      (**(code **)(pGVar1->_padding_ + 0x5c))(pGVar2);
    }
  }
  return;
}
