
undefined1 * FUN_0082c405(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (param_1[2] == 6) {
    iVar1 = *param_1;
    if (*(char *)(iVar1 + 6) == '\0') {
      iVar2 = *(int *)(iVar1 + 0x10);
      if ((param_2 < 1) || (*(int *)(iVar2 + 0x24) < param_2)) {
        puVar3 = (undefined1 *)0x0;
      }
      else {
        *param_3 = *(int *)(*(int *)(iVar1 + 0x10 + param_2 * 4) + 8);
        puVar3 = (undefined1 *)(*(int *)(*(int *)(iVar2 + 0x1c) + -4 + param_2 * 4) + 0x10);
      }
      return puVar3;
    }
    if ((0 < param_2) && (param_2 <= (int)(uint)*(byte *)(iVar1 + 7))) {
      *param_3 = param_2 * 0x10 + 8 + iVar1;
      return &DAT_008a1ad8;
    }
  }
  return (undefined1 *)0x0;
}

