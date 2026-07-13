/*
 * Entry: 0052d12b
 * Name: DayWrecker::RegCollision
 * Namespace: DayWrecker
 * Signature: bool RegCollision(DayWrecker * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
DayWrecker::RegCollision(DayWrecker *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  uint *puVar1;
  ushort uVar2;
  uint uVar3;
  short sVar4;
  GameObject *pGVar5;
  void *pvVar6;
  GameObject *pGVar7;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  uVar3 = *(uint *)(*(int *)&this->field_0x220 + 0x10c);
  if (((uVar3 & 4) != 0) && ((uVar3 & 8) != 0)) {
    if (param_1 == (_OBJ76 *)0x0) {
      pGVar7 = (GameObject *)0x0;
    }
    else {
      pGVar7 = param_1->gameObj;
    }
    pGVar5 = GameObject::GetObj(*(int *)&this->field_0x21c);
    if (pGVar7 == pGVar5) {
      return false;
    }
  }
  if (((*(byte *)(*(int *)&this->field_0x220 + 0x10c) & 4) != 0) &&
     (*(float *)(*(int *)&this->field_0xec + 0x170) != 0.0)) {
    if (param_1 == (_OBJ76 *)0x0) {
      pvVar6 = (void *)0x0;
    }
    else {
      pvVar6 = param_1->gameObj;
    }
    if (pvVar6 != (void *)0x0) {
      local_18 = 0;
      local_14 = 0;
      local_20 = *(undefined4 *)&this->field_0xe8;
      local_1c = local_20;
      sVar4 = (**(code **)(*(int *)&this->field_0x20 + 4))();
      uVar2 = (ushort)local_18 ^ (sVar4 << 6 ^ (ushort)local_18) & 0x3c0;
      local_18 = CONCAT22(local_18._2_2_,
                          uVar2 ^ (*(ushort *)(*(int *)&this->field_0xec + 0x174) ^ uVar2) & 0xf);
      local_14 = *(undefined4 *)(*(int *)&this->field_0xec + 0x170);
      local_10 = 0;
      local_c = 0xbf800000;
      local_8 = 0;
      (**(code **)(*(int *)((int)pvVar6 + 0x20) + 0x38))(&local_20,&local_10);
    }
  }
  puVar1 = (uint *)(*(int *)&this->field_0x220 + 0x10c);
  *puVar1 = *puVar1 & 0xfffffffb;
  return true;
}
