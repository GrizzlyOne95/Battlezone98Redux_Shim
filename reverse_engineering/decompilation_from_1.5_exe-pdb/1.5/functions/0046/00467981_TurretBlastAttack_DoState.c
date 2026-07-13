/*
 * Entry: 00467981
 * Name: TurretBlastAttack::DoState
 * Namespace: TurretBlastAttack
 * Signature: void DoState(TurretBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretBlastAttack::DoState(TurretBlastAttack *this)

{
  bool bVar1;
  GameObject *pGVar2;
  
  if (*(int *)&this->field_0xc != 0xd) {
    pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    *(GameObject **)&this->field_0x1c = pGVar2;
    if (pGVar2 != (GameObject *)0x0) {
      bVar1 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar2);
      if ((!bVar1) && (*(int *)(*(int *)&this->field_0x14 + 0x198) != 0)) {
        bVar1 = UnitTask::AbleToHit((UnitTask *)this);
        if (*(int *)&this->field_0xc == 5) {
          UnitTask::DoStand((UnitTask *)this);
        }
        if (bVar1) {
          bVar1 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,
                                *(float *)&this->field_0xf8,1.0);
          if (!bVar1) {
            bVar1 = true;
            goto LAB_00467a04;
          }
        }
        bVar1 = false;
LAB_00467a04:
        UnitTask::UpdateWeapon((UnitTask *)this,bVar1);
        UnitTask::UpdateSpecial((UnitTask *)this);
        return;
      }
    }
    *(undefined4 *)&this->field_0x10 = 0xd;
  }
  return;
}
