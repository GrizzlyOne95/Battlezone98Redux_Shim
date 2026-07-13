
void FUN_00718220(undefined1 *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined1 *puStack_a0;
  undefined1 *puStack_9c;
  undefined1 *puStack_98;
  undefined1 *puStack_94;
  undefined1 **ppuStack_90;
  undefined1 *puStack_8c;
  uint uStack_88;
  undefined1 local_70 [20];
  undefined1 local_5c [8];
  undefined1 local_54 [4];
  undefined4 local_50;
  undefined1 *local_4c;
  undefined4 local_48;
  undefined1 *local_44;
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857668;
  local_10 = ExceptionList;
  uStack_88 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_8c = &stack0x00000014;
  ppuStack_90 = (undefined1 **)&stack0x00000024;
  puStack_94 = &stack0x0000001c;
  puStack_98 = (undefined1 *)0x718259;
  FUN_00711890();
  puStack_8c = (undefined1 *)0x718261;
  vector<>();
  local_8 = 0;
  puStack_8c = param_1;
  ppuStack_90 = &local_14;
  puStack_94 = (undefined1 *)0x718275;
  FUN_006fc670();
  puStack_8c = param_1;
  ppuStack_90 = &local_18;
  puStack_94 = (undefined1 *)0x718285;
  FUN_006fc670();
  while( true ) {
    puStack_8c = (undefined1 *)0x718290;
    iVar2 = FUN_007106e0();
    if (iVar2 == -1) break;
    puStack_8c = local_24;
    ppuStack_90 = (undefined1 **)0x7182a5;
    puVar3 = (undefined4 *)base();
    puStack_8c = (undefined1 *)*puVar3;
    ppuStack_90 = (undefined1 **)local_18;
    puStack_94 = local_14;
    puStack_98 = param_1;
    puStack_9c = local_70;
    puStack_a0 = local_28;
    puVar3 = (undefined4 *)FUN_007176e0();
    local_14 = (undefined1 *)*puVar3;
    puStack_8c = local_2c;
    ppuStack_90 = (undefined1 **)0x7182d5;
    puVar3 = (undefined4 *)FUN_00710360();
    local_18 = (undefined1 *)*puVar3;
    puStack_8c = (undefined1 *)0x7182e2;
    puStack_8c = (undefined1 *)FUN_004b4350();
    ppuStack_90 = (undefined1 **)local_70;
    puStack_94 = (undefined1 *)0x7182ec;
    FUN_00723d00();
    puStack_8c = param_1;
    ppuStack_90 = (undefined1 **)local_30;
    puStack_94 = (undefined1 *)0x7182fc;
    puVar3 = (undefined4 *)FUN_006fc690();
    puStack_8c = (undefined1 *)*puVar3;
    ppuStack_90 = (undefined1 **)local_18;
    puStack_94 = local_5c;
    puStack_98 = (undefined1 *)0x718312;
    piVar4 = (int *)FUN_006fc6b0();
    puStack_8c = (undefined1 *)piVar4[1];
    ppuStack_90 = (undefined1 **)*piVar4;
    puStack_94 = (undefined1 *)0x718321;
    FUN_007177c0();
  }
  puStack_8c = param_1;
  ppuStack_90 = (undefined1 **)local_34;
  puStack_94 = (undefined1 *)0x718333;
  puVar3 = (undefined4 *)FUN_006fc690();
  puStack_8c = (undefined1 *)*puVar3;
  ppuStack_90 = (undefined1 **)local_18;
  puStack_94 = local_14;
  puStack_98 = param_1;
  puStack_9c = local_70;
  puStack_a0 = local_38;
  puVar3 = (undefined4 *)FUN_007176e0();
  local_14 = (undefined1 *)*puVar3;
  puStack_8c = (undefined1 *)0x718362;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    local_44 = (undefined1 *)&puStack_94;
    puStack_98 = (undefined1 *)&puStack_94;
    puStack_9c = (undefined1 *)0x7183a3;
    local_48 = FUN_004bb570();
    local_8._0_1_ = 1;
    local_4c = (undefined1 *)&puStack_a0;
    local_1c = local_48;
    local_50 = FUN_004bb540(&puStack_a0);
    local_8._0_1_ = 2;
    local_20 = local_50;
    puVar3 = (undefined4 *)FUN_006fc690(local_54,param_1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00717840(param_1,*puVar3);
  }
  else {
    puStack_8c = param_1;
    ppuStack_90 = (undefined1 **)local_3c;
    puStack_94 = (undefined1 *)0x718376;
    puVar3 = (undefined4 *)FUN_006fc690();
    puStack_8c = (undefined1 *)*puVar3;
    ppuStack_90 = (undefined1 **)local_14;
    puStack_94 = param_1;
    puStack_98 = local_40;
    puStack_9c = (undefined1 *)0x71838d;
    FUN_00717810();
  }
  local_8 = 0xffffffff;
  puStack_8c = (undefined1 *)0x718400;
  ~vector<>();
  ExceptionList = local_10;
  return;
}

