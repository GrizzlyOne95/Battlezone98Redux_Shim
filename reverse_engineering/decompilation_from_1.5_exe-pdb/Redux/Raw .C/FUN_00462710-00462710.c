
uint __thiscall FUN_00462710(char *param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (*param_1 == '\0') {
    while (*(int *)(param_1 + 0x28) == -1) {
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      if (*(int *)(param_1 + 8) < *(int *)(param_1 + 0xc)) {
        *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 4);
        *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
        if (*(int *)(param_1 + 0x14) < *(int *)(param_1 + 0x18)) {
          return (uint)param_1 & 0xffffff00;
        }
      }
      *(undefined4 *)(param_1 + 0x28) =
           *(undefined4 *)
            (*(int *)(param_1 + 0x24) +
            (*(int *)(param_1 + 0x18) * *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0xc)) * 4);
    }
    iVar1 = *(int *)(param_1 + 0x20) + *(int *)(param_1 + 0x28) * 8;
    *param_2 = iVar1;
    uVar2 = *(undefined4 *)(iVar1 + 4);
    *(undefined4 *)(param_1 + 0x28) = uVar2;
    uVar3 = CONCAT31((int3)((uint)uVar2 >> 8),1);
  }
  else {
    uVar3 = (uint)param_1 & 0xffffff00;
  }
  return uVar3;
}

