/*
 * Entry: 00458119
 * Name: PersonRetreat::DoStateProlog
 * Namespace: PersonRetreat
 * Signature: bool DoStateProlog(PersonRetreat * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PersonRetreat::DoStateProlog(PersonRetreat *this)

{
  GameObject *this_00;
  SPHERE *pSVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if (*(int *)&this->field_0xc != 0xd) {
    this_00 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    if (this_00 == (GameObject *)0x0) {
      *(undefined4 *)&this->field_0x10 = 0xd;
    }
    else {
      iVar4 = *(int *)&this->field_0x14;
      fVar7 = 20.0;
      pSVar1 = GameObject::GetSphere(this_00);
      fVar5 = Max(this_00->collisionRadius,pSVar1->radius);
      fVar6 = Max(fVar5 + *(float *)(iVar4 + 0x158) + 10.0,fVar7);
      pfVar2 = (float *)(**(code **)(*(int *)(iVar4 + 0x20) + 0xc))();
      pfVar3 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
      fVar5 = *pfVar2 - *(float *)&this->field_0x38;
      fVar7 = pfVar2[2] - *(float *)&this->field_0x40;
      if ((25.0 <= fVar7 * fVar7 + fVar5 * fVar5) &&
         ((fVar6 <= ABS(*pfVar2 - *pfVar3) || (fVar6 <= ABS(pfVar2[2] - pfVar3[2]))))) {
        *(undefined4 *)&this->field_0x1c = 0;
        *(undefined4 *)&this->field_0x80 = 0;
        return true;
      }
      iVar4 = (**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0x30))();
      *(uint *)(iVar4 + 0x14) = *(uint *)(iVar4 + 0x14) | 0x200;
      Team::AddPilot(*(Team **)(*(int *)&this->field_0x14 + 0x170),1);
    }
  }
  return false;
}
