/*
 * Entry: 004eb327
 * Name: MergeAndAdd
 * Namespace: Global
 * Signature: void MergeAndAdd(CAMERA * param_1, long param_2, long param_3, long * param_4, long * param_5, tagENTITY * * param_6, tagENTITY * * param_7, VECTOR_3D * param_8, VECTOR_3D * param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
MergeAndAdd(CAMERA *param_1,long param_2,long param_3,long *param_4,long *param_5,
           tagENTITY **param_6,tagENTITY **param_7,VECTOR_3D *param_8,VECTOR_3D *param_9)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  _ZSORTING *p_Var6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  uint *puVar11;
  int in_ECX;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar12;
  tagENTITY *ptVar13;
  _ZSORTING *p_Var14;
  byte bVar15;
  tagENTITY *unaff_EBX;
  VECTOR_3D *unaff_ESI;
  tagENTITY **pptVar16;
  POLYGON_SKIN *pPVar17;
  tagENTITY *unaff_EDI;
  tagENTITY **pptVar18;
  VECTOR_3D *pVVar19;
  int local_1c;
  int local_14;
  int local_8;
  
  piVar7 = param_5;
  if (LODInfo.mergeBSP != 0) {
    for (; piVar8 = param_4, 0 < in_ECX; in_ECX = in_ECX + -1) {
      *(undefined4 *)(*piVar7 + 0x9c) = 0;
      *(undefined4 *)(*piVar7 + 0xa0) = 0;
      *(undefined4 *)(*piVar7 + 0xa8) = 0;
      *(undefined4 *)(*piVar7 + 0xa4) = 0;
      piVar7 = piVar7 + 1;
    }
    for (; 0 < (int)param_1; param_1 = (CAMERA *)((int)&param_1[-1].View_Pyramid[4].z + 7)) {
      *(undefined4 *)(*piVar8 + 0x9c) = 0;
      *(undefined4 *)(*piVar8 + 0xa0) = 0;
      *(undefined4 *)(*piVar8 + 0xa8) = 0;
      *(undefined4 *)(*piVar8 + 0xa4) = 0;
      piVar8 = piVar8 + 1;
    }
    if (0 < entityCount) {
      local_8 = 1;
      iVar9 = entityHead;
      pVVar19 = (VECTOR_3D *)entityCount;
      do {
        iVar10 = entityEnt[iVar9];
        if (iVar10 < 1) {
          bVar15 = (byte)*(undefined4 *)(param_2 - (iVar10 * 4 + 4));
          iVar12 = *(int *)((int)param_4 - (iVar10 * 4 + 4));
          pptVar18 = param_6 + (iVar10 + 1) * -3;
        }
        else {
          bVar15 = (byte)*(undefined4 *)(param_3 + -4 + iVar10 * 4);
          iVar12 = param_5[iVar10 + -1];
          pptVar18 = param_7 + iVar10 * 3 + -3;
        }
        *(byte *)(iVar12 + 6) = bVar15;
        UpdateMergeBox(unaff_EDI,unaff_ESI,unaff_EBX,pVVar19);
        if (((bVar15 & 8) == 0) && (iVar10 = entityLink[iVar9], local_8 < entityCount)) {
          local_1c = entityCount - local_8;
          iVar12 = extraout_ECX;
          do {
            iVar1 = entityEnt[iVar10];
            if (iVar1 < 1) {
              uVar2 = *(uint *)(param_2 - (iVar1 * 4 + 4));
              iVar3 = *(int *)((int)param_4 - (iVar1 * 4 + 4));
              pptVar16 = param_6 + (iVar1 + 1) * -3;
            }
            else {
              uVar2 = *(uint *)(param_3 + -4 + iVar1 * 4);
              iVar3 = param_5[iVar1 + -1];
              pptVar16 = param_7 + iVar1 * 3 + -3;
            }
            if ((*(int *)(iVar12 + 0xa4) < 10) && ((uVar2 & 8) == 0)) {
              fVar4 = *(float *)(iVar3 + 0x14) + *(float *)(iVar12 + 0x14);
              fVar5 = (float)pptVar18[2] - (float)pptVar16[2];
              if ((ABS(fVar5) <= fVar4) &&
                 (fVar5 * fVar5 +
                  ((float)*pptVar18 - (float)*pptVar16) * ((float)*pptVar18 - (float)*pptVar16) <
                  fVar4 * fVar4)) {
                if ((uVar2 & 0x8000) == 0) {
                  *(int *)(iVar3 + 0x9c) = *(int *)(iVar12 + 0x9c);
                  *(int *)(iVar3 + 0xa0) = iVar12;
                  *(int *)(iVar12 + 0xa4) = *(int *)(iVar12 + 0xa4) + 1;
                  *(int *)(iVar12 + 0x9c) = iVar3;
                  iVar1 = *(int *)(iVar3 + 0x9c);
                  if (iVar1 != 0) {
                    *(int *)(iVar1 + 0xa0) = iVar3;
                  }
                  if ((LODInfo.mergeBSP & 2) != 0) {
                    UpdateMergeBox(unaff_EDI,unaff_ESI,unaff_EBX,pVVar19);
                    iVar12 = extraout_ECX_00;
                  }
                }
                iVar1 = entityEnt[iVar10];
                if (iVar1 < 1) {
                  puVar11 = (uint *)(param_2 - (iVar1 * 4 + 4));
                }
                else {
                  puVar11 = (uint *)(param_3 + -4 + iVar1 * 4);
                }
                *puVar11 = *puVar11 | 0x8000;
              }
            }
            local_1c = local_1c + -1;
            iVar10 = entityLink[iVar10];
          } while (local_1c != 0);
        }
        local_8 = local_8 + 1;
        iVar9 = entityLink[iVar9];
        pVVar19 = (VECTOR_3D *)((int)&pVVar19[-1].z + 3);
      } while (pVVar19 != (VECTOR_3D *)0x0);
    }
  }
  Visible_Entity_Count = 0;
  local_14 = 0;
  iVar9 = entityHead;
  if (0 < entityCount) {
    do {
      iVar10 = entityEnt[iVar9];
      if (iVar10 < 1) {
        ptVar13 = (tagENTITY *)param_4[-1 - iVar10];
        pPVar17 = (POLYGON_SKIN *)(param_6 + (iVar10 + 1) * -3);
        p_Var14 = *(_ZSORTING **)(iVar10 * -4 + -4 + param_2);
        ptVar13->lodFlags = (uchar)p_Var14;
      }
      else {
        ptVar13 = (tagENTITY *)param_5[iVar10 + -1];
        pPVar17 = (POLYGON_SKIN *)(param_7 + iVar10 * 3 + -3);
        p_Var14 = *(_ZSORTING **)(iVar10 * 4 + -4 + param_3);
        ptVar13->lodFlags = (byte)p_Var14 | 0x20;
      }
      iVar10 = Visible_Entity_Count;
      if (((uint)p_Var14 & 0x8000) == 0) {
        if ((LODInfo.mergeBSP & 2) != 0) {
          Visible_Entity_Count = Visible_Entity_Count + 1;
          Visible_Entity_Cluster[iVar10] = ptVar13;
        }
        p_Var6 = SortingTableCurrent;
        SortingTableCurrent->vcnt = 0;
        p_Var6->Type = 6;
        p_Var6[2].Bitmap_Operation = (long)ptVar13;
        p_Var6[1].vcnt = (long)ptVar13->obj76;
        p_Var6[2].Skin_Color.Color = 0;
        p_Var6[1].Next = (_ZSORTING *)0x0;
        p_Var6[1].Previous = p_Var14;
        p_Var6[2].vcnt = (uint)p_Var14 & 0x100;
        p_Var6[1].Skin_Color = *pPVar17;
        p_Var6[1].Bitmap_Operation = (long)pPVar17[1];
        p_Var6[1].Type = (long)pPVar17[2];
        p_Var6[1].Z_Value = (ptVar13->bSphere).radius;
        fVar4 = (float)p_Var6[1].Type - (ptVar13->bSphere).radius;
        p_Var6->Z_Value = fVar4;
        ZSORTAdd(fVar4);
      }
      local_14 = local_14 + 1;
      iVar9 = entityLink[iVar9];
    } while (local_14 < entityCount);
  }
  return;
}
