/*
 * Entry: 005c8000
 * Name: ogg_stream_iovecin
 * Namespace: Global
 * Signature: undefined ogg_stream_iovecin()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_iovecin */

undefined4 __cdecl
ogg_stream_iovecin(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  uint *puVar7;
  size_t _NewSize;
  int *piVar8;
  int iVar9;
  int local_4;
  
  iVar9 = 0;
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    return 0xffffffff;
  }
  if (param_2 == 0) {
    return 0;
  }
  iVar6 = 0;
  if (0 < param_3) {
    puVar7 = (uint *)(param_2 + 4);
    do {
      uVar1 = *puVar7;
      if (0x7fffffff < uVar1) {
        return 0xffffffff;
      }
      if ((int)(0x7fffffff - uVar1) < iVar9) {
        return 0xffffffff;
      }
      iVar6 = iVar6 + 1;
      iVar9 = iVar9 + uVar1;
      puVar7 = puVar7 + 2;
    } while (iVar6 < param_3);
  }
  iVar4 = iVar9 / 0xff;
  iVar6 = param_1[3];
  if (iVar6 != 0) {
    piVar8 = param_1 + 2;
    *piVar8 = *piVar8 - iVar6;
    if (*piVar8 != 0) {
      memmove((void *)*param_1,(void *)(iVar6 + *param_1),param_1[2]);
    }
    param_1[3] = 0;
  }
  iVar6 = param_1[1];
  if (param_1[2] < iVar6 - iVar9) {
LAB_005c80e7:
    iVar6 = FUN_005c7ee0();
    if (iVar6 == 0) {
      if (0 < param_3) {
        piVar8 = (int *)(param_2 + 4);
        local_4 = param_3;
        do {
          memcpy(*param_1 + param_1[2],piVar8[-1],*piVar8);
          param_1[2] = param_1[2] + *piVar8;
          piVar8 = piVar8 + 2;
          local_4 = local_4 + -1;
        } while (local_4 != 0);
      }
      iVar6 = 0;
      if (iVar4 + 1 != 1 && -1 < iVar4) {
        do {
          *(undefined4 *)(param_1[4] + (param_1[7] + iVar6) * 4) = 0xff;
          iVar2 = param_1[7];
          iVar3 = param_1[5];
          *(int *)(iVar3 + (iVar2 + iVar6) * 8) = param_1[0x58];
          *(int *)(iVar3 + 4 + (iVar2 + iVar6) * 8) = param_1[0x59];
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
      }
      *(int *)(param_1[4] + (param_1[7] + iVar6) * 4) = iVar9 % 0xff;
      iVar9 = param_1[7];
      iVar2 = param_1[5];
      *(int *)(iVar2 + (iVar9 + iVar6) * 8) = param_5;
      *(int *)(iVar2 + 4 + (iVar9 + iVar6) * 8) = param_6;
      puVar7 = (uint *)(param_1[4] + param_1[7] * 4);
      param_1[0x58] = param_5;
      param_1[0x59] = param_6;
      *puVar7 = *puVar7 | 0x100;
      param_1[7] = param_1[7] + iVar4 + 1;
      puVar7 = (uint *)(param_1 + 0x56);
      uVar1 = *puVar7;
      *puVar7 = *puVar7 + 1;
      param_1[0x57] = param_1[0x57] + (uint)(0xfffffffe < uVar1);
      if (param_4 != 0) {
        param_1[0x52] = 1;
      }
      return 0;
    }
  }
  else {
    if (iVar6 <= 0x7fffffff - iVar9) {
      _NewSize = iVar6 + iVar9;
      if ((int)_NewSize < 0x7ffffbff) {
        _NewSize = _NewSize + 0x400;
      }
      pvVar5 = realloc((void *)*param_1,_NewSize);
      if (pvVar5 != (void *)0x0) {
        param_1[1] = _NewSize;
        *param_1 = (int)pvVar5;
        goto LAB_005c80e7;
      }
    }
    ogg_stream_clear(param_1);
  }
  return 0xffffffff;
}
