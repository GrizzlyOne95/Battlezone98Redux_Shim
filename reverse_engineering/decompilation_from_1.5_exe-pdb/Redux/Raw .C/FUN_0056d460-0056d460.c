
void __thiscall FUN_0056d460(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)forward<>(0xc,param_2,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_3;
    puVar1[1] = param_3[1];
    puVar1[2] = param_3[2];
  }
  return;
}

