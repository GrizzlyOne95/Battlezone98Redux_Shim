
undefined4 FUN_00710540(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)forward<>(4,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_2;
  }
  return 2;
}

