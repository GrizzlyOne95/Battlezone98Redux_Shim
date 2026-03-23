
void FUN_004a7930(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x120);
  if ((puVar1 != (undefined4 *)0x0) && (puVar1 != (undefined4 *)0x0)) {
    (**(code **)*puVar1)(1);
  }
  *(undefined4 *)(param_1 + 0x120) = 0;
  FUN_0062f240(param_1);
  return;
}

