/*
 * Entry: 004e7cce
 * Name: Cache_Sort_Bsp_Backbone
 * Namespace: Global
 * Signature: MATRIX_STACK * Cache_Sort_Bsp_Backbone(MATRIX_LIST * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MATRIX_STACK * __cdecl Cache_Sort_Bsp_Backbone(MATRIX_LIST *param_1,long param_2)

{
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  int in_EAX;
  int in_EDX;
  float *pfVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float local_14;
  float *local_10;
  int local_c;
  int local_8;
  
  pvVar3 = Quadtree_Cell_Pool;
  iVar6 = 0;
  if (0 < in_EAX) {
    do {
      uVar1 = *(undefined4 *)(*(int *)(in_EDX + 4) + 0xd4);
      *(int *)((int)pvVar3 + iVar6 * 8 + 4) = in_EDX;
      *(undefined4 *)((int)pvVar3 + iVar6 * 8) = uVar1;
      iVar6 = iVar6 + 1;
      in_EDX = in_EDX + 0x48;
    } while (iVar6 < in_EAX);
  }
  if (in_EAX < 2) {
    return pvVar3;
  }
  iVar6 = (in_EAX >> 1) + 1;
  pfVar4 = (float *)((int)pvVar3 + in_EAX * 8 + -8);
  local_10 = (float *)((int)pvVar3 + iVar6 * 8 + -8);
  local_8 = in_EAX;
  do {
    if (iVar6 < 2) {
      local_14 = pfVar4[1];
      fVar5 = *pfVar4;
      local_8 = local_8 + -1;
      *pfVar4 = *(float *)pvVar3;
      pfVar4[1] = *(float *)((int)pvVar3 + 4);
      pfVar4 = pfVar4 + -2;
      if (local_8 == 1) {
        *(float *)pvVar3 = fVar5;
        *(float *)((int)pvVar3 + 4) = local_14;
        return pvVar3;
      }
    }
    else {
      iVar6 = iVar6 + -1;
      fVar5 = local_10[-2];
      local_14 = local_10[-1];
      local_10 = local_10 + -2;
    }
    iVar2 = iVar6 * 2 - local_8;
    local_c = iVar6;
    iVar7 = iVar6 * 2;
    while (iVar7 <= local_8) {
      if ((SBORROW4(iVar7,local_8) != iVar2 < 0) &&
         (*(float *)((int)pvVar3 + iVar7 * 8) < *(float *)((int)pvVar3 + iVar7 * 8 + -8))) {
        iVar7 = iVar7 + 1;
      }
      if (fVar5 <= *(float *)((int)pvVar3 + iVar7 * 8 + -8)) {
        iVar8 = local_8 + 1;
      }
      else {
        *(undefined4 *)((int)pvVar3 + local_c * 8 + -8) =
             *(undefined4 *)((int)pvVar3 + iVar7 * 8 + -8);
        *(undefined4 *)((int)pvVar3 + local_c * 8 + -4) =
             *(undefined4 *)((int)pvVar3 + iVar7 * 8 + -4);
        iVar8 = iVar7 * 2;
        local_c = iVar7;
      }
      iVar2 = iVar8 - local_8;
      iVar7 = iVar8;
    }
    *(float *)((int)pvVar3 + local_c * 8 + -8) = fVar5;
    *(float *)((int)pvVar3 + local_c * 8 + -4) = local_14;
  } while( true );
}
