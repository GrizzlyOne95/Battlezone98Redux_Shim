
undefined4 * FUN_006b0690(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_30 [8];
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  void *local_1c;
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008503f0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c9480(param_1);
  local_8 = 0;
  *local_18 = boost::asio::detail::select_reactor::vftable;
  uVar2 = FUN_006ac540(param_1,uVar1);
  local_18[5] = uVar2;
  FUN_006ac110();
  local_8._0_1_ = 1;
  FUN_006b00f0();
  local_8._0_1_ = 2;
  FUN_0083ead2(local_18 + 0xe,0x1c,4,CMFCScanlinerBitmap::CMFCScanlinerBitmap,
               FID_conflict__CAtlWinModule);
  local_8._0_1_ = 3;
  FUN_0083ead2(local_18 + 0x2a,0xc,3,FUN_006ae590,FUN_006ae620);
  local_8._0_1_ = 4;
  FUN_00423890();
  *(undefined1 *)(local_18 + 0x34) = 0;
  local_18[0x35] = 0;
  *(undefined1 *)(local_18 + 0x36) = 0;
  FUN_00417460();
  local_8._0_1_ = 5;
  local_1c = operator_new(0xc);
  local_8._0_1_ = 6;
  if (local_1c == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_24 = local_18;
    uVar2 = 0;
    puVar3 = (undefined4 *)FUN_006d8f40(local_30,FUN_006b11e0,&local_24,0);
    local_20 = FUN_006d8f60(*puVar3,puVar3[1],uVar2);
  }
  local_28 = local_20;
  local_18[0x35] = local_20;
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_004bb3d0();
  ExceptionList = local_10;
  return local_18;
}

