
undefined4 __fastcall FUN_005d8610(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  float10 fVar5;
  
  if (*(int *)(param_1 + 8) == 0xd) {
    uVar3 = 0;
  }
  else {
    iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
      uVar3 = 0;
    }
    else {
      iVar2 = FUN_00462400();
      fVar4 = (float10)FUN_00462470(*(undefined4 *)(iVar2 + 0xc));
      fVar4 = (float10)FUN_0044fb20((float)fVar4);
      fVar5 = (float10)FUN_00462470(0x41200000);
      fVar4 = (float10)FUN_0044fb20((float)fVar5 + (float)fVar4 + 5.0);
      uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
      fVar5 = (float10)FUN_00462010(uVar3);
      if ((float)fVar4 * (float)fVar4 <= (float)fVar5) {
        *(undefined4 *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x80) = iVar1;
        uVar3 = FUN_004643e0(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x80));
        *(undefined4 *)(param_1 + 0x7c) = uVar3;
        uVar3 = 1;
      }
      else {
        iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0x30))();
        *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x200;
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}

