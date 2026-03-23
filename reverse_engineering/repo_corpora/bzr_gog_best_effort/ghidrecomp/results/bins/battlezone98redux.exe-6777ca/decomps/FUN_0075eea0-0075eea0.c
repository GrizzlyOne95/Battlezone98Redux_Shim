
void FUN_0075eea0(undefined4 param_1,char param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  undefined1 auStack_1e8 [160];
  undefined1 local_148 [8];
  int local_140;
  int local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined1 local_120 [4];
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined1 *local_10c;
  undefined1 local_108 [8];
  int *local_100;
  undefined1 local_fc [56];
  undefined1 local_c4 [28];
  undefined1 local_a8 [28];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cd56;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  FUN_0042d8c0(local_108);
  FID_conflict_begin(local_120);
  do {
    cVar2 = FUN_00420f10(local_120);
    if (cVar2 == '\0') {
LAB_0075f34b:
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    puVar4 = (undefined4 *)FUN_0042de50(uVar3);
    local_100 = (int *)*puVar4;
    cVar2 = FUN_0056f780(param_1);
    if (cVar2 != '\0') {
      if (param_2 != '\0') {
        if (0 < DAT_008eda28) {
          local_134 = FUN_0073a9f0(local_44);
          local_8 = 0;
          local_128 = local_134;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Fully Resetting Connection Status For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        *local_100 = 0;
        *(undefined1 *)(local_100 + 6) = 0;
        *(undefined2 *)(local_100 + 7) = 0;
        FUN_006b29f0(2);
        local_100[8] = local_140;
        local_100[9] = local_13c;
        uVar5 = FUN_006cb470();
        FUN_006cb4c0(uVar5);
        FUN_006cb4c0(local_100 + 10);
        FUN_00429ce0();
        local_100[0x21] = 0;
        local_100[0x22] = 0;
        FUN_0041ff50();
        FUN_0075fa10();
        *(undefined1 *)((int)local_100 + 0x19) = 0;
        *(undefined1 *)((int)local_100 + 0x1a) = 0;
      }
      if (*local_100 != 0) goto LAB_0075f34b;
      if (DAT_00946708 != 0) {
        local_12c = FUN_0073a9f0(local_2c);
        local_8 = 1;
        local_114 = local_12c;
        uVar5 = FUN_0041f870();
        FUN_007d6a70("BZRNet P2P Starting RELAY Connect For Client %s - HandleP2PConnect\n",uVar5);
        local_8 = 0xffffffff;
        ~basic_string<>();
        FUN_0075aa90(local_100);
        goto LAB_0075f34b;
      }
      uVar5 = 0;
      get(param_1,0);
      FUN_006c59c0(param_1,uVar5);
      piVar6 = (int *)FUN_006c9bd0(local_148);
      iVar1 = piVar6[1];
      local_100[8] = *piVar6;
      local_100[9] = iVar1;
      puVar8 = local_c4;
      get(puVar8);
      uVar5 = FUN_006cac80(puVar8);
      uVar7 = FUN_006cac80(local_fc);
      cVar2 = FUN_006b3430(uVar7,uVar5);
      if (cVar2 == '\0') {
        FUN_006cac80(local_a8);
        cVar2 = FUN_0075a050();
        if (cVar2 == '\0') {
          FUN_00574400(3,1);
          local_8 = 3;
          if (&stack0x00000000 == (undefined1 *)0x1f8) {
            local_10c = (undefined1 *)0x0;
          }
          else {
            local_10c = auStack_1e8;
          }
          FUN_006da360(local_10c,local_100 + 0x11);
          local_138 = GetPolicy(local_74);
          local_8._0_1_ = 4;
          local_110 = local_138;
          local_124 = FUN_0073a9f0(local_8c);
          local_8._0_1_ = 5;
          local_118 = local_124;
          uVar5 = FUN_0041f870();
          uVar5 = FUN_0041f870(uVar5);
          FUN_007d6a70("BZRNet P2P Starting WAN Connect For Client %s (IP %s) - HandleP2PConnect\n",
                       uVar5);
          local_8._0_1_ = 4;
          ~basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,3);
          ~basic_string<>();
          *(undefined2 *)(local_100 + 7) = 0x1e;
          *local_100 = 3;
          local_8 = 0xffffffff;
          FUN_00417f10();
          goto LAB_0075f34b;
        }
      }
      local_130 = FUN_0073a9f0(local_5c);
      local_8 = 2;
      local_11c = local_130;
      uVar5 = FUN_0041f870();
      FUN_007d6a70("BZRNet P2P Starting LAN Connect For Client %s - HandleP2PConnect\n",uVar5);
      local_8 = 0xffffffff;
      ~basic_string<>();
      *(undefined2 *)(local_100 + 7) = 0xf;
      *local_100 = 1;
      goto LAB_0075f34b;
    }
    FUN_0042da80();
  } while( true );
}

