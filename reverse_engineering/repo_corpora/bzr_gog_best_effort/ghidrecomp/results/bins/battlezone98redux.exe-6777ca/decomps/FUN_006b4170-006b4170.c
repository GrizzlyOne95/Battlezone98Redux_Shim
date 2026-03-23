
undefined4 * __thiscall FUN_006b4170(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850813;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006ca3c0(param_2);
  local_8 = 0;
  *param_1 = boost::asio::detail::strand_service::vftable;
  uVar2 = FUN_006ac540(param_2,uVar1);
  param_1[5] = uVar2;
  FUN_006ac110();
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_0083ead2(param_1 + 0xc,4,0xc1,FUN_006b4250,FUN_006ca3f0);
  param_1[0xcd] = 0;
  ExceptionList = local_10;
  return param_1;
}

