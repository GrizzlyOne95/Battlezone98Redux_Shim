
void FUN_00657420(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  bool bVar6;
  float10 fVar7;
  char *pcVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined1 local_f8 [4];
  double local_f4;
  double local_ec;
  undefined1 local_e4 [4];
  float local_e0;
  char *local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float local_b0;
  float local_ac;
  undefined4 local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  int local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  undefined4 local_70;
  float local_6c;
  float local_68;
  float local_64;
  char *local_60;
  undefined4 local_5c;
  char *local_58;
  undefined1 local_54 [4];
  int local_50;
  int local_4c;
  uint local_48;
  char *local_44;
  int local_40;
  int local_3c;
  char *local_38 [4];
  char *local_28;
  char *local_24;
  char *local_20;
  char *local_1c;
  char *local_18;
  char *local_14 [3];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = 0;
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_3c + 0x8c) = uVar2;
  if (*(char *)(local_3c + 0x54) == '\0') {
    FUN_005cb2d0("chmisn06.aip",2);
    FUN_005cacb0(1,10);
    FUN_005cadd0(2,0);
    FUN_005cadd0(1,0x32);
    *(undefined1 *)(local_3c + 0x54) = 1;
    fVar7 = (float10)FUN_004b1670();
    local_c4 = (float)fVar7;
    *(float *)(local_3c + 100) = local_c4 + 2.0;
    fVar7 = (float10)FUN_004b1670();
    local_d0 = (float)fVar7;
    *(float *)(local_3c + 0x68) = local_d0 + 60.0;
    fVar7 = (float10)FUN_004b1670();
    local_d8 = (float)fVar7;
    *(float *)(local_3c + 0x78) = local_d8 + 600.0;
    fVar7 = (float10)FUN_004b1670();
    local_e0 = (float)fVar7;
    *(float *)(local_3c + 0x80) = local_e0 + 1200.0;
  }
  fVar7 = (float10)FUN_004b1670();
  local_cc = (float)fVar7;
  if (*(float *)(local_3c + 0x80) <= local_cc && local_cc != *(float *)(local_3c + 0x80)) {
    *(undefined4 *)(local_3c + 0x80) = 0x497423fe;
    FUN_005cada0(2,0x32);
  }
  fVar7 = (float10)FUN_004b1670();
  local_68 = (float)fVar7;
  if (*(float *)(local_3c + 100) <= local_68 && local_68 != *(float *)(local_3c + 100)) {
    *(undefined4 *)(local_3c + 100) = 0x497423fe;
    uVar2 = FUN_00437d30("ch06001.wav");
    *(undefined4 *)(local_3c + 0x114) = uVar2;
    FUN_004f6aa0();
    FUN_004f6ab0("ch06001.otf",DAT_0091755c,0x41000000,0);
  }
  if ((*(int *)(local_3c + 0x114) != 0) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_3c + 0x114)), cVar1 != '\0')) {
    *(undefined4 *)(local_3c + 0x114) = 0;
  }
  fVar7 = (float10)FUN_004b1670();
  local_b0 = (float)fVar7;
  if (*(float *)(local_3c + 0x68) <= local_b0 && local_b0 != *(float *)(local_3c + 0x68)) {
    *(undefined4 *)(local_3c + 0x68) = 0x497423fe;
    uVar2 = FUN_00437d30("ch06002.wav");
    *(undefined4 *)(local_3c + 0x118) = uVar2;
  }
  if ((*(int *)(local_3c + 0x118) != 0) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_3c + 0x118)), cVar1 != '\0')) {
    *(undefined4 *)(local_3c + 0x118) = 0;
    local_70 = FUN_005c8250(&DAT_00878c18,1,"nav_1",0,0);
    FUN_005cd7f0(local_70,"CCA Base");
    fVar7 = (float10)FUN_004b1670();
    local_c0 = (float)fVar7;
    *(float *)(local_3c + 0x6c) = local_c0 + 15.0;
  }
  fVar7 = (float10)FUN_004b1670();
  local_78 = (float)fVar7;
  if (*(float *)(local_3c + 0x6c) <= local_78 && local_78 != *(float *)(local_3c + 0x6c)) {
    *(undefined4 *)(local_3c + 0x6c) = 0x497423fe;
    uVar2 = FUN_00437d30("ch06003.wav");
    *(undefined4 *)(local_3c + 0x11c) = uVar2;
  }
  if ((*(int *)(local_3c + 0x11c) != 0) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_3c + 0x11c)), cVar1 != '\0')) {
    *(undefined4 *)(local_3c + 0x11c) = 0;
    fVar7 = (float10)FUN_004b1670();
    local_c8 = (float)fVar7;
    *(float *)(local_3c + 0x70) = local_c8 + 1.0;
  }
  fVar7 = (float10)FUN_004b1670();
  local_80 = (float)fVar7;
  if (*(float *)(local_3c + 0x70) <= local_80 && local_80 != *(float *)(local_3c + 0x70)) {
    *(undefined4 *)(local_3c + 0x70) = 0x497423fe;
    uVar2 = FUN_00437d30("ch06004.wav");
    *(undefined4 *)(local_3c + 0x120) = uVar2;
  }
  if ((*(int *)(local_3c + 0x120) != 0) &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(local_3c + 0x120)), cVar1 != '\0')) {
    *(undefined4 *)(local_3c + 0x120) = 0;
    fVar7 = (float10)FUN_004b1670();
    local_bc = (float)fVar7;
    *(float *)(local_3c + 0x74) = local_bc + 180.0;
  }
  fVar7 = (float10)FUN_004b1670();
  local_88 = (float)fVar7;
  if (*(float *)(local_3c + 0x74) <= local_88 && local_88 != *(float *)(local_3c + 0x74)) {
    *(undefined4 *)(local_3c + 0x74) = 0x497423fe;
    local_38[0] = "ran_1";
    local_38[1] = "ran_2";
    local_38[2] = "ran_3";
    local_20 = "ran_1_path";
    local_1c = "ran_2_path";
    local_18 = "ran_3_path";
    local_50 = rand();
    local_50 = local_50 % 3;
    local_44 = local_38[local_50];
    local_dc = local_38[local_50 + 6];
    *(int *)(local_3c + 0x110) = local_50;
    uVar2 = FUN_005c8250("cvfigh",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xa4) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xa8) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xac) = uVar2;
    uVar2 = FUN_005c8250("cvfigh",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xb0) = uVar2;
    uVar2 = FUN_005c8250("cvtnk",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xb4) = uVar2;
    uVar2 = FUN_005c8250("cvtnk",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xb8) = uVar2;
    uVar2 = FUN_005c8250("cvtnk",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xbc) = uVar2;
    uVar2 = FUN_005c8250("cvtnk",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xc0) = uVar2;
    uVar2 = FUN_005c8250("cvhraz",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xc4) = uVar2;
    uVar2 = FUN_005c8250("cvhraz",1,local_44,0,0);
    *(undefined4 *)(local_3c + 200) = uVar2;
    uVar2 = FUN_005c8250("cvhraz",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xcc) = uVar2;
    uVar2 = FUN_005c8250("cvhraz",1,local_44,0,0);
    *(undefined4 *)(local_3c + 0xd0) = uVar2;
    for (local_40 = 0; local_40 < 0xc; local_40 = local_40 + 1) {
      FUN_005c88b0(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4),2);
      FUN_005cb960(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4),local_dc,1);
      local_90 = FUN_00462630(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4));
      uVar2 = FUN_004ff060("sspilo");
      *(undefined4 *)(local_90 + 0xec) = uVar2;
    }
    *(undefined1 *)(local_3c + 0x5c) = 1;
  }
  if ((*(char *)(local_3c + 0x5c) != '\0') && (*(char *)(local_3c + 0x5d) == '\0')) {
    local_38[3] = "ran_1_trigger";
    local_28 = "ran_2_trigger";
    local_24 = "ran_3_trigger";
    local_60 = local_38[*(int *)(local_3c + 0x110) + 3];
    for (local_40 = 0; local_40 < 0xc; local_40 = local_40 + 1) {
      fVar7 = (float10)FUN_005cced0(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4));
      local_ec = (double)fVar7;
      if (local_ec < 0.7) {
        *(undefined1 *)(local_3c + 0x5d) = 1;
        break;
      }
      cVar1 = FUN_005c84d0(local_3c + 0xa4 + local_40 * 4);
      if (cVar1 != '\0') {
        fVar7 = (float10)FUN_005c9800(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4),local_60,0);
        local_98 = (float)fVar7;
        if (local_98 < 75.0) {
          *(undefined1 *)(local_3c + 0x5d) = 1;
          break;
        }
      }
    }
    if (*(char *)(local_3c + 0x5d) != '\0') {
      for (local_40 = 0; local_40 < 0xc; local_40 = local_40 + 1) {
        FUN_005c8840(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4),2);
        FUN_005c88b0(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4),2);
        uVar2 = FUN_006572b0(0);
        FUN_005cb820(*(undefined4 *)(local_3c + 0xa4 + local_40 * 4),uVar2);
      }
      FUN_00437d30("ch06005.wav");
      fVar7 = (float10)FUN_004b1670();
      local_d4 = (float)fVar7;
      *(float *)(local_3c + 0x84) = local_d4 + 120.0;
    }
  }
  fVar7 = (float10)FUN_004b1670();
  local_a0 = (float)fVar7;
  if (*(float *)(local_3c + 0x84) <= local_a0 && local_a0 != *(float *)(local_3c + 0x84)) {
    *(undefined4 *)(local_3c + 0x84) = 0x497423fe;
    local_14[0] = (char *)0x0;
    local_14[1] = (char *)0x0;
    local_14[2] = (char *)0x0;
    bVar6 = *(int *)(local_3c + 0x110) != 0;
    if (bVar6) {
      local_14[0] = "ran_1";
    }
    local_48 = (uint)bVar6;
    if (*(int *)(local_3c + 0x110) != 1) {
      local_38[local_48 + 9] = "ran_2";
      local_48 = local_48 + 1;
    }
    if (*(int *)(local_3c + 0x110) != 2) {
      local_38[local_48 + 9] = "ran_3";
      local_48 = local_48 + 1;
    }
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    local_58 = local_38[uVar3 + 9];
    for (local_40 = 0; local_40 < 4; local_40 = local_40 + 1) {
      local_b4 = FUN_005c8250("svfigh",2,local_58,0,0);
      uVar2 = FUN_006572b0(0);
      FUN_005cb820(local_b4,uVar2);
    }
    for (local_40 = 0; local_40 < 4; local_40 = local_40 + 1) {
      local_a8 = FUN_005c8250("svtank",2,local_58,0,0);
      uVar2 = FUN_006572b0(0);
      FUN_005cb820(local_a8,uVar2);
    }
  }
  if ((*(char *)(local_3c + 0x5c) != '\0') && (*(char *)(local_3c + 0x5e) == '\0')) {
    *(undefined1 *)(local_3c + 0x5e) = 1;
    for (local_40 = 0; local_40 < 0xc; local_40 = local_40 + 1) {
      cVar1 = FUN_005c84d0(local_3c + 0xa4 + local_40 * 4);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_3c + 0x5e) = 0;
      }
    }
    if (*(char *)(local_3c + 0x5e) != '\0') {
      FUN_00437d30("ch06006.wav");
    }
  }
  if (((*(char *)(local_3c + 0x5e) != '\0') && (*(char *)(local_3c + 0x60) == '\0')) &&
     (*(char *)(local_3c + 0x61) == '\0')) {
    *(undefined1 *)(local_3c + 0x60) = 1;
    local_5c = DAT_00917a74;
    FID_conflict_begin(local_54);
    while( true ) {
      uVar2 = FID_conflict_end(local_f8);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_4c = *piVar4;
      iVar5 = (**(code **)(*(int *)(local_4c + 0x18) + 4))();
      if (iVar5 == 2) {
        local_b8 = FUN_00477590(local_4c);
        cVar1 = FUN_005c84d0(&local_b8);
        if (cVar1 != '\0') {
          *(undefined1 *)(local_3c + 0x60) = 0;
        }
      }
      FUN_0046b260(local_e4,0);
    }
    if (*(char *)(local_3c + 0x60) != '\0') {
      fVar7 = (float10)FUN_004b1670("ch06win.des");
      local_64 = (float)fVar7;
      FUN_0045c110(local_64 + 1.0);
    }
  }
  fVar7 = (float10)FUN_005cced0(*(undefined4 *)(local_3c + 0x90));
  local_f4 = (double)fVar7;
  if (((local_f4 <= 0.0) &&
      (fVar7 = (float10)FUN_005cced0(*(undefined4 *)(local_3c + 0x94)), (double)fVar7 <= 0.0)) &&
     ((*(char *)(local_3c + 0x61) == '\0' && (*(char *)(local_3c + 0x60) == '\0')))) {
    *(undefined1 *)(local_3c + 0x61) = 1;
    fVar7 = (float10)FUN_004b1670("ch06lsea.des");
    FUN_0045c0f0((float)fVar7);
  }
  fVar7 = (float10)FUN_004b1670();
  local_6c = (float)fVar7;
  if (*(float *)(local_3c + 0x78) <= local_6c && local_6c != *(float *)(local_3c + 0x78)) {
    fVar7 = (float10)FUN_005c9800(*(undefined4 *)(local_3c + 0x90),"activate_1",0);
    local_74 = (float)fVar7;
    if (500.0 <= local_74) {
      fVar7 = (float10)FUN_005c9800(*(undefined4 *)(local_3c + 0x90),"activate_2",0);
      local_7c = (float)fVar7;
      if (500.0 <= local_7c) {
        fVar7 = (float10)FUN_005c9800(*(undefined4 *)(local_3c + 0x94),"activate_1",0);
        local_84 = (float)fVar7;
        if (500.0 <= local_84) {
          fVar7 = (float10)FUN_005c9800(*(undefined4 *)(local_3c + 0x94),"activate_2",0);
          local_8c = (float)fVar7;
          if (500.0 <= local_8c) {
            fVar7 = (float10)FUN_004b1670();
            local_94 = (float)fVar7;
            *(float *)(local_3c + 0x78) = local_94 + 60.0;
            goto LAB_006580fe;
          }
        }
      }
    }
    fVar7 = (float10)FUN_004b1670();
    *(float *)(local_3c + 0x7c) = (float)fVar7;
    *(undefined4 *)(local_3c + 0x78) = 0x497423fe;
  }
