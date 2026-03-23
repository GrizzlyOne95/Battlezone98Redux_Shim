
void FUN_00490980(int param_1,undefined4 param_2,undefined4 param_3)

{
  longlong lVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  int *piVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int local_40;
  int local_3c;
  undefined4 local_38;
  char local_34 [8];
  int local_2c;
  undefined4 *local_28;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849370;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0048f940(param_1,param_2,param_3);
  local_8 = 0;
  *local_28 = ChargeGunClass::vftable;
  FUN_00589430(local_28 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0x700e4deb,0x2e2012e5,local_28 + 0x26,*(undefined4 *)(param_1 + 0x98));
  FUN_00589800(0x700e4deb,0xb9782373,local_28 + 0x27,*(undefined4 *)(param_1 + 0x9c));
  FUN_00589800(0x700e4deb,0xbc8f5a39,local_28 + 0x28,*(undefined4 *)(param_1 + 0xa0));
  FUN_00589800(0x700e4deb,0xedfcc3cb,local_28 + 0x29,*(undefined4 *)(param_1 + 0xa4));
  FUN_00589760(0x700e4deb,0x7e82425c,local_28 + 0x2a,*(undefined4 *)(param_1 + 0xa8));
  lVar1 = (ulonglong)(local_28[0x2a] + 1) * 0x2c;
  uVar2 = FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  local_28[0x2b] = uVar2;
  *(undefined4 *)local_28[0x2b] = 0;
  *(undefined4 *)(local_28[0x2b] + 4) = 0;
  *(undefined4 *)(local_28[0x2b] + 8) = 0;
  *(undefined1 *)(local_28[0x2b] + 0x10) = 0;
  *(undefined4 *)(local_28[0x2b] + 0x20) = 0;
  *(undefined4 *)(local_28[0x2b] + 0x24) = local_28[0x1a];
  *(undefined4 *)(local_28[0x2b] + 0x28) = 0;
  for (local_2c = 1; local_2c <= (int)local_28[0x2a]; local_2c = local_2c + 1) {
    sprintf(local_34,"%d",local_2c);
    fVar4 = (float)local_2c * 0.2;
    iVar3 = local_28[0x2b] + local_2c * 0x2c;
    uVar2 = FUN_00446460(local_34,0xd9356908,iVar3,fVar4);
    FUN_00589800(0x700e4deb,uVar2,iVar3,fVar4);
    uVar7 = 1;
    iVar3 = local_28[0x2b] + 4 + local_2c * 0x2c;
    uVar2 = FUN_00446460(local_34,0x9260ea63,iVar3,1);
    FUN_00589760(0x700e4deb,uVar2,iVar3,uVar7);
    uVar7 = 0x3dcccccd;
    iVar3 = local_28[0x2b] + 8 + local_2c * 0x2c;
    uVar2 = FUN_00446460(local_34,0xd76f37db,iVar3,0x3dcccccd);
    FUN_00589800(0x700e4deb,uVar2,iVar3,uVar7);
    uVar7 = 0;
    iVar3 = local_28[0x2b] + 0xc + local_2c * 0x2c;
    uVar2 = FUN_00446460(local_34,0x22c3372e,iVar3,0);
    FUN_00589800(0x700e4deb,uVar2,iVar3,uVar7);
    uVar7 = 0;
    iVar3 = local_28[0x2b] + 0x10 + local_2c * 0x2c;
    uVar2 = FUN_00446460(local_34,0xcfde2fc0,iVar3,0);
    FUN_0047b6c0(0x700e4deb,uVar2,iVar3,uVar7);
    uVar8 = 0;
    uVar7 = 0;
    piVar5 = &local_40;
    uVar2 = FUN_00446460(local_34,0x10e6fd23,piVar5,0,0);
    FUN_00589c20(0x700e4deb,uVar2,piVar5,uVar7,uVar8);
    if (local_40 == 0 && local_3c == 0) {
      *(undefined4 *)(local_28[0x2b] + 0x20 + local_2c * 0x2c) = 0;
    }
    else {
      uVar2 = FUN_00586c60(local_40,local_3c);
      *(undefined4 *)(local_28[0x2b] + 0x20 + local_2c * 0x2c) = uVar2;
    }
    uVar7 = 0;
    pcVar6 = local_24;
    uVar2 = FUN_00446460(local_34,0x1a05f72c,pcVar6,0);
    FUN_0047b6c0(0x700e4deb,uVar2,pcVar6,uVar7);
    if (local_24[0] == '\0') {
      *(undefined4 *)(local_28[0x2b] + 0x24 + local_2c * 0x2c) =
           *(undefined4 *)(local_28[0x2b] + 0x24 + (local_2c + -1) * 0x2c);
    }
    else {
      uVar2 = FUN_0068bed0(local_24);
      *(undefined4 *)(local_28[0x2b] + 0x24 + local_2c * 0x2c) = uVar2;
    }
    if (*(int *)(local_28[0x2b] + 0x20 + local_2c * 0x2c) == 0) {
      local_38 = 0;
    }
    else {
      local_38 = *(undefined4 *)(*(int *)(local_28[0x2b] + 0x20 + local_2c * 0x2c) + 0x4c);
    }
    *(undefined4 *)(local_28[0x2b] + 0x28 + local_2c * 0x2c) = local_38;
  }
  local_28[0xc] = *(undefined4 *)(local_28[0x2b] + 0x20);
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

