
void __thiscall FUN_004eea20(int param_1,float param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined1 local_e0 [16];
  undefined4 local_d0;
  undefined1 local_b4 [16];
  undefined4 local_a4;
  undefined1 local_88 [16];
  undefined4 local_78;
  undefined1 local_5c [4];
  undefined4 local_58;
  undefined4 local_50;
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined4 local_34;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_18;
  uint local_8;
  
  uVar5 = DAT_00917b14;
  uVar3 = DAT_008e866c;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar4 = DAT_008e8678 * DAT_008e8668;
  iVar1 = *(int *)(param_1 + 0xf8);
  *(float *)(param_1 + 700) =
       param_2 * 2.0 * (*(float *)(param_1 + 0x2b4) - *(float *)(param_1 + 700)) +
       *(float *)(param_1 + 700);
  if (*(char *)(iVar1 + 0x5a0) != '\0') {
    if (*(int *)(param_1 + 0x2c0) == 0) {
      FUN_0043a990(local_b4,uVar3,fVar4,uVar5);
      local_a4 = 0x4001;
      FUN_0043a9e0(local_24);
      local_18 = 1;
      if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
        local_20 = 0x2d;
      }
      else {
        local_20 = 0x41;
      }
      uVar2 = FUN_0043aa30(iVar1 + 0x5a0,*(undefined4 *)(param_1 + 0xf4),local_b4,local_24);
      *(undefined4 *)(param_1 + 0x2c0) = uVar2;
    }
    if (*(int *)(param_1 + 0x2c0) != 0) {
      uVar2 = FUN_008445c0();
      if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
        local_f4 = FUN_008445c0();
      }
      else {
        local_f4 = FUN_008445c0();
      }
      FUN_0043ae50(*(undefined4 *)(param_1 + 0x2c0),local_f4,0xfffffffe,uVar2);
    }
  }
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) != 0) {
    if (*(char *)(iVar1 + 0x5b0) != '\0') {
      if (*(float *)(param_1 + 700) < 1.0) {
        if (*(int *)(param_1 + 0x2c4) != 0) {
          uVar2 = FUN_0043ac70(iVar1 + 0x5b0,*(undefined4 *)(param_1 + 0xf4));
          FUN_0043aaa0(uVar2);
          *(undefined4 *)(param_1 + 0x2c4) = 0;
        }
      }
      else {
        if (*(int *)(param_1 + 0x2c4) == 0) {
          FUN_0043a990(local_88,uVar3,fVar4,uVar5);
          local_78 = 0x4001;
          FUN_0043a9e0(local_5c);
          local_50 = 1;
          if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
            local_58 = 0x2d;
          }
          else {
            local_58 = 0x41;
          }
          uVar2 = FUN_0043aa30(iVar1 + 0x5b0,*(undefined4 *)(param_1 + 0xf4),local_88,local_5c);
          *(undefined4 *)(param_1 + 0x2c4) = uVar2;
        }
        if (*(int *)(param_1 + 0x2c4) != 0) {
          uVar2 = FUN_008445c0();
          if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
            local_f8 = FUN_008445c0();
          }
          else {
            local_f8 = FUN_008445c0();
          }
          FUN_0043ae50(*(undefined4 *)(param_1 + 0x2c4),local_f8,0xfffffffe,uVar2);
        }
      }
    }
    if (*(char *)(iVar1 + 0x5c0) != '\0') {
      *(float *)(param_1 + 0x2c8) =
           param_2 * 2.0 * (*(float *)(param_1 + 0x2b8) - *(float *)(param_1 + 0x2c8)) +
           *(float *)(param_1 + 0x2c8);
      if (*(float *)(param_1 + 0x2c8) <= 0.05) {
        if (*(int *)(param_1 + 0x2cc) != 0) {
          FUN_0043aaa0(*(undefined4 *)(param_1 + 0x2cc));
          *(undefined4 *)(param_1 + 0x2cc) = 0;
        }
      }
      else {
        if (*(int *)(param_1 + 0x2cc) == 0) {
          FUN_0043a990(local_e0,uVar3,fVar4,uVar5);
          local_d0 = 0x4001;
          FUN_0043a9e0(local_40);
          local_34 = 1;
          if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
            local_3c = 0x2d;
          }
          else {
            local_3c = 0x41;
          }
          uVar3 = FUN_0043aa30(iVar1 + 0x5c0,*(undefined4 *)(param_1 + 0xf4),local_e0,local_40);
          *(undefined4 *)(param_1 + 0x2cc) = uVar3;
        }
        if (*(int *)(param_1 + 0x2cc) != 0) {
          uVar3 = FUN_008445c0();
          FUN_0043ae50(*(undefined4 *)(param_1 + 0x2cc),uVar3,0xfffffffe,0xfffffffe);
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

