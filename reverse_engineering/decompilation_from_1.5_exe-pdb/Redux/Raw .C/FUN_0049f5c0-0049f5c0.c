
void FUN_0049f5c0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_8c [8];
  int local_84;
  int local_80;
  char local_7c [4];
  char *local_78;
  undefined4 local_74;
  int local_6c;
  char local_64 [32];
  char local_44 [16];
  char local_34 [16];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008495d0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  sprintf(local_44,"%.8s.odf",&param_2,local_14);
  sprintf(local_64,"%.8s_mp.odf",&param_2);
  cVar1 = FUN_0049f490();
  if ((cVar1 == '\0') || (iVar2 = FUN_00481f10(local_64), iVar2 == 0)) {
    local_78 = local_44;
  }
  else {
    local_78 = local_64;
  }
  FUN_00589430(local_78);
  local_8 = 0;
  cVar1 = FUN_0047b6c0(0xe4350540,0xcf7a27e8,param_1 + 1,0);
  if (cVar1 == '\0') {
    cVar1 = FUN_0047b6c0(0xd3dd9cec,0x45a8bc04,param_1 + 1,0);
    if (cVar1 == '\0') {
      FUN_0047b6c0(0xd3dd9cec,0x92d04727,local_34,0);
      iVar2 = _stricmp(local_34,"wpnpower");
      if (iVar2 == 0) {
        FUN_00589c20(0x397a9ac1,0xfbf47dba,local_8c,0,0);
        sprintf(local_24,"%.8s.odf",local_8c);
        FUN_00589430(local_24);
        local_8._0_1_ = 1;
        FUN_0047b6c0(0xacda90ab,0xf429d8cf,param_1 + 1,0);
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_00589530();
      }
    }
    param_1[6] = 0;
    iVar2 = FUN_004e0f70(param_2,param_3);
    param_1[7] = iVar2;
    param_1[5] = *(int *)(*param_1 + 0x14);
  }
  else {
    if (*param_1 == 0) {
      local_74 = 0;
    }
    else {
      local_74 = *(undefined4 *)(*param_1 + 0x14);
    }
    FUN_00589760(0xe4350540,0xcb5fbcaa,param_1 + 5,local_74);
    pvVar3 = calloc(10,0x20);
    param_1[6] = (int)pvVar3;
    param_1[7] = 0;
    for (local_6c = 0; local_6c < 10; local_6c = local_6c + 1) {
      *(int **)(param_1[6] + local_6c * 0x20) = param_1;
      sprintf(local_7c,"%d",local_6c + 1);
      uVar7 = 0;
      uVar6 = 0;
      piVar5 = &local_84;
      uVar4 = FUN_00446460(local_7c,0xf1915444,piVar5,0,0);
      FUN_00589c20(0xe4350540,uVar4,piVar5,uVar6,uVar7);
      if (local_84 != 0 || local_80 != 0) {
        FUN_0049f5c0(local_6c * 0x20 + param_1[6],local_84,local_80);
      }
    }
  }
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

