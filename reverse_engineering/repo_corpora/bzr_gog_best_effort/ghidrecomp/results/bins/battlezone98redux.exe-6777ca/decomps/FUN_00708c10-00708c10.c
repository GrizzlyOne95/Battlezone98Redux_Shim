
int __thiscall FUN_00708c10(int param_1,int param_2)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845ab8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = (undefined4 *)FUN_00417780(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  basic_string<>(*puVar1);
  local_8 = 0;
  puVar1 = (undefined4 *)FUN_00417780(param_2 + 4);
  *(undefined4 *)(param_1 + 0x18) = *puVar1;
  ExceptionList = local_10;
  return param_1;
}

