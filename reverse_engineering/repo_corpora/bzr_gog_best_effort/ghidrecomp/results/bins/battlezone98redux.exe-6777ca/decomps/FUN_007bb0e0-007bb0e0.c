
void __thiscall
FUN_007bb0e0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  XImage *this;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086172f;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007bb060(param_3,param_4,param_2);
  local_8 = 0;
  *param_1 = boost::filesystem::filesystem_error::vftable;
  FUN_0066ae30();
  local_8._1_3_ = (undefined3)((uint)local_8 >> 8);
  local_8._0_1_ = 2;
  this = operator_new(0x48);
  local_8._0_1_ = 3;
  if (this == (XImage *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = CMFCRibbonInfo::XImage::XImage(this);
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_007bd680(local_20);
  FUN_007bb1aa();
  return;
}

