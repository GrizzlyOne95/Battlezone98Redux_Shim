/*
 * Entry: 0052b6ae
 * Name: BounceBomb::Simulate
 * Namespace: BounceBomb
 * Signature: void Simulate(BounceBomb * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BounceBomb::Simulate(BounceBomb *this,float param_1)

{
  uint *puVar1;
  ExplosionClass *this_00;
  VECTOR_3D_LONG VVar2;
  undefined8 uVar3;
  MAT_3D *pMVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  VECTOR_3D *unaff_ESI;
  float *pfVar7;
  VECTOR_3D *unaff_EDI;
  float *pfVar8;
  MAT_3D local_c0;
  float local_80 [16];
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  VECTOR_3D local_34;
  undefined8 local_28;
  undefined8 local_18;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(float *)&this->field_0x78 < param_1) {
    param_1 = *(float *)&this->field_0x78;
  }
  iVar6 = *(int *)&this->field_0x18;
  if ((*(byte *)(iVar6 + 0x14) & 8) == 0) {
    local_10 = 0;
    local_c = 0;
    local_8 = 0;
    *(undefined4 *)&this->field_0x34 = 0;
    *(undefined4 *)&this->field_0x24 = 0;
    *(undefined4 *)&this->field_0x38 = 0;
    *(undefined4 *)&this->field_0x28 = 0x7149f2ca;
    *(undefined4 *)&this->field_0x3c = 0;
    local_28 = *(undefined8 *)*(undefined1 (*) [20])(iVar6 + 0x48);
    local_18 = *(undefined8 *)(iVar6 + 0x58);
    VVar2.z._4_4_ = (int)((ulonglong)local_18 >> 0x20);
    VVar2._0_20_ = *(undefined1 (*) [20])(iVar6 + 0x48);
    Floor_GetFloor(VVar2,&param_1,&local_34);
    iVar6 = *(int *)&this->field_0x18;
    local_40 = *(undefined4 *)(iVar6 + 0x38);
    uStack_3c = *(undefined4 *)(iVar6 + 0x3c);
    uStack_38 = *(undefined4 *)(iVar6 + 0x40);
    local_10 = local_40;
    local_c = uStack_3c;
    local_8 = uStack_38;
    pMVar4 = Build_Orthogonal_Matrix(&local_c0,unaff_EDI,unaff_ESI);
    uVar3 = local_28;
    pfVar7 = local_80;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar7 = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pfVar7 = pfVar7 + 1;
    }
    pfVar7 = local_80;
    pfVar8 = (float *)(*(int *)&this->field_0x18 + 0x20);
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar8 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pfVar8 = pfVar8 + 1;
    }
    *(undefined8 *)(*(int *)&this->field_0x18 + 0x48) = uVar3;
    *(double *)(*(int *)&this->field_0x18 + 0x50) = (double)param_1;
    *(undefined8 *)(*(int *)&this->field_0x18 + 0x58) = local_18;
    if (*(int *)&this->field_0xd0 != 0) {
      p_Var5 = get_obj_from_handle_fast(*(int *)&this->field_0xd0,*(_OBJ76 **)&this->field_0xcc);
      if (p_Var5 == (_OBJ76 *)0x0) {
        *(undefined4 *)&this->field_0x78 = 0;
      }
    }
  }
  else {
    Grenade::Simulate((Grenade *)this,param_1);
  }
  if (*(float *)&this->field_0x78 <= 0.0) {
    this_00 = *(ExplosionClass **)(*(int *)&this->field_0x10 + 0x3c);
    if (this_00 != (ExplosionClass *)0x0) {
      ExplosionClass::Build
                (this_00,(MAT_3D *)(*(int *)&this->field_0x18 + 0x20),*(_OBJ76 **)&this->field_0xcc)
      ;
    }
    puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
    *puVar1 = *puVar1 | 0x200;
  }
  return;
}
