/*
 * Entry: 005c97c0
 * Name: oggpackB_write
 * Namespace: Global
 * Signature: undefined oggpackB_write()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpackB_write */

void __cdecl oggpackB_write(int *param_1,uint param_2,uint param_3)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  
  if (0x20 < param_3) {
LAB_005c98bf:
    if ((void *)param_1[2] != (void *)0x0) {
      free((void *)param_1[2]);
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    return;
  }
  iVar3 = param_1[4];
  if (iVar3 + -4 <= *param_1) {
    if (param_1[3] == 0) {
      return;
    }
    if ((0x7ffffeff < iVar3) ||
       (pvVar1 = realloc((void *)param_1[2],iVar3 + 0x100), pvVar1 == (void *)0x0))
    goto LAB_005c98bf;
    param_1[4] = param_1[4] + 0x100;
    param_1[2] = (int)pvVar1;
    param_1[3] = *param_1 + (int)pvVar1;
  }
  uVar2 = (*(uint *)(&DAT_00623708 + param_3 * 4) & param_2) << (0x20U - (char)param_3 & 0x1f);
  param_3 = param_3 + param_1[1];
  *(byte *)param_1[3] = *(byte *)param_1[3] | (byte)(uVar2 >> ((char)param_1[1] + 0x18U & 0x1f));
  if ((((7 < (int)param_3) &&
       (*(char *)(param_1[3] + 1) = (char)(uVar2 >> ((char)param_1[1] + 0x10U & 0x1f)),
       0xf < (int)param_3)) &&
      (*(char *)(param_1[3] + 2) = (char)(uVar2 >> ((char)param_1[1] + 8U & 0x1f)),
      0x17 < (int)param_3)) &&
     (*(char *)(param_1[3] + 3) = (char)(uVar2 >> ((byte)param_1[1] & 0x1f)), 0x1f < (int)param_3))
  {
    if (param_1[1] == 0) {
      *(undefined1 *)(param_1[3] + 4) = 0;
    }
    else {
      *(char *)(param_1[3] + 4) = (char)uVar2 << (8U - (char)param_1[1] & 0x1f);
    }
  }
  iVar3 = (int)(param_3 + ((int)param_3 >> 0x1f & 7U)) >> 3;
  *param_1 = *param_1 + iVar3;
  param_1[3] = param_1[3] + iVar3;
  param_1[1] = param_3 & 7;
  return;
}
