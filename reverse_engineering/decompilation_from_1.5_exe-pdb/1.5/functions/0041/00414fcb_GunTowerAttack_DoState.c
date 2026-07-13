/*
 * Entry: 00414fcb
 * Name: GunTowerAttack::DoState
 * Namespace: GunTowerAttack
 * Signature: void DoState(GunTowerAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerAttack::DoState(GunTowerAttack *this)

{
  bool bVar1;
  GameObject *pGVar2;
  float fVar3;
  VECTOR_3D local_24;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar2;
  if (((pGVar2 != (GameObject *)0x0) &&
      (bVar1 = GameObject::FriendP(*(GameObject **)&this->field_0x14,pGVar2), !bVar1)) &&
     (*(int *)(*(int *)&this->field_0x14 + 0x198) != 0)) {
    local_5 = UnitTask::AbleToHit((UnitTask *)this);
    if (*(int *)&this->field_0xc == 5) {
      local_18 = 0;
      local_14 = 0;
      local_10 = 0;
      local_c = *(int *)(*(int *)&this->field_0x14 + 0x228) + 0xc4;
      local_24.x = 0.0;
      local_24.y = 0.0;
      local_24.z = 0.0;
      UnitTask::LookAtLocalPos
                ((UnitTask *)this,(VECTOR_3D *)&this->field_0xcc,(VECTOR_3D *)&this->field_0xe8);
      UnitTask::ApplyForce((UnitTask *)this,&local_24);
      fVar3 = Clamp(*(float *)&this->field_0xe0 * 0.2 + *(float *)&this->field_0xb4,-1.0,1.0);
      *(float *)&this->field_0xb4 = fVar3;
      *(float *)(local_c + 4) = fVar3;
    }
    if ((local_5 == '\0') ||
       (bVar1 = MayHitFriends(*(GameObject **)&this->field_0x14,*(float *)&this->field_0xd8,0.3,1.0)
       , bVar1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    UnitTask::UpdateWeapon((UnitTask *)this,bVar1);
    return;
  }
  *(undefined4 *)&this->field_0x10 = 0xd;
  return;
}
