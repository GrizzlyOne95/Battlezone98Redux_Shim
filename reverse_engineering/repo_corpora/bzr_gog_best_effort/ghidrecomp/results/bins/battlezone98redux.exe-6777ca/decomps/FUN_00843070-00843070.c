
void __thiscall FUN_00843070(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_8 [8];
  
  if ((*(int *)(param_1 + 0x20) == 0) || (*(int *)(param_1 + 0x24) == 0xffff)) {
    puVar2 = (undefined4 *)FUN_00843a50(local_8,param_1,param_3);
    *(undefined4 *)(param_1 + 0x20) = *puVar2;
    *(undefined4 *)(param_1 + 0x24) = puVar2[1];
  }
  else if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
    uVar1 = FUN_0083e820();
    param_3[1] = uVar1;
  }
  *param_2 = *(undefined4 *)(param_1 + 0x20);
  param_2[1] = *(undefined4 *)(param_1 + 0x24);
  return;
}

