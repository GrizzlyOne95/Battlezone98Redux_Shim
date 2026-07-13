
void FUN_00493d40(void)

{
  float fVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  float fVar5;
  undefined8 uVar6;
  float fVar7;
  undefined4 extraout_var;
  
  fVar1 = DAT_00920ef4;
  DAT_00920ef4 = DAT_00920ef4 + 0.04;
  cVar2 = FUN_0047c070();
  uVar4 = extraout_var;
  uVar6 = FUN_00689eb0();
  fVar7 = (float)uVar6;
  if ((cVar2 == 'a') || (cVar2 == 'b')) {
    DAT_009173d4 = DAT_009173cc;
  }
  else {
    DAT_009173d4 = DAT_009173c8;
  }
  iVar3 = FUN_0068f090(DAT_009173d4,uVar6,uVar6,uVar4);
  fVar5 = (((float)iVar3 * fVar7) / 2.0) * DAT_008e77b0;
  iVar3 = FUN_0068f0c0(DAT_009173d4);
  uVar4 = FUN_004d9b40(DAT_009173d4,DAT_008e77a8,DAT_008e77ac,(int)fVar5,
                       (int)((((float)iVar3 * fVar7) / 2.0) * DAT_008e77b0),0,0);
  FUN_0068ca30(DAT_00917580,uVar4);
  DAT_00920ef4 = fVar1;
  return;
}

