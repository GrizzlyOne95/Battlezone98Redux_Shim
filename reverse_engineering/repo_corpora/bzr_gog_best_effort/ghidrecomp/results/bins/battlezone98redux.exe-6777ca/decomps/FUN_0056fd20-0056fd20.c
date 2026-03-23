
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0056fd20(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_9c [16];
  undefined1 local_8c [16];
  undefined1 local_7c [16];
  char *local_6c;
  undefined2 local_68;
  undefined1 local_64 [4];
  undefined4 local_60;
  undefined2 *local_5c;
  int *local_58;
  int *local_54;
  uint local_50;
  int local_4c;
  int local_48;
  char *local_44;
  undefined1 local_40 [4];
  char *local_3c;
  int local_38;
  undefined1 local_31;
  undefined4 *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b6d0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00508f40(local_14);
  local_8 = 0;
  *local_30 = Net::vftable;
  DAT_00917f40 = 0;
  DAT_00917f88 = 0;
  DAT_009180e0 = 0;
  DAT_00917f80 = FUN_00822e60();
  DAT_00917f9c = DAT_00917f80;
  local_30[0x10d] = 0;
  DAT_008e8d14 = DAT_008e8cf4;
  FUN_004b8f50();
  local_5c = (undefined2 *)((int)local_30 + 0x839);
  *local_5c = 0x5250;
  local_30[0x215] = (int)local_30 + 0x83b;
  local_30[0x216] = local_30[0x215] + 4;
  local_30[0x217] = local_30[0x215];
  local_30[0x218] = local_30[0x215] + 8;
  local_30[0x10c] = 300;
  FUN_00764760();
  uVar2 = FUN_00742db0();
  *(undefined2 *)(local_30 + 1) = uVar2;
  _DAT_009183f0 = 0;
  DAT_009183f8 = 0;
  local_30[0x21a] = 0;
  DAT_02a13bb4 = 1;
  DAT_00917f4c = 0;
  DAT_00917f4d = 0;
  *(undefined1 *)(local_30 + 0x219) = 0;
  local_30[0x108] = 0;
  _DAT_009180c4 = FUN_00822e60();
  DAT_009180c8 = _DAT_009180c4;
  DAT_009180dc = _DAT_009180c4;
  DAT_00917f98 = FUN_00573100();
  local_30[0x21b] = 0;
  local_30[2] = 0;
  *(undefined1 *)(local_30 + 0x107) = 0;
  local_30[0x103] = 10000;
  FUN_007d6a70("Net: Clearing user ID information (game starting)\n");
  DAT_009180d4 = 0;
  FUN_0056f7e0();
  local_30[0x10a] = 0;
  local_30[0x10b] = 0;
  DAT_008e8c00 = 0x32;
  DAT_008e8ce8 = 0x14d;
  DAT_008e8c08 = 3;
  DAT_008e8d00 = 3;
  DAT_008e8cec = FUN_00787ac0(&DAT_00883c5c,"MaxPing",700,"net.ini");
  DAT_008e8cfc = FUN_00787ac0(&DAT_00883c5c,"MaxPingsLost",0x14,"net.ini");
  _DAT_008e8cf0 = FUN_00787ac0(&DAT_00883c5c,"UpCount",10,"net.ini");
  _DAT_008e8d10 = FUN_00787ac0(&DAT_00883c5c,"DownCount",5,"net.ini");
  DAT_008e8cf4 = FUN_00787ac0(&DAT_00883c5c,"MinBandwidth",DAT_008e8cf4,"net.ini");
  DAT_008e8d08 = FUN_00787ac0(&DAT_00883c5c,"MaxBandwidth",DAT_008e8d08,"net.ini");
  DAT_008e8d0c = FUN_00787ac0(&DAT_00883c5c,"AutoKickStart",DAT_008e8d0c,"net.ini");
  DAT_008e8cf8 = FUN_00787ac0(&DAT_00883c5c,"AutoKickPing",DAT_008e8cf8,"net.ini");
  DAT_008e8bfc = FUN_00787ac0(&DAT_00883c5c,"AutoKickLoss",DAT_008e8bfc,"net.ini");
  DAT_008e8ce4 = FUN_00787ac0(&DAT_00883c5c,"AutoKickTime",DAT_008e8ce4,"net.ini");
  DAT_008e8c00 = FUN_00787ac0(&DAT_00883c5c,"LimitLowNPPI",DAT_008e8c00,"net.ini");
  DAT_008e8ce8 = FUN_00787ac0(&DAT_00883c5c,"LimitHiNPPI",DAT_008e8ce8,"net.ini");
  DAT_008e8c08 = FUN_00787ac0(&DAT_00883c5c,"DivisorMPPI2NPPI",DAT_008e8c08,"net.ini");
  DAT_008e8d00 = FUN_00787ac0(&DAT_00883c5c,"DivisorPing2NPPI",DAT_008e8d00,"net.ini");
  DAT_008e8d14 = DAT_008e8cf4;
  DAT_00917f98 = FUN_00573100();
  _DAT_009180c4 = FUN_00822e60();
  DAT_00917f79 = 1;
  local_60 = FUN_007659f0();
  FUN_00758aa0(local_30);
  FUN_0056f860();
  FUN_00624210();
  FUN_0046cc80();
  FUN_006269c0();
  FUN_00764760();
  local_4c = FUN_0056f900();
  if (local_4c != 0) {
    local_54 = (int *)FUN_00764760();
    (**(code **)(*local_54 + 0x38))(local_7c);
    FUN_0042d8c0(local_40);
    FID_conflict_begin(local_64);
    FUN_00764760();
    local_68 = FUN_00747070();
    while (cVar1 = FUN_00420f10(local_64), cVar1 != '\0') {
      local_38 = FUN_0042de50();
      local_48 = *(int *)(local_38 + 0x80);
      local_50 = (uint)*(ushort *)(local_38 + 0x28);
      if ((-1 < local_48) && (*(char *)(local_38 + 0x60) != '\0')) {
        uVar3 = FUN_0041f870();
        basic_string<>(uVar3);
        local_8._0_1_ = 1;
        FUN_00576600(local_38 + 8,local_50 & 0xffff,local_2c,local_48);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        cVar1 = FUN_0056f780(local_38 + 8);
        if (cVar1 != '\0') {
          FUN_00571b40(local_38 + 8,local_50 & 0xffff);
          local_44 = (char *)FUN_0041f870();
          local_3c = s_unnamed_008e8c80;
          local_6c = s_unnamed_008e8c80;
          do {
            cVar1 = *local_44;
            *local_3c = cVar1;
            local_44 = local_44 + 1;
            local_3c = local_3c + 1;
          } while (cVar1 != '\0');
          DAT_00917f50 = local_48;
          local_31 = 0;
        }
      }
      FUN_0042da80();
    }
  }
  local_30[2] = 2;
  local_58 = (int *)FUN_00764760();
  uVar3 = (**(code **)(*local_58 + 0x38))(local_9c);
  puVar4 = local_8c;
  FUN_00764760(puVar4,uVar3);
  FUN_0056f8b0(puVar4);
  DAT_00917f78 = FUN_0056f780(uVar3);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

