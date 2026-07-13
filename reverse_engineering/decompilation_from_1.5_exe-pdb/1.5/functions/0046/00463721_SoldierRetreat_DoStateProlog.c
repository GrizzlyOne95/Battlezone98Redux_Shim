/*
 * Entry: 00463721
 * Name: SoldierRetreat::DoStateProlog
 * Namespace: SoldierRetreat
 * Signature: bool DoStateProlog(SoldierRetreat * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SoldierRetreat::DoStateProlog(SoldierRetreat *this)

{
  GameObject *pGVar1;
  SPHERE *pSVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  if (*(int *)&this->field_0xc != 0xd) {
    pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    if (pGVar1 == (GameObject *)0x0) {
      *(undefined4 *)&this->field_0x10 = 0xd;
    }
    else {
      iVar5 = *(int *)&this->field_0x14;
      fVar8 = 20.0;
      pSVar2 = GameObject::GetSphere(pGVar1);
      fVar6 = Max(pGVar1->collisionRadius,pSVar2->radius);
      fVar7 = Max(fVar6 + *(float *)(iVar5 + 0x158) + 10.0,fVar8);
      pfVar3 = (float *)(**(code **)(*(int *)(iVar5 + 0x20) + 0xc))();
      pfVar4 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
      fVar6 = *pfVar3 - *(float *)&this->field_0x38;
      fVar8 = pfVar3[2] - *(float *)&this->field_0x40;
      if ((25.0 <= fVar8 * fVar8 + fVar6 * fVar6) &&
         ((fVar7 <= ABS(*pfVar3 - *pfVar4) || (fVar7 <= ABS(pfVar3[2] - pfVar4[2]))))) {
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
