
void FUN_00718660(undefined1 *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined1 *puStack_9c;
  undefined1 *puStack_98;
  undefined1 *puStack_94;
  undefined1 *puStack_90;
  undefined1 **ppuStack_8c;
  undefined1 *puStack_88;
  uint uStack_84;
  undefined1 local_80 [36];
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
  puStack_c = &LAB_008581e8;
  local_10 = ExceptionList;
  uStack_84 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_88 = &stack0x00000014;
  ppuStack_8c = (undefined1 **)&stack0x00000020;
  puStack_90 = &stack0x00000018;
  puStack_94 = (undefined1 *)0x718699;
  FUN_0071d2a0();
  puStack_88 = (undefined1 *)0x7186a1;
  vector<>();
  local_8 = 0;
  puStack_88 = param_1;
  ppuStack_8c = &local_14;
  puStack_90 = (undefined1 *)0x7186b5;
  FUN_006fc670();
  puStack_88 = param_1;
  ppuStack_8c = &local_18;
  puStack_90 = (undefined1 *)0x7186c5;
  FUN_006fc670();
  while( true ) {
    puStack_88 = (undefined1 *)0x7186d0;
    iVar2 = FUN_007106e0();
    if (iVar2 == -1) break;
    puStack_88 = local_24;
    ppuStack_8c = (undefined1 **)0x7186e5;
    puVar3 = (undefined4 *)base();
    puStack_88 = (undefined1 *)*puVar3;
    ppuStack_8c = (undefined1 **)local_18;
    puStack_90 = local_14;
    puStack_94 = param_1;
    puStack_98 = local_80;
    puStack_9c = local_28;
    puVar3 = (undefined4 *)FUN_007176e0();
    local_14 = (undefined1 *)*puVar3;
    puStack_88 = local_2c;
    ppuStack_8c = (undefined1 **)0x718715;
    puVar3 = (undefined4 *)FUN_00710360();
    local_18 = (undefined1 *)*puVar3;
    puStack_88 = (undefined1 *)0x718722;
    puStack_88 = (undefined1 *)FUN_004b4350();
    ppuStack_8c = (undefined1 **)local_80;
    puStack_90 = (undefined1 *)0x71872c;
    FUN_00723db0();
    puStack_88 = param_1;
    ppuStack_8c = (undefined1 **)local_30;
    puStack_90 = (undefined1 *)0x71873c;
    puVar3 = (undefined4 *)FUN_006fc690();
    puStack_88 = (undefined1 *)*puVar3;
    ppuStack_8c = (undefined1 **)local_18;
    puStack_90 = local_5c;
    puStack_94 = (undefined1 *)0x718752;
    piVar4 = (int *)FUN_0070dbd0();
    puStack_88 = (undefined1 *)piVar4[1];
    ppuStack_8c = (undefined1 **)*piVar4;
    puStack_90 = (undefined1 *)0x718761;
    FUN_00723e60();
  }
  puStack_88 = param_1;
  ppuStack_8c = (undefined1 **)local_34;
  puStack_90 = (undefined1 *)0x718773;
  puVar3 = (undefined4 *)FUN_006fc690();
  puStack_88 = (undefined1 *)*puVar3;
  ppuStack_8c = (undefined1 **)local_18;
  puStack_90 = local_14;
  puStack_94 = param_1;
  puStack_98 = local_80;
  puStack_9c = local_38;
  puVar3 = (undefined4 *)FUN_007176e0();
  local_14 = (undefined1 *)*puVar3;
  puStack_88 = (undefined1 *)0x7187a2;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    local_44 = (undefined1 *)&puStack_90;
    puStack_94 = (undefined1 *)&puStack_90;
    puStack_98 = (undefined1 *)0x7187e3;
    local_48 = FUN_004bb570();
    local_8._0_1_ = 1;
    local_4c = (undefined1 *)&puStack_9c;
    local_1c = local_48;
    local_50 = FUN_004bb540(&puStack_9c);
    local_8._0_1_ = 2;
    local_20 = local_50;
    puVar3 = (undefined4 *)FUN_006fc690(local_54,param_1);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00717840(param_1,*puVar3);
  }
  else {
    puStack_88 = param_1;
    ppuStack_8c = (undefined1 **)local_3c;
    puStack_90 = (undefined1 *)0x7187b6;
    puVar3 = (undefined4 *)FUN_006fc690();
    puStack_88 = (undefined1 *)*puVar3;
    ppuStack_8c = (undefined1 **)local_14;
    puStack_90 = param_1;
    puStack_94 = local_40;
    puStack_98 = (undefined1 *)0x7187cd;
    FUN_00717810();
  }
  local_8 = 0xffffffff;
  puStack_88 = (undefined1 *)0x718840;
  ~vector<>();
  ExceptionList = local_10;
  return;
}

