
void FUN_004710e0(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int local_38;
  int local_34;
  undefined1 local_29;
  undefined4 *local_28;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008475c0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004f0130(param_1,param_2,param_3);
  local_8 = 0;
  *local_28 = APCClass::vftable;
  FUN_00589430(local_28 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0x6b75762f,0x9fa4327,local_28 + 0x17c,*(undefined4 *)(param_1 + 0x5f0));
  FUN_00589800(0x6b75762f,0x74c3a47c,local_28 + 0x17d,*(undefined4 *)(param_1 + 0x5f4));
  FUN_00589760(0x6b75762f,0x1ee0b4c4,local_28 + 0x17f,*(undefined4 *)(param_1 + 0x5fc));
  FUN_00589800(0x6b75762f,0xe28bf4c8,local_28 + 0x180,*(undefined4 *)(param_1 + 0x600));
  FUN_00589c20(0x6b75762f,0x9c6f5edd,&local_38,0,0);
  if (local_38 == 0 && local_34 == 0) {
    local_28[0x17e] = 0;
    goto LAB_004712b9;
  }
  sprintf(local_24,"%.8s.odf",&local_38);
  if (((char)local_38 == 'a') || ((char)local_38 == 's')) {
LAB_00471253:
    iVar2 = FUN_00481f10(local_24);
    if (iVar2 == 0) goto LAB_00471263;
  }
  else {
    cVar1 = FUN_00571c40();
    if ((cVar1 == '\0') || (DAT_008e8c0d != '\0')) goto LAB_00471253;
LAB_00471263:
    if ((*(char *)(local_28 + 0x33) == 'c') || (*(char *)(local_28 + 0x33) == 's')) {
      local_29 = 0x73;
    }
    else {
      local_29 = 0x61;
    }
    local_38 = CONCAT31(local_38._1_3_,local_29);
  }
  uVar3 = FUN_004e0f70(local_38,local_34);
  local_28[0x17e] = uVar3;
LAB_004712b9:
  FUN_00589800(0x6b75762f,0x1d0683f1,local_28 + 0x181,*(undefined4 *)(param_1 + 0x604));
  FUN_00589800(0x6b75762f,0x282bd2cb,local_28 + 0x182,*(undefined4 *)(param_1 + 0x608));
  FUN_00589800(0x6b75762f,0xcafc923b,local_28 + 0x183,*(undefined4 *)(param_1 + 0x60c));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

