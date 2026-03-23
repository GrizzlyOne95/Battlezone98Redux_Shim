
XImage * __fastcall FUN_0076dcc0(XImage *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d50e;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  CMFCRibbonInfo::XImage::XImage(param_1);
  local_8 = 0;
  basic_string<>(uVar1);
  local_8._0_1_ = 1;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  basic_string<>();
  ExceptionList = local_10;
  return param_1;
}

