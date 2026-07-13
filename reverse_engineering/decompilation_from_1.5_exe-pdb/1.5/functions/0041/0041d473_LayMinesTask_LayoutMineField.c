/*
 * Entry: 0041d473
 * Name: LayMinesTask::LayoutMineField
 * Namespace: LayMinesTask
 * Signature: bool LayoutMineField(LayMinesTask * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LayMinesTask::LayoutMineField(LayMinesTask *this,VECTOR_3D *param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D VVar4;
  uchar uVar5;
  bool bVar6;
  VECTOR_3D *pVVar7;
  SINCOS SVar8;
  VECTOR_3D local_2c;
  float local_20;
  undefined4 local_1c;
  float local_18;
  SINCOS local_14;
  uchar local_c;
  undefined3 uStack_b;
  int local_8;
  
  iVar1 = this->mine;
  this->mine = iVar1 + 1;
  if (iVar1 != this->mineCount) {
    uVar5 = CellRegion((this->center).x,(this->center).z);
    local_8 = 0;
    local_1c = 0;
    _local_c = CONCAT31(uStack_b,uVar5);
    do {
      SVar8 = SinCos(this->angle);
      local_20 = SVar8.Cos;
      local_18 = SVar8.Sin;
      VVar4.y = (float)local_1c;
      VVar4.x = local_20;
      VVar4.z = local_18;
      local_14 = SVar8;
      pVVar7 = AddMultVectors(&local_2c,this->center,this->radius,VVar4);
      param_1->x = pVVar7->x;
      param_1->y = pVVar7->y;
      param_1->z = pVVar7->z;
      fVar2 = this->angle + this->angleInc;
      this->angle = fVar2;
      fVar3 = 6.2831855 - this->angleInc * 0.5;
      if (fVar3 < fVar2 != (fVar3 == fVar2)) {
        this->angle = fVar2 - 6.2831855;
        fVar2 = this->radius + this->radiusInc;
        this->radius = fVar2;
        this->angleInc = (this->radiusInc / fVar2) * 1.2566371;
      }
      bVar6 = GoodMinePosition(param_1->x,param_1->z,(uchar)_local_c);
      if (bVar6) {
        return true;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 0x40);
  }
  return false;
}
