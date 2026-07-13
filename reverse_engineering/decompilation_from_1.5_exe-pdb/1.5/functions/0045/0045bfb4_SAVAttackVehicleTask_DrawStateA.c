/*
 * Entry: 0045bfb4
 * Name: SAVAttackVehicleTask::DrawStateA
 * Namespace: SAVAttackVehicleTask
 * Signature: void DrawStateA(SAVAttackVehicleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SAVAttackVehicleTask::DrawStateA(SAVAttackVehicleTask *this)

{
  double dVar1;
  _OBJ76 *p_Var2;
  float fVar3;
  VECTOR_3D VVar4;
  char cVar5;
  char *pcVar6;
  float *pfVar7;
  VECTOR_3D *pVVar8;
  GameObject *pGVar9;
  VECTOR_3D *pVVar10;
  float fVar11;
  long lVar12;
  VECTOR_3D local_70;
  VECTOR_3D local_64;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  UnitTask::DrawStateA((UnitTask *)this);
  sprintf(local_58," SAVAttackVehicleTask:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  cVar5 = (**(code **)(**(int **)&this->field_0x14 + 100))();
  pcVar6 = "true";
  if (cVar5 == '\0') {
    pcVar6 = "false";
  }
  sprintf(local_58," Deployed: %s",pcVar6);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  fVar11 = Get_Time();
  dVar1 = (double)(*(float *)&this->field_0x124 - fVar11);
  sprintf(local_58," TimeOut: (%f)",SUB84(dVar1,0),(int)((ulonglong)dVar1 >> 0x20));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  fVar11 = *pfVar7 - *(float *)&this->field_0x2c;
  fVar3 = pfVar7[2] - *(float *)&this->field_0x34;
  dVar1 = (double)SQRT(fVar3 * fVar3 + fVar11 * fVar11);
  sprintf(local_58," GotoDist: (%f)",SUB84(dVar1,0),(int)((ulonglong)dVar1 >> 0x20));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  fVar11 = SQRT(*(float *)&this->field_0xa4);
  lVar12 = DisplayInterface::colorWhite;
  pVVar8 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  WorldCircle(pVVar8,fVar11,lVar12);
  pGVar9 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  *(GameObject **)&this->field_0x1c = pGVar9;
  if (pGVar9 != (GameObject *)0x0) {
    p_Var2 = pGVar9->obj;
    pVVar8 = (VECTOR_3D *)(**(code **)(pGVar9->_padding_ + 0xc))();
    VVar4.x = (p_Var2->transform).front_x;
    VVar4.y = (p_Var2->transform).front_y;
    VVar4.z = (p_Var2->transform).front_z;
    pVVar10 = AddMultVectors(&local_70,*pVVar8,20.0,VVar4);
    local_64.x = pVVar10->x;
    local_64.y = pVVar10->y;
    pVVar8 = &local_64;
    local_64.z = pVVar10->z;
    lVar12 = DisplayInterface::colorRed;
    pVVar10 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    WorldLine(pVVar10,pVVar8,lVar12);
  }
  return;
}
