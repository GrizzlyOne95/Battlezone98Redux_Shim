
undefined4 __thiscall FUN_006f6650(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_c [4];
  int local_8;
  
  uVar2 = *(undefined4 *)(param_1 + 0x1c);
  local_8 = param_1;
  puVar1 = (undefined4 *)FUN_0041fc60(local_c);
  FUN_006f72a0(*(undefined1 *)(local_8 + 0xc),local_8 + 0x10,*(undefined4 *)(local_8 + 0x18),*puVar1
               ,uVar2);
  return param_2;
}

