/*
 * Entry: 0052d234
 * Name: DayWrecker::Explode
 * Namespace: DayWrecker
 * Signature: void Explode(DayWrecker * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DayWrecker::Explode(DayWrecker *this)

{
  uint *puVar1;
  float fVar2;
  int extraout_EAX;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  MAT_3D *pMVar6;
  MAT_3D local_58;
  undefined1 local_18 [8];
  float local_10;
  float local_c;
  long local_8;
  
  puVar1 = (uint *)(*(int *)&this->field_0xc8 + 0x14);
  *puVar1 = *puVar1 | 0x200;
  fVar2 = *(float *)&this->field_0xdc;
  pfVar5 = (float *)(*(int *)&this->field_0xc8 + 0x20);
  pMVar6 = &local_58;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar6->right_x = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  local_58.posit_x = (double)fVar2;
  local_58.posit_y = (double)*(float *)&this->field_0xe0;
  local_58.posit_z = (double)*(float *)&this->field_0xe4;
  ExplosionClass::Build(xplBuilding,&local_58,(_OBJ76 *)0x0);
  if (((byte)useD3D & 4) != 0) {
    iVar4 = *(int *)&this->field_0xc4;
    local_18._0_4_ = *(float *)(iVar4 + 8);
    local_18._4_4_ = *(float *)(iVar4 + 0xc);
    local_10 = *(float *)(iVar4 + 0x10);
    local_c = *(float *)(iVar4 + 0x14);
    Vector_Transform((VECTOR_3D *)local_18,(VECTOR_3D *)local_18,1,
                     (MAT_3D *)(*(int *)&this->field_0xc8 + 0x20));
    Vector_Transform((VECTOR_3D *)local_18,(VECTOR_3D *)local_18,1,&View_Record.MainCam.Matrix);
    local_8 = Camera_Bounding_Sphere_Test(&View_Record.MainCam,(VECTOR_3D *)local_18,local_c);
    if ((double)local_8 < 0.0 != ((double)local_8 == 0.0)) {
      fVar2 = (local_c / local_10) * 3.0;
      ColorFade::SetGlare(&colorFade,fVar2 * fVar2);
    }
  }
  _ftol2_sse();
  for (iVar4 = extraout_EAX; iVar4 != 0; iVar4 = iVar4 + -1) {
    uVar3 = Rand_Counter + 1U & 0xff;
    local_18._4_4_ = Pseudo_Rand_Number[uVar3] * 20.0;
    uVar3 = (uVar3 + 1 & 0xff) + 1;
    Rand_Counter = uVar3 & 0xff;
    local_10 = *(float *)(&DAT_00c9021c + uVar3 * 4) * 15.0 + 5.0;
    local_c = Pseudo_Rand_Number[Rand_Counter] * 20.0;
    ParticleEffect::AddParticle
              (&particleEffect,(VECTOR_3D *)&this->field_0xdc,(VECTOR_3D *)(local_18 + 4));
  }
  (**(code **)(*(int *)this + 0x10))();
  return;
}
