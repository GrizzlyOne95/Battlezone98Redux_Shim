
int __thiscall FUN_0042aa50(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  FUN_0042d860(uVar1);
  puVar2 = (undefined4 *)FUN_00417780(param_3);
  *(undefined4 *)(param_1 + 0xc) = *puVar2;
  return param_1;
}

