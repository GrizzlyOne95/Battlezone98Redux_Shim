
void __thiscall FUN_006e4110(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined1 auStack_120 [84];
  undefined4 uStack_cc;
  undefined1 *puStack_c8;
  undefined1 *puStack_c4;
  undefined1 *puStack_c0;
  uint uStack_bc;
  undefined1 local_b8 [8];
  undefined4 local_b0;
  undefined1 *local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined4 local_a0;
  int local_9c;
  undefined1 local_98 [104];
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085420b;
  local_10 = ExceptionList;
  uStack_bc = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(int *)(param_1 + 0x1c) = param_4;
  local_a4 = param_4;
  local_9c = param_1;
  local_14 = uStack_bc;
  if (param_4 == 1) goto LAB_006e4164;
  do {
    puStack_c0 = (undefined1 *)(local_9c + 0x10);
    puStack_c4 = (undefined1 *)(local_9c + 4);
    puStack_c8 = (undefined1 *)0x6e42a0;
    cVar1 = FUN_006e50c0();
    if (cVar1 != '\0') {
LAB_006e42f3:
      puStack_c0 = (undefined1 *)(local_9c + 4);
      puStack_c4 = (undefined1 *)&param_2;
      puStack_c8 = (undefined1 *)0x6e430f;
      FUN_006f0330();
      goto LAB_006e430f;
    }
    puStack_c0 = (undefined1 *)0x6e42b9;
    cVar1 = FUN_006cb280();
    if (cVar1 == '\0') {
      puStack_c0 = (undefined1 *)0x3e3;
      puStack_c4 = (undefined1 *)0x6e42cd;
      FUN_006d8cf0();
      goto LAB_006e42f3;
    }
    puStack_c0 = (undefined1 *)0x6e42d7;
    cVar1 = FUN_004c85a0();
    if (cVar1 != '\0') goto LAB_006e42f3;
    puStack_c0 = (undefined1 *)0x6e42ee;
    FUN_006d7040();
LAB_006e4164:
    puStack_c0 = (undefined1 *)(local_9c + 0x10);
    puStack_c4 = (undefined1 *)(local_9c + 4);
    puStack_c8 = (undefined1 *)&param_2;
    uStack_cc = 0x6e4187;
    FUN_004fa190();
    puStack_c0 = (undefined1 *)(local_9c + 0x10);
    puStack_c4 = (undefined1 *)(local_9c + 4);
    puStack_c8 = (undefined1 *)0x6e41a0;
    cVar1 = FUN_006d7060();
    if (cVar1 != '\0') {
      puStack_c0 = (undefined1 *)&param_2;
      puStack_c4 = local_b8;
      puStack_c8 = (undefined1 *)0x6e41c2;
      FUN_006cb300();
      puStack_c0 = local_30;
      puStack_c4 = (undefined1 *)0x6e41d4;
      FUN_006d7020();
      puStack_c4 = (undefined1 *)0x6e41db;
      FUN_006d72c0();
      puStack_c0 = (undefined1 *)local_9c;
      puStack_c4 = local_30;
      puStack_c8 = (undefined1 *)0x6e41f3;
      FUN_006f13a0();
      goto LAB_006e430f;
    }
  } while (param_4 == 0);
  puStack_c0 = (undefined1 *)0x3;
  puStack_c4 = (undefined1 *)0x6e420c;
  FUN_006d8e00();
  puStack_c0 = (undefined1 *)&param_2;
  local_ac = auStack_120;
  local_b0 = FUN_006e5d70(local_9c);
  puStack_c0 = (undefined1 *)FUN_006f1520(local_98);
  local_8 = 0;
  puStack_c4 = (undefined1 *)0x6e4269;
  local_a8 = puStack_c0;
  local_a0 = puStack_c0;
  FUN_006e4900();
  puStack_c4 = (undefined1 *)0x6e4270;
  FUN_006f1590();
  local_8 = 0xffffffff;
  puStack_c0 = (undefined1 *)0x6e4282;
  FUN_006e4540();
LAB_006e430f:
  ExceptionList = local_10;
  uStack_bc = 0x6e4324;
  FUN_0083e885();
  return;
}

