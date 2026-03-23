
void __thiscall FUN_00842fe0(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_8 [8];
  
  if ((*(int *)(param_1 + 0x18) == 0) || (*(int *)(param_1 + 0x1c) == 0xffff)) {
    if ((*(int *)(param_1 + 0x20) == 0) ||
       ((*(int *)(param_1 + 0x24) == 0xffff || (*(int *)(param_1 + 0x20) == 4)))) {
      puVar2 = (undefined4 *)FUN_008438a0(local_8,param_1,param_3);
      *(undefined4 *)(param_1 + 0x18) = *puVar2;
      *(undefined4 *)(param_1 + 0x1c) = puVar2[1];
      goto LAB_0084304c;
    }
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x24);
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
    uVar1 = FUN_0083e820();
    param_3[1] = uVar1;
  }
LAB_0084304c:
  *param_2 = *(undefined4 *)(param_1 + 0x18);
  param_2[1] = *(undefined4 *)(param_1 + 0x1c);
  return;
}

