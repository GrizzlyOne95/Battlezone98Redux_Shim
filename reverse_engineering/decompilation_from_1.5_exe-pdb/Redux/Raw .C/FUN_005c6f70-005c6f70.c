
void FUN_005c6f70(void)

{
  char cVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  float fVar6;
  int iVar7;
  float extraout_EDX;
  float extraout_EDX_00;
  int local_34;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  float local_28;
  int local_24;
  char local_1d;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = FUN_004344a0();
  if ((iVar2 != 2) || (cVar1 = FUN_005ddde0(), cVar1 == '\0')) {
    if ((DAT_02cecee0 != DAT_02a13d14) ||
       (((DAT_02cecee4 != DAT_02a13d18 || (*(byte *)(DAT_0094672c + 0x26) != DAT_02a13d1c)) ||
        (fVar3 = (float)FUN_00689eb0(), DAT_00918268 != fVar3)))) {
      FUN_005c6cf0();
    }
    local_1d = FUN_0047c070();
    if (local_1d == 'a') {
      *(undefined4 *)(local_1c + 0xc) = DAT_00918294;
      *(undefined4 *)(local_1c + 0x14) = DAT_00918274;
    }
    else {
      *(undefined4 *)(local_1c + 0xc) = DAT_00918288;
      *(undefined4 *)(local_1c + 0x14) = DAT_00918298;
    }
    local_24 = FUN_00462370();
    if (local_24 != 0) {
      local_28 = DAT_00920ef4;
      if (400 < DAT_02cecee0) {
        fVar3 = (float)FUN_00689eb0();
        iVar2 = FUN_0068f090(*(undefined4 *)(local_1c + 0xc));
        FUN_00689eb0();
        iVar4 = FUN_0068f0c0(*(undefined4 *)(local_1c + 0xc));
        DAT_00920ef4 = local_28 + 0.001;
        uVar5 = FUN_004d9b40(*(undefined4 *)(local_1c + 0xc),DAT_00918260,DAT_00918264,
                             (int)(((float)iVar2 * fVar3) / 2.0),
                             (int)(((float)iVar4 * extraout_EDX) / 2.0),1,0);
        FUN_0068ca30(DAT_00917580,uVar5);
      }
      DAT_00920ef4 = local_28;
      uVar5 = FUN_0081cb40("names","Scrap",DAT_00917550,DAT_0091755c,0xffffffff,0,1,0);
      FUN_004c0100(DAT_00917580,DAT_0091829c,DAT_009182a0,local_30,local_2c,uVar5);
      uVar5 = FUN_005e1190();
      uVar5 = FUN_005e10b0(uVar5);
      sprintf(local_18,"%02ld/%02ld",uVar5);
      FUN_004c0100(DAT_00917580,DAT_0091826c,DAT_00918270,local_30,local_2c,local_18,DAT_00917550,
                   DAT_0091755c,0xffffffff,0,1,0);
      fVar3 = (float)FUN_00689eb0();
      iVar2 = FUN_0068f090(*(undefined4 *)(local_1c + 0xc));
      if (400 < DAT_02cecee0) {
        DAT_00920ef4 = local_28 + 0.001;
        fVar6 = (float)FUN_00689eb0();
        iVar4 = FUN_0068f090(*(undefined4 *)(local_1c + 0x14));
        FUN_00689eb0();
        iVar7 = FUN_0068f0c0(*(undefined4 *)(local_1c + 0x14));
        local_34 = DAT_0091828c;
        if (DAT_00915567 != '\0') {
          local_34 = DAT_00918260 + (int)(((float)iVar2 * fVar3) / 2.0);
        }
        uVar5 = FUN_004d9b40(*(undefined4 *)(local_1c + 0x14),local_34,DAT_00918290,
                             (int)(((float)iVar4 * fVar6) / 2.0),
                             (int)(((float)iVar7 * extraout_EDX_00) / 2.0),1,0);
        FUN_0068ca30(DAT_00917580,uVar5);
        DAT_00920ef4 = local_28;
      }
      uVar5 = FUN_0081cb40("names","Pilots",DAT_00917550,DAT_0091755c,0xffffffff,0,1,0);
      FUN_004c0100(DAT_00917580,DAT_00918280,DAT_00918284,local_30,local_2c,uVar5);
      uVar5 = FUN_0045bba0();
      uVar5 = FUN_005e1220(uVar5);
      sprintf(local_18,"%02ld/%02ld",uVar5);
      FUN_004c0100(DAT_00917580,DAT_00918278,DAT_0091827c,local_30,local_2c,local_18,DAT_00917550,
                   DAT_0091755c,0xffffffff,0,1,0);
    }
  }
  FUN_0083e885();
  return;
}

