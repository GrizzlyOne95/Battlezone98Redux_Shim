
void FUN_004560b0(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)(param_2 + 0x1c);
  uVar2 = *(undefined4 *)(param_2 + 0x20);
  *param_1 = *(undefined4 *)(param_2 + 0x18);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  FUN_0083e885();
  return;
}

