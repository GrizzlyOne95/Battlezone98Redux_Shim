
void __thiscall FUN_005dfbc0(int param_1,undefined4 param_2)

{
  int iVar1;
  
  FUN_00611610(param_2);
  if (*(int *)(param_1 + 0xd8) == 0) {
    *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(*(int *)(param_1 + 8) + 0x68);
  }
  else {
    iVar1 = FUN_005df210();
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(*(int *)(param_1 + 8) + 0xa8);
      *(undefined4 *)(param_1 + 0xdc) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(*(int *)(param_1 + 8) + 0xac);
      if (*(int *)(param_1 + 0xdc) != iVar1) {
        *(int *)(param_1 + 0xdc) = iVar1;
        *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(*(int *)(param_1 + 8) + 0xa0);
        *(uint *)(param_1 + 200) = *(uint *)(*(int *)(param_1 + 8) + 0x98) ^ 0x80000000;
      }
    }
  }
  return;
}

