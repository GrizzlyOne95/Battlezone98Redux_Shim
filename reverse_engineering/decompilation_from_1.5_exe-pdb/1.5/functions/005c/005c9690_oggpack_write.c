/*
 * Entry: 005c9690
 * Name: oggpack_write
 * Namespace: Global
 * Signature: undefined oggpack_write()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_write */

void __cdecl oggpack_write(int *param_1,uint param_2,uint param_3)

{
  void *pvVar1;
  int iVar2;
  
  if (0x20 < param_3) {
LAB_005c978f:
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
  iVar2 = param_1[4];
  if (iVar2 + -4 <= *param_1) {
    if (param_1[3] == 0) {
      return;
    }
    if ((0x7ffffeff < iVar2) ||
       (pvVar1 = realloc((void *)param_1[2],iVar2 + 0x100), pvVar1 == (void *)0x0))
    goto LAB_005c978f;
    param_1[4] = param_1[4] + 0x100;
    param_1[2] = (int)pvVar1;
    param_1[3] = *param_1 + (int)pvVar1;
  }
  param_2 = param_2 & *(uint *)(&DAT_00623708 + param_3 * 4);
  param_3 = param_3 + param_1[1];
  *(byte *)param_1[3] = *(byte *)param_1[3] | (char)param_2 << ((byte)param_1[1] & 0x1f);
  if ((((7 < (int)param_3) &&
       (*(char *)(param_1[3] + 1) = (char)(param_2 >> (8U - (char)param_1[1] & 0x1f)),
       0xf < (int)param_3)) &&
      (*(char *)(param_1[3] + 2) = (char)(param_2 >> (0x10U - (char)param_1[1] & 0x1f)),
      0x17 < (int)param_3)) &&
     (*(char *)(param_1[3] + 3) = (char)(param_2 >> (0x18U - (char)param_1[1] & 0x1f)),
     0x1f < (int)param_3)) {
    if (param_1[1] == 0) {
      *(undefined1 *)(param_1[3] + 4) = 0;
    }
    else {
      *(char *)(param_1[3] + 4) = (char)(param_2 >> (0x20U - (char)param_1[1] & 0x1f));
    }
  }
  iVar2 = (int)(param_3 + ((int)param_3 >> 0x1f & 7U)) >> 3;
  *param_1 = *param_1 + iVar2;
  param_1[3] = param_1[3] + iVar2;
  param_1[1] = param_3 & 7;
  return;
}
