
void FUN_00479c40(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int local_34;
  int local_30;
  undefined4 *local_2c;
  undefined1 local_25;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008478c0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_0047ffd0(param_1,param_2,param_3);
  local_8 = 0;
  *local_2c = BarracksClass::vftable;
  FUN_00589430(local_2c + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589760(0x66e9b4de,0x8588af8c,local_2c + 0x58,*(undefined4 *)(param_1 + 0x160));
  local_30 = 0x6f6c;
  local_34 = CONCAT31(0x697073,*(undefined1 *)(local_2c + 0x33));
  FUN_00589c20(0x66e9b4de,0xde331a5a,&local_34,local_34,0x6f6c);
  if (local_34 == 0 && local_30 == 0) {
    local_2c[0x59] = 0;
    goto LAB_00479db4;
  }
  sprintf(local_24,"%.8s.odf",&local_34,uVar2);
  if (((char)local_34 == 'a') || ((char)local_34 == 's')) {
LAB_00479d4e:
    iVar3 = FUN_00481f10(local_24);
    if (iVar3 == 0) goto LAB_00479d5e;
  }
  else {
    cVar1 = FUN_00571c40();
    if ((cVar1 == '\0') || (DAT_008e8c0d != '\0')) goto LAB_00479d4e;
LAB_00479d5e:
    if ((*(char *)(local_2c + 0x33) == 'c') || (*(char *)(local_2c + 0x33) == 's')) {
      local_25 = 0x73;
    }
    else {
      local_25 = 0x61;
    }
    local_34 = CONCAT31(local_34._1_3_,local_25);
  }
  uVar4 = FUN_004e0f70(local_34,local_30);
  local_2c[0x59] = uVar4;
LAB_00479db4:
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

