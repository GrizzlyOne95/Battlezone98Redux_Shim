
undefined4
FUN_0080a160(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined1 local_1c [12];
  undefined4 local_10;
  undefined4 local_8;
  
  iVar2 = FUN_007df2f0();
  if (iVar2 != 0) {
    std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
              (param_1,param_2,param_4);
    local_10 = FUN_00417780(param_5);
    local_8 = FUN_00417780(local_10);
    FUN_007ef2f0(local_8);
    cVar1 = FUN_007ff0b0(param_1,param_2,local_1c,param_4);
    if (cVar1 != '\0') {
      FUN_007ff1d0(param_5,local_8);
      return 1;
    }
    FUN_007ff1f0(param_5,local_8);
  }
  return 0;
}

