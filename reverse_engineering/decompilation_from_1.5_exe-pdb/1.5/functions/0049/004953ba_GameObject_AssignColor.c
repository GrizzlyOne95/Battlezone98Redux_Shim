/*
 * Entry: 004953ba
 * Name: GameObject::AssignColor
 * Namespace: GameObject
 * Signature: void AssignColor(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::AssignColor(GameObject *this)

{
  int iVar1;
  bool bVar2;
  long lVar3;
  
  if ((this->teamSlot < 0) && (this->obj->class_id == CLASS_ID_POWERUP)) {
    this->liveColor = DisplayInterface::colorYellow;
    lVar3 = DisplayInterface::colorDkYellow;
  }
  else {
    iVar1 = this->teamNumber;
    if (iVar1 == 0) {
      this->liveColor = DisplayInterface::colorWhite;
      lVar3 = DisplayInterface::colorGrey;
    }
    else if (userTeamNumber == iVar1) {
      this->liveColor = DisplayInterface::colorGreen;
      lVar3 = DisplayInterface::colorDkGreen;
    }
    else {
      if (userTeamList != (Team *)0x0) {
        bVar2 = Team::FriendP(userTeamList,iVar1);
        if (bVar2) {
          this->liveColor = DisplayInterface::colorBlue;
          lVar3 = DisplayInterface::colorDkBlue;
          goto LAB_00495453;
        }
      }
      this->liveColor = DisplayInterface::colorRed;
      lVar3 = DisplayInterface::colorDkRed;
    }
  }
LAB_00495453:
  this->deadColor = lVar3;
  return;
}
