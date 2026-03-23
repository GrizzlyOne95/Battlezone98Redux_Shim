
void FUN_0047cc40(undefined4 param_1,undefined4 param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  float local_4c;
  int *local_48;
  double local_44;
  double local_3c;
  double local_34;
  undefined1 local_2c [12];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00480340(param_1,param_2);
  *(undefined8 *)(local_48 + 0x3a) = *(undefined8 *)(local_48[5] + 0x48);
  *(undefined8 *)(local_48 + 0x3c) = *(undefined8 *)(local_48[5] + 0x50);
  *(undefined8 *)(local_48 + 0x3e) = *(undefined8 *)(local_48[5] + 0x58);
  DAT_009175b4 = 1;
  local_4c = *(float *)(local_48[3] + 0x50);
  dVar1 = *(double *)(local_48[5] + 0x48);
  dVar2 = *(double *)(local_48[5] + 0x50);
  dVar3 = *(double *)(local_48[5] + 0x58);
  local_20._0_4_ = SUB84(dVar1,0);
  local_20._4_4_ = (undefined4)((ulonglong)dVar1 >> 0x20);
  uVar11 = local_20._4_4_;
  local_18._0_4_ = SUB84(dVar2,0);
  local_18._4_4_ = (undefined4)((ulonglong)dVar2 >> 0x20);
  uVar4 = local_18._4_4_;
  local_10._0_4_ = SUB84(dVar3,0);
  local_10._4_4_ = (undefined4)((ulonglong)dVar3 >> 0x20);
  uVar5 = local_10._4_4_;
  uVar6 = (undefined4)local_20;
  local_20 = dVar1;
  uVar7 = (undefined4)local_18;
  local_18 = dVar2;
  uVar8 = (undefined4)local_10;
  local_10 = dVar3;
  iVar9 = FUN_00784620(uVar6,uVar11,uVar7,uVar4,uVar8,uVar5,local_48[0xc],local_48[0xd],
                       local_48[0xe],&local_4c,local_2c);
  local_44 = (double)(local_4c * (float)local_48[0xc]) + local_20;
  local_3c = (double)(local_4c * (float)local_48[0xd]) + local_18;
  local_34 = (double)(local_4c * (float)local_48[0xe]) + local_10;
  iVar10 = FUN_00480f40(&local_4c,&local_44,local_2c);
  *(double *)(local_48[5] + 0x48) = local_44;
  *(double *)(local_48[5] + 0x50) = local_3c;
  *(double *)(local_48[5] + 0x58) = local_34;
  if (iVar10 == 0) {
    if (iVar9 != 0) {
      (**(code **)(*local_48 + 0x14))(0,local_2c);
    }
  }
  else {
    uVar11 = FUN_00479f30(iVar10,local_2c);
    (**(code **)(*local_48 + 0x14))(uVar11);
  }
  *(uint *)(local_48[5] + 0x14) = *(uint *)(local_48[5] + 0x14) & 0xfffffdff;
  FUN_0044dc60(local_48[5] + 0x20,local_4c);
  local_48[0x1e] = *(int *)(local_48[3] + 0x88);
  FUN_0083e885();
  return;
}

