/*
 * Entry: 005b3110
 * Name: render_line
 * Namespace: Global
 * Signature: void render_line(int param_1, int param_2, int param_3, int param_4, int param_5, float * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl render_line(int param_1,int param_2,int param_3,int param_4,int param_5,float *param_6)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  int in_ECX;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_8;
  
  iVar9 = param_3 - param_2;
  uVar4 = in_ECX - param_4;
  iVar2 = (int)uVar4 / iVar9;
  if ((int)uVar4 < 0) {
    local_8 = iVar2 + -1;
  }
  else {
    local_8 = iVar2 + 1;
  }
  uVar6 = iVar2 * iVar9 >> 0x1f;
  iVar8 = ((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)) - ((iVar2 * iVar9 ^ uVar6) - uVar6);
  iVar5 = 0;
  if (param_3 < param_1) {
    param_1 = param_3;
  }
  if (param_2 < param_1) {
    *(float *)(param_5 + param_2 * 4) =
         FLOOR1_fromdB_LOOKUP[param_4] * *(float *)(param_5 + param_2 * 4);
  }
  iVar7 = param_2 + 1;
  if (iVar7 < param_1) {
    if (3 < param_1 - iVar7) {
      param_3 = ((param_1 - iVar7) - 4U >> 2) + 1;
      iVar1 = iVar7 * 4;
      iVar7 = iVar7 + param_3 * 4;
      pfVar3 = (float *)(param_5 + 8 + iVar1);
      do {
        iVar5 = iVar5 + iVar8;
        iVar1 = iVar2;
        if (iVar9 <= iVar5) {
          iVar5 = iVar5 - iVar9;
          iVar1 = local_8;
        }
        iVar5 = iVar5 + iVar8;
        pfVar3[-2] = FLOOR1_fromdB_LOOKUP[param_4 + iVar1] * pfVar3[-2];
        iVar10 = iVar2;
        if (iVar9 <= iVar5) {
          iVar5 = iVar5 - iVar9;
          iVar10 = local_8;
        }
        iVar10 = param_4 + iVar1 + iVar10;
        iVar5 = iVar5 + iVar8;
        pfVar3[-1] = FLOOR1_fromdB_LOOKUP[iVar10] * pfVar3[-1];
        iVar1 = iVar2;
        if (iVar9 <= iVar5) {
          iVar5 = iVar5 - iVar9;
          iVar1 = local_8;
        }
        iVar10 = iVar10 + iVar1;
        iVar5 = iVar5 + iVar8;
        *pfVar3 = FLOOR1_fromdB_LOOKUP[iVar10] * *pfVar3;
        iVar1 = iVar2;
        if (iVar9 <= iVar5) {
          iVar5 = iVar5 - iVar9;
          iVar1 = local_8;
        }
        param_4 = iVar10 + iVar1;
        param_3 = param_3 + -1;
        pfVar3[1] = FLOOR1_fromdB_LOOKUP[param_4] * pfVar3[1];
        pfVar3 = pfVar3 + 4;
      } while (param_3 != 0);
    }
    if (iVar7 < param_1) {
      pfVar3 = FLOOR1_fromdB_LOOKUP + param_4;
      do {
        iVar5 = iVar5 + iVar8;
        iVar1 = iVar2;
        if (iVar9 <= iVar5) {
          iVar5 = iVar5 - iVar9;
          iVar1 = local_8;
        }
        pfVar3 = pfVar3 + iVar1;
        iVar1 = iVar7 * 4;
        iVar7 = iVar7 + 1;
        *(float *)(param_5 + -4 + iVar7 * 4) = *pfVar3 * *(float *)(param_5 + iVar1);
      } while (iVar7 < param_1);
    }
  }
  return;
}
