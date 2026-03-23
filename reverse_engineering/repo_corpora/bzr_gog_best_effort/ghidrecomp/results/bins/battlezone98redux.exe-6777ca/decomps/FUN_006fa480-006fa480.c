
int __thiscall FUN_006fa480(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853a3b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 8));
  local_8 = 0;
  uVar3 = 0;
  uVar4 = 1;
  uVar2 = FUN_00417780(param_2,1,0,uVar1);
  FUN_0070bae0(uVar2,uVar4,uVar3);
  ExceptionList = local_10;
  return param_1;
}

