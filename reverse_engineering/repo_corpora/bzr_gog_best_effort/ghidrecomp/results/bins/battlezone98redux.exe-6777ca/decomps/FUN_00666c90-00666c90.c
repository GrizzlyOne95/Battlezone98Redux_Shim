
undefined4 * __thiscall FUN_00666c90(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  puVar2 = (undefined4 *)FUN_00433f60(uVar1);
  *param_1 = *puVar2;
  *(undefined1 *)(param_1 + 1) = 0;
  return param_1;
}

