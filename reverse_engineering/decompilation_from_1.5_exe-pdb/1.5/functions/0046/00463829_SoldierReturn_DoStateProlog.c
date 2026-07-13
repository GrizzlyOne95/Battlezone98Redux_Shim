/*
 * Entry: 00463829
 * Name: SoldierReturn::DoStateProlog
 * Namespace: SoldierReturn
 * Signature: bool DoStateProlog(SoldierReturn * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SoldierReturn::DoStateProlog(SoldierReturn *this)

{
  GameObject *pGVar1;
  SPHERE *pSVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  if (*(int *)&this->field_0xc != 0xd) {
    pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    if (pGVar1 == (GameObject *)0x0) {
      *(undefined4 *)&this->field_0x10 = 0xd;
    }
    else {
      fVar7 = 10.0;
      pSVar2 = GameObject::GetSphere(pGVar1);
      fVar6 = Max(pGVar1->collisionRadius,pSVar2->radius);
      fVar6 = Max(fVar6 + *(float *)(*(int *)&this->field_0x14 + 0x158) + 5.0,fVar7);
      pfVar3 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
      pfVar4 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
      if (fVar6 * fVar6 <=
          (pfVar4[2] - pfVar3[2]) * (pfVar4[2] - pfVar3[2]) +
          (*pfVar4 - *pfVar3) * (*pfVar4 - *pfVar3)) {
        *(undefined4 *)&this->field_0x1c = 0;
        *(GameObject **)&this->field_0x84 = pGVar1;
        pGVar1 = AvoidObject(*(GameObject **)&this->field_0x14,pGVar1);
        *(GameObject **)&this->field_0x80 = pGVar1;
        return true;
      }
      iVar5 = (**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0x30))();
      *(uint *)(iVar5 + 0x14) = *(uint *)(iVar5 + 0x14) | 0x200;
    }
  }
  return false;
}
