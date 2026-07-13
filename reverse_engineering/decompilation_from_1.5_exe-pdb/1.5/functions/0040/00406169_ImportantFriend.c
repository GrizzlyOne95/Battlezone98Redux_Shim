/*
 * Entry: 00406169
 * Name: ImportantFriend
 * Namespace: Global
 * Signature: bool ImportantFriend(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl ImportantFriend(GameObject *param_1,GameObject *param_2)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  AiProcess *pAVar4;
  GameObject *unaff_EDI;
  
  piVar1 = &unaff_EDI->_padding_;
  iVar3 = (**(code **)(*piVar1 + 0x30))();
  iVar3 = *(int *)(iVar3 + 0xac);
  if (iVar3 == 1) {
LAB_004061d8:
    pAVar4 = unaff_EDI->aiProcess;
  }
  else {
    if (iVar3 == 2) {
      iVar3 = (**(code **)*piVar1)();
      if (*(int *)(iVar3 + 0x20) == 0x4745495a) {
        return false;
      }
      iVar3 = (**(code **)*piVar1)();
      if (*(int *)(iVar3 + 0x20) == 0x41525449) {
        return true;
      }
      goto LAB_00406192;
    }
    if (iVar3 == 3) {
      iVar3 = (**(code **)*piVar1)();
      if (*(int *)(iVar3 + 0x20) != 0x544f5250) {
        return false;
      }
      goto LAB_00406192;
    }
    if (iVar3 == 5) {
      return false;
    }
    if (iVar3 == 6) goto LAB_004061d8;
    if (iVar3 == 7) {
      return false;
    }
    pAVar4 = (AiProcess *)(iVar3 + -10);
  }
  if (pAVar4 == (AiProcess *)0x0) {
    return false;
  }
LAB_00406192:
  bVar2 = GameObject::FriendP(param_1,unaff_EDI);
  return bVar2;
}
