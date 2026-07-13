
void FUN_0078c6c0(void)

{
  uint uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  undefined4 uVar4;
  code *pcVar5;
  undefined1 auStack_dc [164];
  undefined4 local_38;
  undefined4 local_34;
  undefined1 *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085eaf3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xec) {
    local_30 = (undefined1 *)0x0;
  }
  else {
    local_30 = auStack_dc;
  }
  pcVar5 = FUN_004bc8c0;
  iVar2 = FUN_00764870(FUN_004bc8c0,uVar1);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_30,"cUI_MainScreen::Click_MultiPlayer calling isNetworkInit() :");
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  local_38 = GetPolicy(local_2c);
  local_8._0_1_ = 1;
  local_34 = local_38;
  uVar4 = FUN_0041f870();
  FUN_007d6a70(uVar4);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  iVar2 = FUN_00764870();
  if (iVar2 != 0) {
    iVar2 = FUN_00764760();
    if (iVar2 == 0) {
      FUN_007d6a70("cUI_MainScreen::Click_MultiPlayer getLobby() == NULL");
    }
    else {
      FUN_007c7930(0xe);
    }
  }
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

