
void __fastcall FUN_004b8000(int *param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 auStack_10c [12];
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined2 *puStack_d4;
  int *piStack_d0;
  undefined1 local_c0 [16];
  undefined1 local_b0 [16];
  undefined1 local_a0 [16];
  undefined1 local_90 [16];
  undefined2 *local_80;
  undefined4 local_7c;
  undefined2 *local_78;
  int local_74;
  undefined4 local_70;
  int local_6c;
  int *local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int *local_54;
  int *local_50;
  int *local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  undefined4 *local_3c;
  int local_38;
  undefined4 *local_34;
  char local_2d;
  int *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined2 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_009175b8 = (int *)0x0;
  piStack_d0 = (int *)0x4b8030;
  local_2c = param_1;
  local_38 = (**(code **)(*param_1 + 0x30))();
  if (local_38 != 0) {
    piStack_d0 = *(int **)(local_38 + 0xc);
    puStack_d4 = *(undefined2 **)(local_38 + 8);
    uStack_d8 = 0x4b804e;
    local_2d = FUN_004b7650();
    if (local_2d == '\0') {
      local_34 = (undefined4 *)&DAT_009175c0;
      local_80 = (undefined2 *)&DAT_009175dc;
      piStack_d0 = (int *)0x4b824b;
      local_64 = FUN_00417c70();
      if (local_64 == 0) {
        local_4c = (int *)0x0;
      }
      else {
        local_4c = (int *)(local_64 + 0x18);
      }
      local_44 = (uint)(local_2c == local_4c);
      piStack_d0 = (int *)0x4b828a;
      local_6c = (**(code **)*local_2c)();
      if (local_6c == 0) {
        *local_34 = 0;
        local_34[1] = 0;
        local_34[2] = 0;
        local_34[3] = 0;
        local_34[4] = 0;
        local_34[5] = 0;
        local_34[6] = 0;
        uVar4 = local_44 & 1;
        piStack_d0 = (int *)0x4b8366;
        bVar1 = (**(code **)(*local_2c + 4))();
        *(byte *)((int)local_34 + 1) = (byte)(uVar4 << 7) | 0x40 | (bVar1 & 0xf) << 2;
      }
      else {
        uVar4 = local_44 & 1;
        piStack_d0 = (int *)0x4b82ad;
        bVar1 = (**(code **)(*local_2c + 4))();
        *(byte *)((int)local_34 + 1) = (byte)(uVar4 << 7) | (bVar1 & 0xf) << 2;
        puVar2 = (undefined4 *)(local_38 + 0x20);
        puVar5 = auStack_10c;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = (undefined4 *)FUN_006255b0(local_a0);
        local_18 = *puVar2;
        local_14 = puVar2[1];
        local_10 = puVar2[2];
        local_c = *(undefined2 *)(puVar2 + 3);
        *(undefined4 *)((int)local_34 + 6) = local_18;
        *(undefined4 *)((int)local_34 + 10) = local_14;
        *(undefined4 *)((int)local_34 + 0xe) = local_10;
        *(undefined2 *)((int)local_34 + 0x12) = local_c;
        *(int *)((int)local_34 + 2) = local_2c[0x19];
        local_34[5] = *(undefined4 *)(local_38 + 8);
        local_34[6] = *(undefined4 *)(local_38 + 0xc);
      }
      for (local_40 = 0; local_40 < 8; local_40 = local_40 + 1) {
        *(byte *)((int)local_34 + local_40 + 0x14) =
             *(byte *)((int)local_34 + local_40 + 0x14) & 0x7f;
      }
      DAT_009175b8 = (int *)0x1c;
      piStack_d0 = (int *)&DAT_009175b8;
      puStack_d4 = local_80;
      uStack_d8 = 0x4b83c4;
      (**(code **)(*local_2c + 0x44))();
      *(undefined1 *)local_34 = DAT_009175b8._0_1_;
      if (((int *)0x1c < DAT_009175b8) &&
         ((local_38 == 0 || ((*(uint *)(local_38 + 0x14) & 0x80) == 0)))) {
        piStack_d0 = (int *)0x4b83f3;
        local_50 = (int *)FUN_00764760();
        piStack_d0 = (int *)local_c0;
        puStack_d4 = (undefined2 *)0x4b840a;
        piStack_d0 = (int *)(**(code **)(*local_50 + 0x38))();
        puStack_d4 = (undefined2 *)0x4b8410;
        local_58 = FUN_00577200();
        piStack_d0 = local_2c;
        puStack_d4 = (undefined2 *)0x4b841f;
        local_7c = FUN_004b75f0();
        if (local_58 != 0) {
          piStack_d0 = DAT_009175b8;
          puStack_d4 = &DAT_009175c0;
          uStack_dc = 0x4b8443;
          uStack_d8 = local_7c;
          FUN_00575570();
        }
      }
    }
    else {
      local_3c = (undefined4 *)&DAT_009175c0;
      local_78 = (undefined2 *)0x9175d5;
      piStack_d0 = (int *)0x4b8075;
      local_5c = FUN_00417c70();
      if (local_5c == 0) {
        local_68 = (int *)0x0;
      }
      else {
        local_68 = (int *)(local_5c + 0x18);
      }
      local_48 = (uint)(local_2c == local_68);
      piStack_d0 = (int *)0x4b80b4;
      local_74 = (**(code **)*local_2c)();
      if (local_74 == 0) {
        *local_3c = 0;
        local_3c[1] = 0;
        local_3c[2] = 0;
        local_3c[3] = 0;
        local_3c[4] = 0;
        *(undefined1 *)(local_3c + 5) = 0;
        uVar4 = local_48 & 1;
        piStack_d0 = (int *)0x4b8184;
        bVar1 = (**(code **)(*local_2c + 4))();
        *(byte *)((int)local_3c + 1) = (byte)(uVar4 << 7) | 0x40 | (bVar1 & 0xf) << 2;
      }
      else {
        uVar4 = local_48 & 1;
        piStack_d0 = (int *)0x4b80d7;
        bVar1 = (**(code **)(*local_2c + 4))();
        *(byte *)((int)local_3c + 1) = (byte)(uVar4 << 7) | (bVar1 & 0xf) << 2;
        puVar2 = (undefined4 *)(local_38 + 0x20);
        puVar5 = auStack_10c;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = (undefined4 *)FUN_006255b0(local_90);
        local_28 = *puVar2;
        local_24 = puVar2[1];
        local_20 = puVar2[2];
        local_1c = *(undefined2 *)(puVar2 + 3);
        *(undefined4 *)((int)local_3c + 6) = local_28;
        *(undefined4 *)((int)local_3c + 10) = local_24;
        *(undefined4 *)((int)local_3c + 0xe) = local_20;
        *(undefined2 *)((int)local_3c + 0x12) = local_1c;
        *(int *)((int)local_3c + 2) = local_2c[0x19];
        *(char *)(local_3c + 5) = local_2d;
      }
      DAT_009175b8 = (int *)0x15;
      piStack_d0 = (int *)&DAT_009175b8;
      puStack_d4 = local_78;
      uStack_d8 = 0x4b81b2;
      (**(code **)(*local_2c + 0x44))();
      *(undefined1 *)local_3c = DAT_009175b8._0_1_;
      if (((int *)0x15 < DAT_009175b8) &&
         ((local_38 == 0 || ((*(uint *)(local_38 + 0x14) & 0x80) == 0)))) {
        piStack_d0 = (int *)0x4b81e1;
        local_54 = (int *)FUN_00764760();
        piStack_d0 = (int *)local_b0;
        puStack_d4 = (undefined2 *)0x4b81f8;
        piStack_d0 = (int *)(**(code **)(*local_54 + 0x38))();
        puStack_d4 = (undefined2 *)0x4b81fe;
        local_60 = FUN_00577200();
        if (local_60 != 0) {
          piStack_d0 = local_2c;
          puStack_d4 = (undefined2 *)0x4b8213;
          uStack_d8 = FUN_004b75f0();
          piStack_d0 = DAT_009175b8;
          puStack_d4 = &DAT_009175c0;
          uStack_dc = 0x4b8231;
          local_70 = uStack_d8;
          FUN_00575570();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