LAB_006580fe:
  fVar7 = (float10)FUN_004b1670();
  local_9c = (float)fVar7;
  if (*(float *)(local_3c + 0x7c) <= local_9c && local_9c != *(float *)(local_3c + 0x7c)) {
    cVar1 = FUN_005c84d0(local_3c + 0xd4);
    if (((cVar1 == '\0') && (cVar1 = FUN_005c84d0(local_3c + 0xd8), cVar1 == '\0')) &&
       ((cVar1 = FUN_005c84d0(local_3c + 0xdc), cVar1 == '\0' &&
        (cVar1 = FUN_005c84d0(local_3c + 0xe0), cVar1 == '\0')))) {
      *(undefined4 *)(local_3c + 0x7c) = 0x497423fe;
    }
    else {
      fVar7 = (float10)FUN_004b1670();
      local_a4 = (float)fVar7;
      *(float *)(local_3c + 0x7c) = local_a4 + 300.0;
      *(int *)(local_3c + 0x128) = *(int *)(local_3c + 0x128) + 1;
      if (*(int *)(local_3c + 0x128) == 3) {
        *(undefined4 *)(local_3c + 0x124) = 6;
      }
      for (local_40 = 0; local_40 < *(int *)(local_3c + 0x124); local_40 = local_40 + 1) {
        if (*(int *)(local_3c + 0xe4 + local_40 * 4) == 0) {
LAB_0065825d:
          uVar10 = 0;
          uVar9 = 0;
          pcVar8 = "annoy_1";
          uVar2 = 2;
          uVar3 = rand();
          uVar3 = uVar3 & 0x80000003;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
          }
          uVar2 = FUN_005c8250((&PTR_s_svfigh_008fe6e4)[uVar3],uVar2,pcVar8,uVar9,uVar10);
          *(undefined4 *)(local_3c + 0xe4 + local_40 * 4) = uVar2;
          FUN_005cb960(*(undefined4 *)(local_3c + 0xe4 + local_40 * 4),"annoy_1_path",1);
        }
        else {
          fVar7 = (float10)FUN_005cced0(*(undefined4 *)(local_3c + 0xe4 + local_40 * 4));
          local_ac = (float)fVar7;
          if (local_ac <= 0.0) goto LAB_0065825d;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

