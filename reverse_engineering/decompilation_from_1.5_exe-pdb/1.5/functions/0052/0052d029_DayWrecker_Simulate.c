/*
 * Entry: 0052d029
 * Name: DayWrecker::Simulate
 * Namespace: DayWrecker
 * Signature: void Simulate(DayWrecker * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DayWrecker::Simulate(DayWrecker *this,float param_1)

{
  uint *puVar1;
  float fVar2;
  ExplosionClass *this_00;
  int iVar3;
  float *pfVar4;
  MAT_3D *pMVar5;
  MAT_3D local_44;
  
  if ((*(byte *)(*(int *)&this->field_0x220 + 0x10c) & 4) == 0) {
    obj_set_flag(*(_OBJ76 **)&this->field_0xe8,0x200);
    puVar1 = (uint *)(*(int *)&this->field_0x220 + 0x10c);
    *puVar1 = *puVar1 | 0x20;
    if (((*(_OBJ76 **)&this->field_0xe8)->flags & 0x800) != 0) {
      Remove_Light_Source(*(_OBJ76 **)&this->field_0xe8);
    }
    MakeCrater(*(float *)&this->field_0xfc,*(float *)&this->field_0x104,
               *(float *)(*(int *)&this->field_0xec + 0x17c));
    fVar2 = *(float *)&this->field_0xfc;
    this_00 = *(ExplosionClass **)(*(int *)&this->field_0xec + 0x178);
    pfVar4 = (float *)(*(int *)&this->field_0xe8 + 0x20);
    pMVar5 = &local_44;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar5->right_x = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
    local_44.posit_x = (double)fVar2;
    local_44.posit_y = (double)*(float *)&this->field_0x100;
    local_44.posit_z = (double)*(float *)&this->field_0x104;
    (**(code **)(*(int *)&this->field_0x20 + 0x10))();
    ExplosionClass::Build(this_00,&local_44,(_OBJ76 *)0x0);
  }
  else {
    PowerUp::Simulate((PowerUp *)this,param_1);
  }
  return;
}
