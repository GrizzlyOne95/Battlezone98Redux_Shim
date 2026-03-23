
void __fastcall FUN_00598960(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_128 [4];
  undefined1 local_124 [4];
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 local_118 [4];
  float local_114;
  int local_110;
  float local_10c;
  int local_108;
  undefined4 local_104;
  int local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  int local_f4;
  int local_f0;
  int local_ec;
  undefined4 local_e8;
  int local_e4;
  int local_e0;
  undefined *local_dc;
  int local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  void *local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  undefined4 local_b0;
  int local_ac;
  int *local_a8;
  int local_a4;
  int local_a0;
  char local_99;
  int *local_98;
  char local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c06f;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_1[0x2d] = 10;
  param_1[0x2e] = *(int *)(DAT_00917580 + 4) + -0x28;
  param_1[0x2f] = param_1[0x2d] + 0xfa;
  param_1[0x30] = param_1[0x2e] + 0x14;
  local_98 = param_1;
  if (DAT_00919870 == '\0') {
    if ((((DAT_00919872 != '\0') && (param_1[0x2a] != 0)) && (-1 < param_1[0x2c])) &&
       ((param_1[0x39] != DAT_009175a0 || (param_1[0x3a] != DAT_009175a4)))) {
      param_1[0x39] = DAT_009175a0;
      param_1[0x3a] = DAT_009175a4;
      (**(code **)(*param_1 + 0x28))(DAT_009175a0,DAT_009175a4,&local_10c,&local_114,local_14);
      *(float *)(*(int *)(local_98[0x2a] + 8) + local_98[0x2c] * 8) =
           local_10c - (float)local_98[0x3b];
      *(float *)(*(int *)(local_98[0x2a] + 8) + 4 + local_98[0x2c] * 8) =
           local_114 - (float)local_98[0x3c];
    }
  }
  else {
    cVar1 = FUN_00599580();
    if (cVar1 == '\0') {
      if (local_98[0x2a] == 0) {
        local_dc = &DAT_0094de1c;
        FUN_00430590();
        puVar3 = (undefined4 *)FUN_0042d8c0(local_118);
        local_b0 = *puVar3;
        while( true ) {
          uVar4 = FID_conflict_begin(local_124);
          cVar1 = FUN_00420f10(uVar4);
          if (cVar1 == '\0') break;
          puVar3 = (undefined4 *)FUN_0042de50();
          local_a8 = (int *)*puVar3;
          if (*local_a8 != 0) {
            for (local_a4 = 0; local_a4 < local_a8[1]; local_a4 = local_a4 + 1) {
              (**(code **)(*local_98 + 0x24))
                        (*(undefined4 *)(local_a8[2] + local_a4 * 8),
                         *(undefined4 *)(local_a8[2] + 4 + local_a4 * 8),&local_ec,&local_100);
              iVar2 = FUN_00594280(local_ec - DAT_009175a0);
              if ((iVar2 < 4) && (iVar2 = FUN_00594280(local_100 - DAT_009175a4), iVar2 < 4)) {
                FUN_00599670(local_a8);
                local_98[0x2c] = local_a4;
                break;
              }
            }
            if (local_98[0x2a] != 0) break;
          }
          FUN_00438c10(local_128,0);
        }
        if (local_98[0x2a] == 0) {
          local_99 = '\x01';
          local_e0 = local_98[0x2b] + 1;
          local_98[0x2b] = local_e0;
          sprintf(local_94,"path_%d",local_e0);
          local_c4 = operator_new(0x18);
          local_8 = 0;
          if (local_c4 == (void *)0x0) {
            local_d4 = 0;
          }
          else {
            local_d4 = FUN_00460390(local_94,1);
          }
          local_e4 = local_d4;
          local_8 = 0xffffffff;
          local_cc = local_d4;
          *(undefined4 *)(local_d4 + 4) = 0;
          FUN_00599670(local_d4);
        }
        else {
          local_99 = '\0';
        }
      }
      else {
        local_99 = '\x01';
        local_b4 = local_98[0x2a];
        for (local_a0 = 0; local_a0 < *(int *)(local_b4 + 4); local_a0 = local_a0 + 1) {
          (**(code **)(*local_98 + 0x24))
                    (*(undefined4 *)(*(int *)(local_b4 + 8) + local_a0 * 8),
                     *(undefined4 *)(*(int *)(local_b4 + 8) + 4 + local_a0 * 8),&local_f4,&local_110
                    );
          iVar2 = FUN_00594280(local_f4 - DAT_009175a0);
          if ((iVar2 < 4) && (iVar2 = FUN_00594280(local_110 - DAT_009175a4), iVar2 < 4)) {
            local_99 = '\0';
            if ((DAT_00919875 == '\0') &&
               ((local_a0 == 0 && (local_98[0x2c] == *(int *)(local_b4 + 4) + -1)))) {
              local_d8 = *(int *)(local_98[0x2a] + 4);
              *(int *)(local_98[0x2a] + 4) = *(int *)(local_98[0x2a] + 4) + 1;
              *(undefined4 *)(*(int *)(local_98[0x2a] + 8) + local_d8 * 8) =
                   **(undefined4 **)(local_98[0x2a] + 8);
              *(undefined4 *)(*(int *)(local_98[0x2a] + 8) + 4 + local_d8 * 8) =
                   *(undefined4 *)(*(int *)(local_98[0x2a] + 8) + 4);
              FUN_00599670(0);
            }
            else {
              local_98[0x2c] = local_a0;
            }
            break;
          }
        }
      }
      if (local_99 == '\0') {
        if (local_98[0x2a] == 0) {
          local_98[0x3b] = 0;
          local_98[0x3c] = 0;
        }
        else {
          (**(code **)(*local_98 + 0x28))(DAT_009175a0,DAT_009175a4,local_98 + 0x3b,local_98 + 0x3c)
          ;
          local_98[0x3b] =
               (int)((float)local_98[0x3b] -
                    *(float *)(*(int *)(local_98[0x2a] + 8) + local_98[0x2c] * 8));
          local_98[0x3c] =
               (int)((float)local_98[0x3c] -
                    *(float *)(*(int *)(local_98[0x2a] + 8) + 4 + local_98[0x2c] * 8));
        }
      }
      else {
        (**(code **)(*local_98 + 0x28))(DAT_009175a0,DAT_009175a4,&local_104,&local_fc);
        if ((DAT_00919875 == '\0') || (*(int *)(local_98[0x2a] + 4) + -1 <= local_98[0x2c])) {
          local_ac = *(int *)(local_98[0x2a] + 4);
        }
        else {
          memmove((void *)(*(int *)(local_98[0x2a] + 8) + 0x10 + local_98[0x2c] * 8),
                  (void *)(*(int *)(local_98[0x2a] + 8) + 8 + local_98[0x2c] * 8),
                  (*(int *)(local_98[0x2a] + 4) - local_98[0x2c]) * 8);
          local_ac = local_98[0x2c] + 1;
        }
        *(int *)(local_98[0x2a] + 4) = *(int *)(local_98[0x2a] + 4) + 1;
        *(undefined4 *)(*(int *)(local_98[0x2a] + 8) + local_ac * 8) = local_104;
        *(undefined4 *)(*(int *)(local_98[0x2a] + 8) + 4 + local_ac * 8) = local_fc;
        local_98[0x2c] = local_ac;
        local_98[0x3b] = 0;
        local_98[0x3c] = 0;
      }
      local_98[0x39] = DAT_009175a0;
      local_98[0x3a] = DAT_009175a4;
    }
  }
  if (DAT_00919871 != '\0') {
    FUN_00599670(0);
  }
  if ((DAT_00919874 != '\0') && (local_98[0x2a] != 0)) {
    if (*(int *)(local_98[0x2a] + 4) == 1) {
      local_c8 = local_98[0x2a];
      FUN_00599670(0);
      local_bc = FUN_0046f0f0(local_c8);
      if (local_bc != 0) {
        local_108 = local_bc;
        local_c0 = local_bc;
        if (local_bc == 0) {
          local_e8 = 0;
        }
        else {
          local_e8 = FUN_0046f0c0(1);
        }
      }
      local_f0 = local_c8;
      local_d0 = local_c8;
      if (local_c8 == 0) {
        local_f8 = 0;
      }
      else {
        local_f8 = FUN_00460640(1);
      }
    }
    else {
      local_b8 = *(int *)(local_98[0x2a] + 4) + -1;
      *(int *)(local_98[0x2a] + 4) = local_b8;
      if (local_98[0x2c] < local_b8) {
        memmove((void *)(*(int *)(local_98[0x2a] + 8) + local_98[0x2c] * 8),
                (void *)(*(int *)(local_98[0x2a] + 8) + 8 + local_98[0x2c] * 8),
                (*(int *)(local_98[0x2a] + 4) - local_98[0x2c]) * 8);
      }
      if (local_98[0x2c] == *(int *)(local_98[0x2a] + 4)) {
        local_98[0x2c] = local_98[0x2c] + -1;
      }
    }
  }
  FUN_00596190(0);
  if (local_98[0x2a] != 0) {
    FUN_00595e80(local_98[0x2a],local_98[0x2c],DAT_0091757c);
    FUN_0068afb0(DAT_00917580,local_98[0x2d],local_98[0x2e],local_98[0x2f],local_98[0x30],
                 DAT_00917570,0);
    FUN_004c0100(DAT_00917580,local_98[0x2d] + 2,local_98[0x2e] + 1,local_120,local_11c,
                 *(undefined4 *)local_98[0x2a],DAT_00917550,DAT_0091755c,0xffffffff,0,0,0);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

