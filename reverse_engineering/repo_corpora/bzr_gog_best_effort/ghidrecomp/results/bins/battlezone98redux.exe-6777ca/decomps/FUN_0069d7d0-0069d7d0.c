
undefined4 * __thiscall
FUN_0069d7d0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fa08;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00698b40(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = Mapgrid_Goal::vftable;
  param_1[0x10] = param_2;
  param_1[0x11] = param_3;
  param_1[0xe] = param_4;
  param_1[0xf] = param_5;
  FUN_0069d940();
  param_1[10] = 2;
  param_1[0x20] = 0xbf800000;
  ExceptionList = local_10;
  return param_1;
}

