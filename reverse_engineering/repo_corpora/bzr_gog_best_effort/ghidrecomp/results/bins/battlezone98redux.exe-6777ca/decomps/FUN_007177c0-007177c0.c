
undefined4 * __thiscall FUN_007177c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  
  *param_1 = param_2;
  param_1[1] = param_3;
  cVar2 = FUN_00710380();
  if (cVar2 == '\0') {
    puVar3 = (undefined4 *)allocator<>(&param_2);
    uVar1 = puVar3[1];
    param_1[2] = *puVar3;
    param_1[3] = uVar1;
  }
  return param_1;
}

