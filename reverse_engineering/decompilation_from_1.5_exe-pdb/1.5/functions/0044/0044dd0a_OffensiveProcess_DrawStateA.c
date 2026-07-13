/*
 * Entry: 0044dd0a
 * Name: OffensiveProcess::DrawStateA
 * Namespace: OffensiveProcess
 * Signature: void DrawStateA(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OffensiveProcess::DrawStateA(OffensiveProcess *this)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  GameObject *pGVar3;
  float *pfVar4;
  VECTOR_3D *pVVar5;
  float fVar6;
  long lVar7;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  GameObject *local_8;
  
  UnitProcess::DrawStateA((UnitProcess *)this);
  fVar6 = SQRT(this->engageRange);
  lVar7 = DisplayInterface::colorWhite;
  pVVar2 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
  WorldCircle(pVVar2,fVar6,lVar7);
  if (this->_padding_ == 8) {
    pGVar3 = GameObjectHandle::GetObj(this->_padding_);
    if (pGVar3 != (GameObject *)0x0) {
      fVar6 = SQRT(this->followRange);
      lVar7 = DisplayInterface::colorBlue;
      pVVar2 = (VECTOR_3D *)(**(code **)(pGVar3->_padding_ + 0xc))();
      WorldCircle(pVVar2,fVar6,lVar7);
    }
  }
  if ((this->_padding_ == 7) && (this->_padding_ != 0)) {
    local_8 = GameObjectHandle::GetObj(this->_padding_);
    if (local_8 != (GameObject *)0x0) {
      pfVar4 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      local_20.x = *pfVar4;
      local_20.y = pfVar4[1];
      local_8 = (GameObject *)&local_8->_padding_;
      local_20.z = pfVar4[2];
      pfVar4 = (float *)(**(code **)(*(int *)local_8 + 0xc))();
      local_14 = *pfVar4;
      local_10 = pfVar4[1];
      local_c = pfVar4[2];
      local_2c.x = local_14 - local_20.x;
      local_2c.y = local_10 - local_20.y;
      local_2c.z = local_c - local_20.z;
      local_20.x = local_2c.x;
      local_20.y = local_2c.y;
      local_20.z = local_2c.z;
      pVVar2 = Normalize_Vector(&local_2c,&local_20);
      pVVar2 = ScaleVector(&local_20,150.0,*pVVar2);
      local_2c.x = pVVar2->x;
      local_2c.y = pVVar2->y;
      local_2c.z = pVVar2->z;
      pfVar4 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      local_20.x = *pfVar4;
      local_20.y = pfVar4[1];
      local_20.z = pfVar4[2];
      local_38.x = local_2c.x + local_20.x;
      local_38.y = local_2c.y + local_20.y;
      local_38.z = local_2c.z + local_20.z;
      pVVar2 = &local_38;
      lVar7 = DisplayInterface::colorWhite;
      local_14 = local_38.x;
      local_10 = local_38.y;
      local_c = local_38.z;
      pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      WorldLine(pVVar5,pVVar2,lVar7);
      iVar1 = this->_padding_;
      lVar7 = DisplayInterface::colorYellow;
      pVVar2 = (VECTOR_3D *)(**(code **)(local_8->_padding_ + 0xc))();
      pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(iVar1 + 0x20) + 0xc))();
      WorldLine(pVVar5,pVVar2,lVar7);
      pGVar3 = GameObjectHandle::GetObj(this->_padding_);
      if (pGVar3 != (GameObject *)0x0) {
        iVar1 = this->_padding_;
        lVar7 = DisplayInterface::colorYellow;
        pVVar2 = (VECTOR_3D *)(**(code **)(pGVar3->_padding_ + 0xc))();
        pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(iVar1 + 0x20) + 0xc))();
        WorldLine(pVVar5,pVVar2,lVar7);
      }
    }
  }
  return;
}
