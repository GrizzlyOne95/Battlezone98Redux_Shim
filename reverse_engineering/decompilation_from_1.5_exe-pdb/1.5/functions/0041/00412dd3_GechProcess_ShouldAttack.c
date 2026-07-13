/*
 * Entry: 00412dd3
 * Name: GechProcess::ShouldAttack
 * Namespace: GechProcess
 * Signature: bool ShouldAttack(GechProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GechProcess::ShouldAttack(GechProcess *this,State param_1)

{
  VECTOR_3D_LONG VVar1;
  VECTOR_3D VVar2;
  bool bVar3;
  MAT_3D *pMVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  MAT_3D local_128;
  MAT_3D local_e8;
  float local_a8 [10];
  double local_80;
  double local_78;
  double local_70;
  float local_68 [10];
  double local_40;
  double local_38;
  double local_30;
  double local_28;
  double local_20;
  double local_18;
  float local_10;
  float local_c;
  float local_8;
  
  if (param_1 == GOTO) {
    pMVar4 = obj_rel_parent_matrix
                       (&local_e8,*(_OBJ76 **)(*(int *)(*(int *)&this->field_0x2c + 0x228) + 0xf4),
                        (_OBJ76 *)0x0);
    iVar6 = *(int *)&this->field_0x60;
    pfVar7 = local_68;
    for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pfVar7 = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pfVar7 = pfVar7 + 1;
    }
    local_28 = local_40;
    local_20 = local_38;
    local_18 = local_30;
    p_Var5 = (_OBJ76 *)(**(code **)(*(int *)(iVar6 + 0x20) + 0x30))();
    iVar6 = IsCraft(p_Var5);
    if ((iVar6 == 0) &&
       (iVar6 = (**(code **)(*(int *)(*(int *)&this->field_0x60 + 0x20) + 0x30))(),
       *(int *)(iVar6 + 0xac) != 4)) {
      pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x60 + 0x20) + 0xc))();
      fVar9 = (float10)*pfVar7;
      fVar10 = (float10)pfVar7[1];
      fVar11 = (float10)pfVar7[2];
    }
    else {
      pMVar4 = obj_rel_parent_matrix
                         (&local_128,
                          *(_OBJ76 **)(*(int *)(*(int *)&this->field_0x60 + 0x228) + 0xf4),
                          (_OBJ76 *)0x0);
      pfVar7 = local_a8;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar7 = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pfVar7 = pfVar7 + 1;
      }
      fVar9 = (float10)local_80;
      fVar10 = (float10)local_78;
      fVar11 = (float10)local_70;
    }
    local_10 = (float)(fVar9 - (float10)local_40);
    local_c = (float)(fVar10 - (float10)local_38);
    local_8 = (float)(fVar11 - (float10)local_30);
    param_1 = 0x3f800000;
    VVar1.y = local_20;
    VVar1.x = local_28;
    VVar1.z = local_18;
    VVar2.y = local_c;
    VVar2.x = local_10;
    VVar2.z = local_8;
    iVar6 = Terrain_GetIntersection(VVar1,VVar2,(float *)&param_1,(VECTOR_3D *)0x0);
    return (bool)('\x01' - (iVar6 != 0));
  }
  bVar3 = OffensiveProcess::ShouldAttack((OffensiveProcess *)this,param_1);
  return bVar3;
}
