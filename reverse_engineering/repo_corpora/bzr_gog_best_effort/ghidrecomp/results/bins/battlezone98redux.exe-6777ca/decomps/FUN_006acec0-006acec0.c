
undefined4 * FUN_006acec0(undefined4 param_1,DWORD param_2)

{
  uint uVar1;
  undefined4 uVar2;
  HANDLE pvVar3;
  undefined1 local_24 [8];
  DWORD local_1c;
  DWORD local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008500af;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8e40(param_1);
  local_8 = 0;
  *local_14 = boost::asio::detail::win_iocp_io_service::vftable;
  FUN_00423890(uVar1);
  local_8._0_1_ = 1;
  local_14[6] = 0;
  local_14[7] = 0;
  local_14[8] = 0;
  local_14[9] = 0;
  uVar2 = FUN_006adc80();
  local_14[10] = uVar2;
  FUN_00447eb0(0);
  local_8._0_1_ = 2;
  FUN_00423890();
  local_8._0_1_ = 3;
  local_14[0xd] = 0;
  FUN_006ac110();
  local_8._0_1_ = 4;
  FUN_00423890();
  FUN_006c8f00();
  local_8 = CONCAT31(local_8._1_3_,5);
  if (param_2 == 0xffffffff) {
    local_18 = 0xffffffff;
  }
  else {
    local_18 = param_2;
  }
  pvVar3 = CreateIoCompletionPort((HANDLE)0xffffffff,(HANDLE)0x0,0,local_18);
  local_14[5] = pvVar3;
  if (local_14[5] == 0) {
    local_1c = GetLastError();
    uVar2 = FUN_006abbb0();
    FUN_00416430(local_1c,uVar2);
    FUN_006aba00(local_24,&DAT_008969b0);
  }
  ExceptionList = local_10;
  return local_14;
}

