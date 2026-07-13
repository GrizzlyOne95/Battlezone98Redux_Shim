
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_00773f00(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_1174 [12];
  undefined1 local_1168 [4];
  undefined4 local_1164;
  undefined4 local_1160;
  undefined4 local_115c;
  undefined4 local_1158;
  undefined4 local_1154;
  undefined4 local_1150;
  undefined4 local_114c;
  undefined4 local_1148;
  undefined4 local_1144;
  undefined4 local_1140;
  int local_113c;
  undefined4 local_1138;
  undefined4 local_1134;
  undefined4 local_1130;
  undefined4 local_112c;
  int *local_1128;
  int *local_1124;
  uint local_1120;
  undefined1 local_111c [24];
  undefined1 local_1104 [24];
  undefined1 local_10ec [24];
  undefined1 local_10d4 [24];
  undefined1 local_10bc [24];
  undefined1 local_10a4 [48];
  undefined1 local_1074 [24];
  undefined1 local_105c [24];
  undefined1 local_1044 [48];
  undefined1 local_1014 [4096];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e2f9;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1120 = 0;
  local_14 = uVar2;
  iVar3 = FUN_00773a50(uVar2);
  if (iVar3 != 0) {
    local_1124 = (int *)FUN_00773a50(uVar2);
    local_113c = (**(code **)(*local_1124 + 0xe4))(&local_1164,1);
    if (local_113c != 0) {
      local_1128 = (int *)FUN_00773a50(uVar2);
      cVar1 = (**(code **)(*local_1128 + 0xec))
                        (local_1164,local_1160,local_1174,local_1014,0x1000,local_1168);
      if (cVar1 != '\0') {
        FUN_00426a60(local_1014,0);
        local_8 = 0;
        local_114c = FUN_00841100(local_10a4);
        local_8._0_1_ = 1;
        local_1144 = local_114c;
        FUN_00417fd0(param_1);
        local_1120 = local_1120 | 1;
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_004180b0();
        local_8 = 0xffffffff;
        FUN_004180b0();
        goto LAB_00774268;
      }
    }
  }
  FUN_00426a60(&DAT_02cf0000,0);
  local_8 = 2;
  FUN_00426a60("301650",0);
  local_8._0_1_ = 3;
  FUN_00426a60("content",0);
  local_8._0_1_ = 4;
  FUN_00426a60("workshop",0);
  local_8._0_1_ = 5;
  local_1158 = FUN_00841100(local_1104);
  local_8._0_1_ = 6;
  local_1130 = local_1158;
  local_1138 = FUN_00841100(local_111c);
  local_8._0_1_ = 7;
  local_1134 = local_1138;
  local_1148 = FUN_00662ec0(local_10ec,local_1138,local_1074);
  local_8._0_1_ = 8;
  local_1140 = local_1148;
  local_115c = FUN_00662ec0(local_10d4,local_1148,local_1044);
  local_8._0_1_ = 9;
  local_1154 = local_115c;
  local_1150 = FUN_00662ec0(local_10bc,local_115c,local_105c);
  local_8._0_1_ = 10;
  local_112c = local_1150;
  FUN_00773a70(local_1150);
  local_8._0_1_ = 9;
  FUN_004180b0();
  local_8._0_1_ = 8;
  FUN_004180b0();
  local_8._0_1_ = 7;
  FUN_004180b0();
  local_8._0_1_ = 6;
  FUN_004180b0();
  local_8._0_1_ = 5;
  FUN_004180b0();
  local_8._0_1_ = 4;
  FUN_004180b0();
  local_8._0_1_ = 3;
  FUN_004180b0();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004180b0();
  FUN_00417fd0(param_1);
  local_1120 = local_1120 | 1;
  local_8 = 0xffffffff;
  FUN_004180b0();
LAB_00774268:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

