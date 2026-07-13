/*
 * Entry: 0046f4af
 * Name: SitTask::DoState
 * Namespace: SitTask
 * Signature: void DoState(SitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SitTask::DoState(SitTask *this)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  char cVar4;
  VECTOR_3D *pVVar5;
  int *piVar6;
  float *pfVar7;
  float fVar8;
  VECTOR_3D VStack_3c;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  VECTOR_3D VStack_18;
  float *pfStack_c;
  int *piStack_8;
  
  VStack_18.x = 0.0;
  VStack_18.y = 0.0;
  piVar6 = *(int **)&this->field_0x14;
  VStack_18.z = 0.0;
  fVar8 = *(float *)&this->field_0x9c;
  pfVar7 = (float *)(piVar6[0x8a] + 0xc4);
  pfStack_c = pfVar7;
  piStack_8 = piVar6;
  if (!NAN(fVar8) && 4.0 < fVar8 != (fVar8 == 4.0)) {
    cVar4 = (**(code **)(*piVar6 + 0x68))();
    if (cVar4 != '\0') {
      pVVar5 = EvadeOrdnanceForce(&VStack_3c,*(GameObject **)&this->field_0x14,
                                  *(Ordnance **)&this->field_0x128,(Ordnance **)&this->field_0x128);
      fStack_24 = pVVar5->x;
      fStack_20 = pVVar5->y;
      fStack_1c = pVVar5->z;
      fVar8 = TimeStep();
      fStack_30 = *(float *)&this->field_0x12c;
      fStack_2c = *(float *)&this->field_0x130;
      fStack_28 = *(float *)&this->field_0x134;
      VStack_3c.x = fStack_24 - fStack_30;
      VStack_3c.y = fStack_20 - fStack_2c;
      VStack_3c.z = fStack_1c - fStack_28;
      VVar3.x = *(float *)&this->field_0x12c;
      VVar3.y = *(float *)&this->field_0x130;
      VVar3.z = *(float *)&this->field_0x134;
      VVar2.y = VStack_3c.y;
      VVar2.x = VStack_3c.x;
      VVar2.z = VStack_3c.z;
      pVVar5 = AddMultVectors(&VStack_3c,VVar3,fVar8 + fVar8,VVar2);
      VStack_3c.x = pVVar5->x;
      VStack_3c.y = pVVar5->y;
      VStack_3c.z = pVVar5->z;
      *(float *)&this->field_0x12c = VStack_3c.x;
      *(float *)&this->field_0x130 = VStack_3c.y;
      *(float *)&this->field_0x134 = VStack_3c.z;
      piVar6 = piStack_8;
      pfVar7 = pfStack_c;
      fStack_24 = VStack_3c.x;
      fStack_20 = VStack_3c.y;
      fStack_1c = VStack_3c.z;
      VStack_18.x = VStack_3c.x;
      VStack_18.y = VStack_3c.y;
      VStack_18.z = VStack_3c.z;
    }
  }
  if (0.01 < (float)piVar6[0x44]) {
    VVar1.y = VStack_18.y;
    VVar1.x = VStack_18.x;
    VVar1.z = VStack_18.z;
    pVVar5 = AddMultVectors(&VStack_3c,VVar1,-4.0,*(VECTOR_3D *)(piVar6 + 0x48));
    VStack_18.x = pVVar5->x;
    VStack_18.y = pVVar5->y;
    VStack_18.z = pVVar5->z;
    piVar6 = piStack_8;
    pfVar7 = pfStack_c;
  }
  UnitTask::ApplyForce((UnitTask *)this,&VStack_18);
  fVar8 = Clamp(-(float)piVar6[0x4c],-1.0,1.0);
  *pfVar7 = fVar8;
  pfVar7[4] = 0.0;
  return;
}
