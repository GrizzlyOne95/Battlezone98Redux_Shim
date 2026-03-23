
undefined4 __fastcall FUN_005d8370(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  
  if (*(int *)(param_1 + 8) == 0xd) {
    return 0;
  }
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 != 0) {
    iVar2 = FUN_00462400();
    fVar6 = (float10)FUN_00462470(*(undefined4 *)(iVar2 + 0xc));
    fVar6 = (float10)FUN_0044fb20((float)fVar6);
    fVar7 = (float10)FUN_00462470(0x41a00000);
    fVar6 = (float10)FUN_0044fb20((float)fVar7 + (float)fVar6 + 5.0);
    pfVar3 = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
    pfVar4 = (float *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    fVar7 = (float10)FUN_00462010(pfVar3,param_1 + 0x34);
    if (((float)fVar7 < 25.0) ||
       ((fVar7 = (float10)FUN_00453f80(*pfVar3 - *pfVar4), (float)fVar7 < (float)fVar6 &&
        (fVar7 = (float10)FUN_00453f80(pfVar3[2] - pfVar4[2]), (float)fVar7 < (float)fVar6)))) {
      iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0x30))();
      *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x200;
      uVar5 = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x18) = 0;
      *(int *)(param_1 + 0x80) = iVar1;
      uVar5 = FUN_004643e0(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x80));
      *(undefined4 *)(param_1 + 0x7c) = uVar5;
      uVar5 = 1;
    }
    return uVar5;
  }
  *(undefined4 *)(param_1 + 0xc) = 0xd;
  return 0;
}

