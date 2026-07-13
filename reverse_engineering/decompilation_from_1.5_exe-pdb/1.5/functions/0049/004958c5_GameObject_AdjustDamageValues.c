/*
 * Entry: 004958c5
 * Name: GameObject::AdjustDamageValues
 * Namespace: GameObject
 * Signature: void AdjustDamageValues(GameObject * this, DAMAGE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::AdjustDamageValues(GameObject *this,DAMAGE *param_1)

{
  ushort uVar1;
  float fVar2;
  bool bVar3;
  int iVar4;
  Team *this_00;
  
  iVar4 = Net_IsNetGame();
  if (iVar4 != 0) {
    return;
  }
  if (1 < difficultySetting) {
    return;
  }
  if ((this->obj->flags & 0x10) == 0) {
    if ((param_1->field_0x8 & 0x10) == 0) {
      return;
    }
    bVar3 = FriendP(this,*(ushort *)((int)&param_1->dmg_source->flags + 2) & 0xf);
    if (bVar3) {
      fVar2 = (float)difficultySetting * 0.5;
    }
    else {
      fVar2 = 1.5 - (float)difficultySetting * 0.25;
    }
    param_1->dmg_value = fVar2 * param_1->dmg_value;
    return;
  }
  if (param_1->dmg_source != (_OBJ76 *)0x0) {
    uVar1 = *(ushort *)((int)&param_1->dmg_source->flags + 2);
    iVar4 = (**(code **)(this->_padding_ + 4))();
    this_00 = Team::GetTeam(uVar1 & 0xf);
    bVar3 = Team::FriendP(this_00,iVar4);
    if (bVar3) {
      fVar2 = (float)difficultySetting * 0.5;
      goto LAB_0049593d;
    }
  }
  fVar2 = (float)difficultySetting * 0.25 + 0.5;
LAB_0049593d:
  param_1->dmg_value = fVar2 * param_1->dmg_value;
  return;
}
