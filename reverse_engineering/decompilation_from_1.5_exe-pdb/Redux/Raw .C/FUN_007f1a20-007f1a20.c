
int FUN_007f1a20(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_38 [20];
  undefined1 local_24 [16];
  undefined1 local_14 [12];
  int local_8;
  
  puVar1 = (undefined4 *)FUN_00447eb0(param_3);
  uVar2 = FUN_007e27e0(local_14,param_2,*puVar1);
  uVar2 = FUN_007f2510(local_38,uVar2);
  FUN_007f2530(uVar2);
  FUN_007f1d80(param_1,local_24);
  std::allocator<char>::allocator<char>((allocator<char> *)(local_8 + 0x14));
  return local_8;
}

