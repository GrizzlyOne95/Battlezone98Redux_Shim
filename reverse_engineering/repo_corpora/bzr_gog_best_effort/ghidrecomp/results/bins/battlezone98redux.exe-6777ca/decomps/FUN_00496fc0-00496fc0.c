
void __thiscall FUN_00496fc0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)forward<>(8,param_2,param_1);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = param_3[1];
    *puVar2 = *param_3;
    puVar2[1] = uVar1;
  }
  return;
}

