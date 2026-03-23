
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0077e990(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  float fStack0000000c;
  
  fStack0000000c = 5.0;
  FUN_0077d5e0(param_2);
  DAT_02cc50e0 = fStack0000000c;
  DAT_02cc50e4 = 1.0 / fStack0000000c;
  _DAT_02cc50e8 = param_1;
  FUN_0077e490();
  FUN_0077e230();
  FUN_0077dcb0();
  FUN_0077d690();
  uVar1 = FUN_0077d400();
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(uVar1);
  FUN_0067e0e0();
  return 1;
}

