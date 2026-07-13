/*
 * Entry: 0052c586
 * Name: Cannon::GetLeadPosition
 * Namespace: Cannon
 * Signature: VECTOR_3D * GetLeadPosition(Cannon * this, VECTOR_3D * __return_storage_ptr__, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall
Cannon::GetLeadPosition(Cannon *this,VECTOR_3D *__return_storage_ptr__,GameObject *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float *pfVar11;
  
  pfVar11 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  iVar5 = this->_padding_;
  __return_storage_ptr__->x = *pfVar11;
  __return_storage_ptr__->y = pfVar11[1];
  __return_storage_ptr__->z = pfVar11[2];
  if ((iVar5 != 0) && (0.1 < (param_1->euler).v_mag)) {
    fVar1 = *(float *)(iVar5 + 0x50);
    fVar8 = __return_storage_ptr__->x - (float)*(double *)&this->_padding_;
    fVar2 = (param_1->euler).v.x;
    fVar3 = (param_1->euler).v.y;
    __return_storage_ptr__->x = fVar8;
    fVar9 = __return_storage_ptr__->y - (float)*(double *)&this->_padding_;
    fVar4 = (param_1->euler).v.z;
    __return_storage_ptr__->y = fVar9;
    fVar10 = __return_storage_ptr__->z - (float)*(double *)&this->_padding_;
    __return_storage_ptr__->z = fVar10;
    fVar1 = (fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4) - fVar1 * fVar1;
    fVar7 = fVar8 * fVar2 + fVar9 * fVar3 + fVar10 * fVar4;
    fVar6 = fVar7 * fVar7 - (fVar8 * fVar8 + fVar9 * fVar9 + fVar10 * fVar10) * fVar1;
    if (0.0 < fVar6) {
      fVar1 = (-fVar7 - SQRT(fVar6)) / fVar1;
    }
    else {
      fVar1 = -(fVar7 / fVar1);
    }
    __return_storage_ptr__->x = fVar2 * fVar1 + fVar8 + (float)*(double *)&this->_padding_;
    __return_storage_ptr__->y = fVar1 * fVar3 + fVar9 + (float)*(double *)&this->_padding_;
    __return_storage_ptr__->z = fVar10 + fVar1 * fVar4 + (float)*(double *)&this->_padding_;
  }
  return __return_storage_ptr__;
}
