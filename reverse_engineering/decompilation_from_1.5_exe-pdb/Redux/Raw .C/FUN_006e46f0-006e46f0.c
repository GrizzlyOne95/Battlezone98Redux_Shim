
facet * __thiscall FUN_006e46f0(facet *param_1,undefined4 param_2,uint param_3,undefined1 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854249;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::locale::facet::facet(param_1,param_3);
  local_8 = 0;
  *(undefined ***)param_1 = std::numpunct<char>::vftable;
  FUN_006e5e10(param_2,param_4,uVar1);
  ExceptionList = local_10;
  return param_1;
}

