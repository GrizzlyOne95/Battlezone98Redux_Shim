
void __fastcall FUN_005c6cf0(undefined4 param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float extraout_EDX;
  int iVar7;
  float extraout_EDX_00;
  float extraout_EDX_01;
  int iVar8;
  float extraout_EDX_02;
  undefined8 uVar9;
  
  fVar1 = (float)FUN_00689eb0(param_1);
  iVar2 = -(int)((fVar1 * 176.0) / 2.0);
  FUN_00689eb0();
  iVar6 = (int)((extraout_EDX * 10.0) / 2.0);
  fVar1 = (float)FUN_00689eb0();
  iVar7 = (int)((fVar1 * 100.0) / 2.0);
  FUN_00689eb0();
  iVar3 = (int)((extraout_EDX_00 * 10.0) / 2.0);
  FUN_00689eb0();
  fVar1 = (float)FUN_00689eb0();
  fVar4 = (float)FUN_00689eb0();
  iVar8 = (int)((fVar4 * 80.0) / 2.0);
  FUN_00689eb0();
  iVar5 = (int)((extraout_EDX_02 * 10.0) / 2.0);
  uVar9 = FUN_00689eb0();
  DAT_00918260 = DAT_02cecee0 / 2 + iVar2;
  DAT_0091829c = DAT_00918260 + iVar7;
  DAT_009182a0 = iVar6 + iVar3;
  DAT_0091826c = DAT_00918260 + iVar7;
  DAT_00918270 = iVar6 + (int)((extraout_EDX_01 * 18.0) / 2.0) + iVar3;
  DAT_0091828c = DAT_02cecee0 / 2 + (int)((fVar1 * 176.0) / 2.0) + iVar2;
  DAT_00918280 = DAT_0091828c + iVar8;
  DAT_00918284 = iVar6 + iVar5;
  DAT_00918278 = DAT_0091828c + iVar8;
  DAT_0091827c = iVar6 + (int)(((float)((ulonglong)uVar9 >> 0x20) * 18.0) / 2.0) + iVar5;
  DAT_02a13d14 = DAT_02cecee0;
  DAT_02a13d18 = DAT_02cecee4;
  DAT_02a13d1c = (uint)*(byte *)(DAT_0094672c + 0x26);
  DAT_00918264 = iVar6;
  DAT_00918290 = iVar6;
  DAT_00918268 = FUN_00689eb0(param_1,(int)uVar9);
  return;
}

