
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00616500(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float fVar5;
  double dVar6;
  undefined4 local_140;
  int local_138;
  float local_128 [6];
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  float fStack_f8;
  float fStack_f4;
  float fStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00945498 == 0) {
    FUN_00776690();
  }
  FUN_0067ca70((float)DAT_02cd9120 / 255.0,(float)DAT_02cd9121 / 255.0,(float)DAT_02cd9122 / 255.0);
  uVar1 = FUN_00685560();
  FUN_00685580(0);
  if (DAT_02a13d94 == '\0') {
    if (((DAT_02cd5108 != DAT_02cd9120) || (DAT_02cd5109 != DAT_02cd9121)) ||
       (DAT_02cd510a != DAT_02cd9122)) {
      FUN_006856f0(0);
      fVar5 = (float)*(double *)(param_1 + 0x168) + 100.0 + (float)_DAT_02a13da4;
      iVar2 = FUN_00615c30(local_128,param_1,fVar5,fVar5 + 400.0);
      if (iVar2 != 0) {
        FUN_00685740(param_1,local_128,iVar2,
                     (uint)DAT_02cd5108 << 0x10 | 0xff000000 | (uint)DAT_02cd5109 << 8 |
                     (uint)DAT_02cd510a);
      }
      iVar2 = FUN_00615830(local_128,param_1,fVar5 + 400.0);
      if (iVar2 != 0) {
        FUN_00685740(param_1,local_128,iVar2,
                     (uint)DAT_02cd5108 << 0x10 | 0xff000000 | (uint)DAT_02cd5109 << 8 |
                     (uint)DAT_02cd510a);
      }
      FUN_006856e0();
    }
  }
  else if (DAT_02a13d90 == 0) {
    fVar3 = (float10)FUN_00822d60();
    iVar2 = FUN_006162d0(local_128,param_1,
                         (float)*(double *)(param_1 + 0x168) + (float)_DAT_02a13da4);
    if (iVar2 != 0) {
      FUN_006855a0(&DAT_02a13d94,0);
      FUN_00685a40(param_1,local_128,iVar2);
      FUN_006856e0();
    }
    dVar6 = (double)((float)fVar3 * 0.03) + _DAT_02a13dd0;
    fVar4 = (float10)_CIfmod();
    _DAT_02a13dd0 = (double)fVar4;
    fVar3 = (float10)_CIfmod((double)((float)fVar3 * 0.03) + _DAT_02a13de8,dVar6);
    _DAT_02a13de8 = (double)fVar3;
  }
  else {
    local_140 = CONCAT22(local_140._2_2_,0xff00);
    local_140 = CONCAT31(local_140._1_3_,0xff);
    fStack_e0 = (float)*(double *)(param_1 + 0x160);
    local_128[1] = (float)*(double *)(param_1 + 0x168) + (float)_DAT_02a13da4;
    fStack_d8 = (float)*(double *)(param_1 + 0x170);
    local_128[0] = fStack_e0 - _DAT_008eaaa0;
    local_128[2] = fStack_d8 - _DAT_008eaaa0;
    local_128[3] = 0.0;
    local_128[4] = 0.0;
    local_128[5] = (float)local_140;
    fStack_110 = fStack_e0 + _DAT_008eaaa0;
    fStack_108 = fStack_d8 - _DAT_008eaaa0;
    uStack_104 = 0x3f800000;
    uStack_100 = 0;
    uStack_fc = local_140;
    fStack_f8 = fStack_e0 + _DAT_008eaaa0;
    fStack_f0 = fStack_d8 + _DAT_008eaaa0;
    uStack_ec = 0x3f800000;
    uStack_e8 = 0x3f800000;
    uStack_e4 = local_140;
    fStack_e0 = fStack_e0 - _DAT_008eaaa0;
    fStack_d8 = fStack_d8 + _DAT_008eaaa0;
    uStack_d4 = 0;
    uStack_d0 = 0x3f800000;
    uStack_cc = local_140;
    fStack_10c = local_128[1];
    fStack_f4 = local_128[1];
    fStack_dc = local_128[1];
    for (local_138 = 0; local_138 < 4; local_138 = local_138 + 1) {
      FUN_00820180(local_128 + local_138 * 6,local_128 + local_138 * 6,1,param_1 + 0x40);
    }
    FUN_006855a0(&DAT_02a13d94,0);
    FUN_00685a40(param_1,local_128,4);
    FUN_006856e0();
  }
  FUN_00685580(5);
  FUN_00615300(param_1);
  if (2 < param_2) {
    FUN_00775c40(param_1);
    FUN_00777600(param_1);
    FUN_00776440(param_1);
  }
  FUN_00685580(uVar1);
  FUN_0083e885();
  return;
}

