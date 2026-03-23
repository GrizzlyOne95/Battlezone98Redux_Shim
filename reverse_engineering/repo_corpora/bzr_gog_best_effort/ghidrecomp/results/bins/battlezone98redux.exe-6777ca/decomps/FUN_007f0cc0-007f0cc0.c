
int FUN_007f0cc0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_34 [16];
  undefined1 local_24 [16];
  undefined1 local_14 [12];
  int local_8;
  
  puVar1 = (undefined4 *)FUN_00447eb0(param_3);
  uVar2 = FUN_007e27e0(local_14,param_2,*puVar1);
  uVar2 = FUN_007f15b0(local_34,uVar2);
  FUN_007e2820(uVar2);
  FUN_007dfd00(param_1,local_24);
  std::allocator<char>::allocator<char>((allocator<char> *)(local_8 + 0x14));
  return local_8;
}

