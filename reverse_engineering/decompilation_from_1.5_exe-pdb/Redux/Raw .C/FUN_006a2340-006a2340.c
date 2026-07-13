
void FUN_006a2340(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined8 local_68;
  char *local_60;
  int local_5c;
  int local_50;
  undefined1 local_4c [16];
  char local_3c [16];
  char local_2c [16];
  char local_1c [8];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fb80;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  sprintf(local_2c,"%.8s.odf",&param_1,uVar2);
  iVar3 = FUN_00481f10(local_2c);
  if (iVar3 != 0) {
    FUN_00589430(local_2c);
    local_8 = 0;
    cVar1 = FUN_0047b6c0(0xd3dd9cec,0x92d04727,local_4c,0);
    if (cVar1 == '\0') {
      sprintf(local_3c,"%.8s_mp.odf",&param_1,uVar2);
      cVar1 = FUN_0049f490();
      if ((cVar1 == '\0') || (iVar3 = FUN_00481f10(local_3c), iVar3 == 0)) {
        local_60 = local_2c;
      }
      else {
        local_60 = local_3c;
      }
      FUN_00589430(local_60);
      local_8._0_1_ = 1;
      local_50 = 1;
      while( true ) {
        sprintf(local_1c,"%d",local_50);
        local_68 = 0;
        uVar7 = 0;
        uVar6 = 0;
        puVar5 = &local_68;
        uVar4 = FUN_00446460(local_1c,0xf1915444,puVar5,0,0);
        cVar1 = FUN_00589c20(0xe4350540,uVar4,puVar5,uVar6,uVar7);
        if (cVar1 == '\0') break;
        if ((int)local_68 != 0 || local_68._4_4_ != 0) {
          FUN_006a2340((int)local_68,local_68._4_4_);
        }
        local_50 = local_50 + 1;
      }
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00589530();
    }
    else {
      local_5c = FUN_004e0f70(param_1,param_2);
      if (local_5c != 0) {
        FUN_006a2200(local_5c,0);
      }
    }
    local_8 = 0xffffffff;
    FUN_00589530();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

