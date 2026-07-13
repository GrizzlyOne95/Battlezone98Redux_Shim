/*
 * Entry: 004f8cd1
 * Name: Select_Light_Sources
 * Namespace: Global
 * Signature: void Select_Light_Sources(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Select_Light_Sources(_OBJ76 *param_1)

{
  DYNAMIC_LIGHT *pDVar1;
  float fVar2;
  MAT_3D *pMVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  long lVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  MAT_3D local_a4;
  float local_64 [10];
  double local_3c;
  double local_34;
  double local_2c;
  float local_24 [5];
  float local_10;
  int local_c;
  int local_8;
  
  Lights_Struct.Apply_Light_Counter = 0;
  lVar8 = Lights_Struct.Apply_Light_Counter;
  if (TOD_tbl[Lights_Struct.TOD_entry].Day_Time != 1) {
    pMVar3 = obj_rel_parent_matrix(&local_a4,param_1,(_OBJ76 *)0x0);
    pfVar7 = local_64;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar7 = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pfVar7 = pfVar7 + 1;
    }
    lVar8 = 0;
    local_8 = 4;
    if (Lights_Struct.Visibles_Light_Counter < 4) {
      local_8 = Lights_Struct.Visibles_Light_Counter;
    }
    local_8 = local_8 + 1;
    local_24[0] = -1e+20;
    local_c = 0;
    if (0 < Lights_Struct.Visibles_Light_Counter) {
      do {
        pDVar1 = Lights_Struct.Visibles_Lights[local_c];
        fVar9 = (float10)local_3c - (float10)(pDVar1->World_Pos).x;
        fVar10 = (float10)local_34 - (float10)(pDVar1->World_Pos).y;
        fVar11 = (float10)local_2c - (float10)(pDVar1->World_Pos).z;
        fVar9 = (float10)1 /
                ((float10)pDVar1->Att_Dist * (fVar9 * fVar9 + fVar10 * fVar10 + fVar11 * fVar11) +
                (float10)1);
        local_10 = (float)fVar9;
        if ((pDVar1->flags & 1) != 0) {
          fVar9 = (float10)__CIpow();
          fVar9 = fVar9 * (float10)local_10;
        }
        if ((lVar8 < local_8) || (iVar4 = lVar8, (float10)local_24[0] < fVar9)) {
          Lights_Struct.Apply_Lights[lVar8] = pDVar1;
          local_24[lVar8] = (float)fVar9;
          fVar2 = local_24[0];
          iVar4 = lVar8 + 1;
          iVar6 = 1;
          iVar5 = 0;
          if (1 < iVar4) {
            do {
              if (local_24[iVar6] < local_24[0]) {
                local_24[0] = local_24[iVar6];
                iVar5 = iVar6;
              }
              iVar6 = iVar6 + 1;
            } while (iVar6 < iVar4);
          }
          local_24[0] = local_24[iVar5];
          local_24[iVar5] = fVar2;
          pDVar1 = Lights_Struct.Apply_Lights[iVar5];
          Lights_Struct.Apply_Lights[iVar5] = Lights_Struct.Apply_Lights[0];
          Lights_Struct.Apply_Lights[0] = pDVar1;
          if (iVar4 == local_8) {
            iVar4 = lVar8;
          }
        }
        local_c = local_c + 1;
        lVar8 = iVar4;
      } while (local_c < Lights_Struct.Visibles_Light_Counter);
    }
  }
  Lights_Struct.Apply_Light_Counter = lVar8;
  return;
}
