/*
 * Entry: 004dc119
 * Name: Targeting::Simulate
 * Namespace: Targeting
 * Signature: void Simulate(Targeting * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Targeting::Simulate(Targeting *this,float param_1)

{
  Team *this_00;
  GameObject *this_01;
  GameObject *pGVar1;
  AiCommand AVar2;
  int iVar3;
  GameObject *pGVar4;
  int iVar5;
  
  this_01 = GameObject::userObject;
  this_00 = GameObject::userTeamList;
  if (GameObject::userObject == (GameObject *)0x0) {
    return;
  }
  pGVar1 = GameObject::GetObj(GameObject::userObject->targetHandle);
  if (user_controls.frontal_target == '\0') {
    if (user_controls.cycle_beacon == '\0') {
      pGVar4 = (GameObject *)0x0;
      if (pGVar1 != (GameObject *)0x0) {
        pGVar4 = ValidateTarget(this,pGVar1);
      }
    }
    else {
      if (((pGVar1 == (GameObject *)0x0) || (iVar5 = pGVar1->teamSlot, iVar5 < 0x23)) ||
         (0x2c < iVar5)) {
        iVar5 = 0;
      }
      pGVar4 = (GameObject *)0x0;
      iVar3 = iVar5;
      if (iVar5 == 0) {
        iVar5 = 0x23;
        do {
          pGVar4 = Team::GetSlot(this_00,iVar5);
          if (pGVar4 != (GameObject *)0x0) break;
          iVar5 = iVar5 + 1;
        } while (iVar5 < 0x2d);
      }
      else {
        do {
          iVar3 = iVar3 + 1;
          if (0x2c < iVar3) {
            iVar3 = 0x23;
            if (0x22 < iVar5) goto LAB_004dc1c0;
            break;
          }
          pGVar4 = Team::GetSlot(this_00,iVar3);
        } while (pGVar4 == (GameObject *)0x0);
      }
    }
  }
  else if (pGVar1 == (GameObject *)0x0) {
    pGVar4 = FindTarget(this);
  }
  else {
    pGVar4 = (GameObject *)0x0;
  }
LAB_004dc1e3:
  GameObject::SetTarget(this_01,pGVar4);
  AVar2 = ActionMode::GetCommand(&actionMode,pGVar4);
  if (AVar2 == CMD_SELECT) {
    AVar2 = CMD_NONE;
  }
  ControlPanel::AltCommand(&controlPanel,AVar2,pGVar4);
  return;
  while (iVar3 = iVar3 + 1, iVar3 <= iVar5) {
LAB_004dc1c0:
    pGVar4 = Team::GetSlot(this_00,iVar3);
    if (pGVar4 != (GameObject *)0x0) break;
  }
  goto LAB_004dc1e3;
}
