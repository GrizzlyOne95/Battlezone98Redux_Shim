
undefined4 __fastcall FUN_005a5670(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float10 fVar5;
  float10 fVar6;
  undefined4 uVar7;
  
  if (*(int *)(param_1 + 8) == 0xd) {
    return 0;
  }
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 != 0) {
    iVar2 = FUN_00462400();
    fVar5 = (float10)FUN_00462470(*(undefined4 *)(iVar2 + 0xc));
    fVar5 = (float10)FUN_0044fb20((float)fVar5);
    fVar6 = (float10)FUN_00462470(0x41a00000);
    fVar5 = (float10)FUN_0044fb20((float)fVar6 + (float)fVar5 + 5.0);
    pfVar3 = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
    pfVar4 = (float *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    fVar6 = (float10)FUN_00462010(pfVar3,param_1 + 0x34);
    if (((float)fVar6 < 25.0) ||
       ((fVar6 = (float10)FUN_00453f80(*pfVar3 - *pfVar4), (float)fVar6 < (float)fVar5 &&
        (fVar6 = (float10)FUN_00453f80(pfVar3[2] - pfVar4[2]), (float)fVar6 < (float)fVar5)))) {
      iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0x30))();
      *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x200;
      uVar7 = 1;
      FUN_00462590(1);
      FUN_005e11b0(uVar7);
      uVar7 = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x18) = 0;
      *(undefined4 *)(param_1 + 0x7c) = 0;
      uVar7 = 1;
    }
    return uVar7;
  }
  *(undefined4 *)(param_1 + 0xc) = 0xd;
  return 0;
}

