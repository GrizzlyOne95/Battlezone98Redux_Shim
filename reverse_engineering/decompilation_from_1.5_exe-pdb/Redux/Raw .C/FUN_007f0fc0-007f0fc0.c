
int FUN_007f0fc0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_20 [8];
  undefined1 local_18 [12];
  int local_c;
  undefined1 local_6 [2];
  
  puVar1 = (undefined4 *)FUN_00447eb0(param_3);
  uVar2 = FUN_007e27e0(local_18,param_2,*puVar1);
  uVar2 = FUN_007f1850(local_20,uVar2);
  FUN_007f1870(uVar2);
  FUN_007f1470(param_1,local_6);
  std::allocator<char>::allocator<char>((allocator<char> *)(local_c + 8));
  return local_c;
}

