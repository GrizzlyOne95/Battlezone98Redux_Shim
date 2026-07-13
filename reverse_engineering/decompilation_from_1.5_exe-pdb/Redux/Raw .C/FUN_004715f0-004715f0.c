
uint __thiscall FUN_004715f0(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  float10 fVar3;
  
  if (param_2 == 0) {
    uVar2 = 0;
    if ((((*(int *)(param_1 + 0x1c) == 0xb) ||
         (uVar2 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x34) + 0x18))(),
         *(int *)(uVar2 + 0x14) != 0x41504300)) || (*(int *)(*(int *)(param_1 + 0x34) + 0x300) != 0)
        ) || (fVar3 = (float10)FUN_00822d80(), uVar2 = param_1,
             (float)fVar3 <= *(float *)(param_1 + 0x4c) + 1.0)) {
      uVar2 = uVar2 & 0xffffff00;
    }
    else {
      FUN_004dbce0(0xb);
      iVar1 = *(int *)(param_1 + 0x34);
      *(int *)(iVar1 + 200) = *(int *)(*(int *)(param_1 + 0x34) + 200) + 1;
      *(undefined4 *)(param_1 + 0x20) = 0xb;
      uVar2 = CONCAT31((int3)((uint)iVar1 >> 8),1);
    }
  }
  else if ((param_2 == 1) && (*(int *)(param_1 + 0x1c) == 7)) {
    if (*(int *)(param_1 + 0x38) == 0) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),9,0);
    }
    else {
      iVar1 = FUN_004714e0();
      if (iVar1 == 5) {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),5,0);
      }
      else {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),9,0);
      }
    }
    uVar2 = FUN_004dbb40();
    uVar2 = uVar2 & 0xffffff00;
  }
  else {
    uVar2 = FUN_005fad00(param_2);
  }
  return uVar2;
}

