/*
 * Entry: 0045bbc8
 * Name: SAVProcess::DoSubTask
 * Namespace: SAVProcess
 * Signature: bool DoSubTask(SAVProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SAVProcess::DoSubTask(SAVProcess *this)

{
  float *pfVar1;
  GameObject *pGVar2;
  int iVar3;
  int iVar4;
  float local_8;
  
  pfVar1 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0xc + 0x20) + 0xc))();
  if ((((*pfVar1 - TerMinX < 20.0) || (TerMaxX - *pfVar1 < 20.0)) || (pfVar1[2] - TerMinZ < 20.0))
     || (TerMaxZ - pfVar1[2] < 20.0)) {
    iVar3 = (**(code **)(*(int *)(*(int *)&this->field_0xc + 0x20) + 0x30))();
    *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) | 0x200;
  }
  else if (((*(int *)&this->field_0x18 != 7) ||
           (pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x34),
           pGVar2 == (GameObject *)0x0)) ||
          (iVar3 = (**(code **)pGVar2->_padding_)(), *(int *)(iVar3 + 0x28) != 4)) {
    local_8 = 10000.0;
    pGVar2 = GetClosestEnemyPersonWithin(*(GameObject **)&this->field_0x2c,&local_8);
    if (pGVar2 != (GameObject *)0x0) {
LAB_0045bc87:
      iVar3 = *(int *)&this->field_0x20;
      if (iVar3 == 0) {
        *(undefined4 *)&this->field_0x20 = *(undefined4 *)&this->field_0x18;
        *(undefined4 *)&this->field_0x24 = *(undefined4 *)&this->field_0x34;
        *(undefined4 *)&this->field_0x1c = 7;
        iVar4 = GameObject::GetHandle(pGVar2);
      }
      else {
        iVar4 = *(int *)&this->field_0x24;
        *(undefined4 *)&this->field_0x20 = 0;
        *(int *)&this->field_0x1c = iVar3;
      }
      *(int *)&this->field_0x34 = iVar4;
      return true;
    }
    if (*(int *)&this->field_0x18 != 7) {
      local_8 = 40000.0;
      pGVar2 = GetClosestEnemyWithin(*(GameObject **)&this->field_0x2c,&local_8);
      if (pGVar2 != (GameObject *)0x0) goto LAB_0045bc87;
    }
  }
  return false;
}
