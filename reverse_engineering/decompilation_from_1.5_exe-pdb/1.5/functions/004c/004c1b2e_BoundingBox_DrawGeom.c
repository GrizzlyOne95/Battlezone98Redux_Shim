/*
 * Entry: 004c1b2e
 * Name: BoundingBox::DrawGeom
 * Namespace: BoundingBox
 * Signature: void DrawGeom(BoundingBox * this, CLSN_GEOM * param_1, MAT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall
BoundingBox::DrawGeom(BoundingBox *this,CLSN_GEOM *param_1,MAT_3D *param_2,long param_3)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 *puVar6;
  tagPOINT *ptVar7;
  _clsn_poly *p_Var8;
  tagPOINT tVar9;
  int aiStack_3c [4];
  undefined4 uStack_2c;
  float local_18 [2];
  float local_10;
  undefined1 *local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar5 = param_1->vtx_count;
  uStack_2c = 0x4c1b52;
  iVar3 = iVar5 * -0xc;
  local_c = &stack0xffffffd8 + iVar3;
  if (param_2 == (MAT_3D *)0x0) {
    aiStack_3c[iVar5 * -3 + 4] = iVar5 * 0xc;
    aiStack_3c[iVar5 * -3 + 3] = (int)param_1->verts;
    aiStack_3c[iVar5 * -3 + 2] = (int)local_c;
    aiStack_3c[iVar5 * -3 + 1] = 0x4c1b7b;
    memcpy();
    puVar6 = &stack0xffffffd8 + iVar3;
  }
  else {
    aiStack_3c[iVar5 * -3 + 4] = (int)param_2;
    aiStack_3c[iVar5 * -3 + 3] = iVar5;
    aiStack_3c[iVar5 * -3 + 2] = (int)param_1->verts;
    aiStack_3c[iVar5 * -3 + 1] = (int)local_c;
    aiStack_3c[iVar5 * -3] = 0x4c1b6a;
    Vector_Transform((VECTOR_3D *)aiStack_3c[iVar5 * -3 + 1],(VECTOR_3D *)aiStack_3c[iVar5 * -3 + 2]
                     ,aiStack_3c[iVar5 * -3 + 3],(MAT_3D *)aiStack_3c[iVar5 * -3 + 4]);
    puVar6 = &stack0xffffffd8 + iVar3;
  }
  *(undefined4 *)(puVar6 + -4) = 0x4c1b88;
  iVar3 = iVar5 * -8;
  ptVar7 = (tagPOINT *)(puVar6 + iVar3);
  local_10 = 0.0;
  if (0 < iVar5) {
    do {
      *(float **)(puVar6 + iVar3 + -4) = local_18;
      *(CAMERA **)(puVar6 + iVar3 + -8) = DisplayInterface::currentCamera;
      *(undefined1 **)(puVar6 + iVar3 + -0xc) = local_c;
      *(undefined4 *)(puVar6 + iVar3 + -0x10) = 0x4c1bac;
      tVar9 = WorldToScreen(*(VECTOR_3D **)(puVar6 + iVar3 + -0xc),*(CAMERA **)(puVar6 + iVar3 + -8)
                            ,*(float **)(puVar6 + iVar3 + -4));
      fVar2 = local_18[0];
      *ptVar7 = tVar9;
      if (fVar2 < 0.0) {
        return;
      }
      local_10 = (float)((int)local_10 + 1);
      local_c = local_c + 0xc;
      ptVar7 = ptVar7 + 1;
    } while ((int)local_10 < iVar5);
  }
  p_Var8 = param_1->polys;
  if (p_Var8 < p_Var8 + param_1->poly_count) {
    do {
      iVar5 = 0;
      local_10 = *(float *)(puVar6 + (uint)p_Var8->vtxlist[p_Var8->vtx_count + -1] * 8 + iVar3 + 4);
      uVar4 = *(undefined4 *)(puVar6 + (uint)p_Var8->vtxlist[p_Var8->vtx_count + -1] * 8 + iVar3);
      if (0 < p_Var8->vtx_count) {
        do {
          uVar1 = *(undefined4 *)(puVar6 + (uint)p_Var8->vtxlist[iVar5] * 8 + iVar3);
          fVar2 = *(float *)(puVar6 + (uint)p_Var8->vtxlist[iVar5] * 8 + iVar3 + 4);
          *(undefined4 *)(puVar6 + iVar3 + -4) = 0;
          *(long *)(puVar6 + iVar3 + -8) = param_3;
          *(float *)(puVar6 + iVar3 + -0xc) = fVar2;
          *(undefined4 *)(puVar6 + iVar3 + -0x10) = uVar1;
          *(float *)(puVar6 + iVar3 + -0x14) = local_10;
          local_18[0] = fVar2;
          *(undefined4 *)(puVar6 + iVar3 + -0x18) = uVar4;
          *(_GRAPHIC_BUFFER **)(puVar6 + iVar3 + -0x1c) = DisplayInterface::currentBuffer;
          *(undefined4 *)(puVar6 + iVar3 + -0x20) = 0x4c1c2a;
          Graphic_Line(*(_GRAPHIC_BUFFER **)(puVar6 + iVar3 + -0x1c),
                       *(long *)(puVar6 + iVar3 + -0x18),*(long *)(puVar6 + iVar3 + -0x14),
                       *(long *)(puVar6 + iVar3 + -0x10),*(long *)(puVar6 + iVar3 + -0xc),
                       *(long *)(puVar6 + iVar3 + -8),*(BITMAP_OPER *)(puVar6 + iVar3 + -4));
          iVar5 = iVar5 + 1;
          local_10 = local_18[0];
          uVar4 = uVar1;
        } while (iVar5 < p_Var8->vtx_count);
      }
      p_Var8 = p_Var8 + 1;
    } while (p_Var8 < param_1->polys + param_1->poly_count);
  }
  return;
}
