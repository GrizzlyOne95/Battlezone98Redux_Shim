
void __thiscall FUN_006e3de0(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined1 auStack_130 [92];
  undefined4 uStack_d4;
  undefined1 *puStack_d0;
  undefined1 *puStack_cc;
  undefined1 *puStack_c8;
  uint uStack_c4;
  undefined1 local_c0 [8];
  undefined4 local_b8;
  undefined1 *local_b4;
  undefined4 local_b0;
  int local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined1 local_a0 [112];
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085419b;
  local_10 = ExceptionList;
  uStack_c4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(int *)(param_1 + 0x1c) = param_4;
  local_ac = param_4;
  local_a4 = param_1;
  local_14 = uStack_c4;
  if (param_4 == 1) goto LAB_006e3e34;
  do {
    puStack_c8 = (undefined1 *)(local_a4 + 0x10);
    puStack_cc = (undefined1 *)(local_a4 + 4);
    puStack_d0 = (undefined1 *)0x6e3f70;
    cVar1 = FUN_006e50c0();
    if (cVar1 != '\0') {
LAB_006e3fc3:
      puStack_c8 = (undefined1 *)(local_a4 + 4);
      puStack_cc = (undefined1 *)&param_2;
      puStack_d0 = (undefined1 *)0x6e3fdf;
      FUN_006f0290();
      goto LAB_006e3fdf;
    }
    puStack_c8 = (undefined1 *)0x6e3f89;
    cVar1 = FUN_006cb280();
    if (cVar1 == '\0') {
      puStack_c8 = (undefined1 *)0x3e3;
      puStack_cc = (undefined1 *)0x6e3f9d;
      FUN_006d8cf0();
      goto LAB_006e3fc3;
    }
    puStack_c8 = (undefined1 *)0x6e3fa7;
    cVar1 = FUN_004c85a0();
    if (cVar1 != '\0') goto LAB_006e3fc3;
    puStack_c8 = (undefined1 *)0x6e3fbe;
    FUN_006d7040();
LAB_006e3e34:
    puStack_c8 = (undefined1 *)(local_a4 + 0x10);
    puStack_cc = (undefined1 *)(local_a4 + 4);
    puStack_d0 = (undefined1 *)&param_2;
    uStack_d4 = 0x6e3e57;
    FUN_004fa190();
    puStack_c8 = (undefined1 *)(local_a4 + 0x10);
    puStack_cc = (undefined1 *)(local_a4 + 4);
    puStack_d0 = (undefined1 *)0x6e3e70;
    cVar1 = FUN_006d7060();
    if (cVar1 != '\0') {
      puStack_c8 = (undefined1 *)&param_2;
      puStack_cc = local_c0;
      puStack_d0 = (undefined1 *)0x6e3e92;
      FUN_006cb300();
      puStack_c8 = local_30;
      puStack_cc = (undefined1 *)0x6e3ea4;
      FUN_006d7020();
      puStack_cc = (undefined1 *)0x6e3eab;
      FUN_006d72c0();
      puStack_c8 = (undefined1 *)local_a4;
      puStack_cc = local_30;
      puStack_d0 = (undefined1 *)0x6e3ec3;
      FUN_006f1110();
      goto LAB_006e3fdf;
    }
  } while (param_4 == 0);
  puStack_c8 = (undefined1 *)0x3;
  puStack_cc = (undefined1 *)0x6e3edc;
  FUN_006d8e00();
  puStack_c8 = (undefined1 *)&param_2;
  local_b4 = auStack_130;
  local_b8 = FUN_006e5cd0(local_a4);
  puStack_c8 = (undefined1 *)FUN_006f1290(local_a0);
  local_8 = 0;
  puStack_cc = (undefined1 *)0x6e3f39;
  local_b0 = puStack_c8;
  local_a8 = puStack_c8;
  FUN_006e4900();
  puStack_cc = (undefined1 *)0x6e3f40;
  FUN_006f1300();
  local_8 = 0xffffffff;
  puStack_c8 = (undefined1 *)0x6e3f52;
  FUN_006e4520();
LAB_006e3fdf:
  ExceptionList = local_10;
  uStack_c4 = 0x6e3ff4;
  FUN_0083e885();
  return;
}

