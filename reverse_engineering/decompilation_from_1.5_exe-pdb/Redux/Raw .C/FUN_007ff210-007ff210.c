
undefined4
FUN_007ff210(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4,
            undefined1 *param_5)

{
  char cVar1;
  int iVar2;
  undefined1 local_18 [18];
  undefined1 local_6;
  undefined1 local_5;
  
  iVar2 = FUN_007df2f0();
  if (iVar2 != 0) {
    std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
              (param_1,param_2,*param_4);
    FUN_00417780(&local_6,*param_5);
    FUN_00417780(&local_5,local_6);
    FUN_007ef2f0(&local_5);
    cVar1 = FUN_007ff0b0(param_1,param_2,local_18,param_4);
    if (cVar1 != '\0') {
      FUN_00800c20(param_5,&local_5);
      return 1;
    }
    FUN_00800c40(param_5,&local_5);
  }
  return 0;
}

