
void __fastcall FUN_005983a0(int *param_1)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_d8 [4];
  undefined1 local_d4 [4];
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  int local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  int local_a4;
  undefined4 *local_a0;
  int local_9c;
  undefined4 local_98;
  float local_94;
  int local_90;
  int *local_8c;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_8c = param_1;
  if (DAT_00919870 != '\0') {
    (**(code **)(*param_1 + 0x28))(DAT_009175a0,DAT_009175a4,&local_9c,&local_a8);
    if ((float)local_8c[0x22] == 1e+30) {
      local_8c[0x22] = local_9c;
      local_8c[0x23] = local_a8;
    }
    else if ((float)local_8c[0x24] == 1e+30) {
      local_8c[0x24] = local_9c;
      local_8c[0x25] = local_a8;
      if (local_8c[0x29] != 0) {
        local_b4 = local_8c[0x29];
        local_a4 = local_b4;
        if (local_b4 == 0) {
          local_cc = 0;
        }
        else {
          local_cc = FUN_00460640();
        }
      }
      iVar1 = FUN_00822e60();
      local_8c[0x26] = iVar1;
      if (local_8c[0x21] < 0) {
        local_90 = 1;
      }
      else {
        local_90 = local_8c[0x21];
      }
      iVar1 = FUN_00466450(local_8c[0x22],local_8c[0x23],local_8c[0x24],local_8c[0x25],0,local_90);
      local_8c[0x29] = iVar1;
      iVar1 = FUN_00822e60();
      local_8c[0x26] = iVar1 - local_8c[0x26];
      fVar2 = (float10)FUN_00417910();
      local_8c[0x27] = (int)(float)fVar2;
      if (local_8c[0x29] == 0) {
        local_94 = 0.0;
      }
      else {
        fVar2 = (float10)FUN_00461110();
        local_94 = (float)fVar2;
      }
      local_8c[0x28] = (int)local_94;
      local_8c[0x22] = 0x7149f2ca;
      local_8c[0x24] = 0x7149f2ca;
    }
  }
  if ((float)local_8c[0x22] != 1e+30) {
    (**(code **)(*local_8c + 0x24))(local_8c[0x22],local_8c[0x23],&local_c8,&local_ac);
    FUN_005953c0(local_c8,local_ac,3,&local_b0,&local_c4,&local_d0,&local_bc);
    FUN_0068b020(DAT_00917580,local_b0,local_c4,local_d0,local_bc,DAT_009175b0,0);
  }
  if (local_8c[0x29] != 0) {
    if (*(int *)(local_8c[0x29] + 0x10) == 3) {
      local_98 = DAT_0091757c;
    }
    else {
      local_98 = DAT_009175b0;
    }
    FUN_00595e80();
    sprintf(local_88,"Time: %ld ms\nDist: %.1f m\nLen: %.1f m",local_8c[0x26],
            (double)(float)local_8c[0x27],(double)(float)local_8c[0x28]);
    local_a0 = (undefined4 *)(*(int *)(local_8c[0x29] + 8) + -8 + *(int *)(local_8c[0x29] + 4) * 8);
    (**(code **)(*local_8c + 0x24))(*local_a0,local_a0[1],&local_c0,&local_b8);
    FUN_004c0100(DAT_00917580,local_c0,local_b8,local_d8,local_d4,local_88,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,2,0,0);
  }
  FUN_0083e885();
  return;
}

