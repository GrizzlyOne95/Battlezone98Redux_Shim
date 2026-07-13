
void FUN_008187a0(undefined4 param_1,char param_2,char param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_160 [8];
  undefined1 local_158 [8];
  undefined1 local_150 [8];
  undefined1 local_148 [8];
  undefined1 local_140 [8];
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  uint *local_12c;
  int local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined1 local_118 [8];
  int local_110;
  int local_10c;
  size_t local_108;
  int local_104;
  uint local_100;
  uint local_fc;
  int local_f8;
  undefined4 local_f4;
  void *local_f0;
  void *local_ec;
  uint *local_e8;
  undefined1 local_e4 [28];
  undefined1 local_c8 [24];
  undefined1 local_b0 [28];
  uint local_94;
  undefined1 local_90 [24];
  undefined1 local_78 [100];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864dc1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_100 = 0;
  local_14 = uVar1;
  FUN_00818fa0(uVar1);
  local_8 = 0;
  local_108 = 0x1000;
  for (local_104 = 3; local_f0 = (void *)0x0, local_104 != 0; local_104 = local_104 + -1) {
    local_f0 = calloc(1,local_108);
    local_110 = GetAdaptersAddresses(0,0x3e,0,local_f0,&local_108);
    if (local_110 != 0x6f) break;
    free(local_f0);
  }
  local_128 = local_110;
  if (local_110 == 0) {
    for (local_ec = local_f0; local_ec != (void *)0x0; local_ec = *(void **)((int)local_ec + 8)) {
      local_f8 = 0;
      for (local_e8 = *(uint **)((int)local_ec + 0x10); local_e8 != (uint *)0x0;
          local_e8 = (uint *)local_e8[2]) {
        if (local_f8 == 0) {
          local_f8 = *(int *)((int)local_ec + 0x8c);
        }
        else {
          local_f8 = *(int *)(local_f8 + 8);
        }
        if (((param_2 != '\0') && (*(short *)local_e8[3] == 2)) ||
           ((param_3 != '\0' && (*(short *)local_e8[3] == 0x17)))) {
          local_134 = 100;
          local_10c = WSAAddressToStringA(local_e8[3],local_e8[4],0,local_78,&local_134);
          if (local_10c == -1) {
            local_10c = WSAGetLastError();
          }
          else {
            basic_string<>(local_78);
            local_8._0_1_ = 1;
            basic_string<>(*(undefined4 *)((int)local_ec + 0xc));
            local_8._0_1_ = 2;
            local_f4 = FUN_00819000(local_c8);
            local_8 = CONCAT31(local_8._1_3_,1);
            ~basic_string<>();
            if (*(int *)((int)local_ec + 0x44) == 1) {
              local_120 = FUN_00818e50(local_148,0);
              FUN_008190e0(1);
              FUN_00417c60();
            }
            if (*(int *)((int)local_ec + 0x40) == 0x18) {
              local_11c = FUN_00818e50(local_160,1);
              FUN_008190e0(1);
              FUN_00417c60();
            }
            if ((*(uint *)((int)local_ec + 0x38) & 0x10) == 0) {
              local_130 = FUN_00818e50(local_158,4);
              FUN_008190e0(1);
              FUN_00417c60();
            }
            local_138 = FUN_00818e50(local_140,8);
            FUN_008190e0(1);
            FUN_00417c60();
            local_124 = FUN_00818e50(local_150,3);
            FUN_008190e0(1);
            FUN_00417c60();
            local_fc = 0;
            if (*local_e8 < 0x30) {
              if (local_f8 != 0) {
                local_fc = *(uint *)(local_f8 + 0x14);
              }
            }
            else {
              local_12c = local_e8;
              local_fc = (uint)(byte)local_e8[0xb];
            }
            if ((*(short *)local_e8[3] == 2) && (0x20 < local_fc)) {
              local_fc = 0;
            }
            FUN_00818cd0();
            uVar2 = FUN_00818780(local_e4,local_90);
            FUN_00759f10(uVar2);
            local_94 = local_fc;
            FUN_00818e90(local_b0);
            local_8 = local_8 & 0xffffff00;
            ~basic_string<>();
          }
        }
      }
    }
    if (local_f0 != (void *)0x0) {
      free(local_f0);
    }
    FUN_00818fd0(local_118);
    local_100 = local_100 | 1;
    local_8 = 0xffffffff;
    FUN_00818cb0();
  }
  else {
    if (local_f0 != (void *)0x0) {
      free(local_f0);
    }
    FUN_00818fa0(uVar1);
    local_100 = local_100 | 1;
    local_8 = 0xffffffff;
    FUN_00818cb0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

