
undefined2 * __thiscall FUN_005815e0(undefined2 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  puVar2 = (undefined2 *)FUN_00433f60(uVar1);
  *param_1 = *puVar2;
  *(undefined4 *)(param_1 + 2) = 0;
  return param_1;
}

