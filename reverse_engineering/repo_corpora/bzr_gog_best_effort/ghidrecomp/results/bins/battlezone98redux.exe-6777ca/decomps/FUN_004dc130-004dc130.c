
void __thiscall FUN_004dc130(int param_1,int *param_2)

{
  float fVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  
  fVar5 = (float10)FUN_00822da0();
  fVar1 = (float)fVar5;
  *(undefined4 *)(param_1 + 0x98) = 0;
  if (param_2[1] == 0) {
    *(float *)(param_1 + 0x1f0) = fVar1;
  }
  else if (*param_2 == param_2[1]) {
    if ((*(ushort *)(param_2 + 2) >> 4 & 1) != 0) {
      *(float *)(param_1 + 0x1dc) = fVar1;
    }
    uVar3 = FUN_0047e9a0(param_2[1]);
    cVar2 = FUN_004db600(uVar3);
    if (cVar2 == '\0') {
      *(float *)(param_1 + 0x1e4) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x1ec) = fVar1;
    }
  }
  else {
    if ((*(ushort *)(param_2 + 2) >> 4 & 1) != 0) {
      *(float *)(param_1 + 0x1d8) = fVar1;
    }
    uVar3 = FUN_0047e9a0(param_2[1]);
    cVar2 = FUN_004db600(uVar3);
    if (cVar2 == '\0') {
      *(float *)(param_1 + 0x1e0) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x1e8) = fVar1;
      FUN_0047c3e0(param_1);
    }
    iVar4 = FUN_00479f30(*param_2);
    if ((iVar4 != 0) && (iVar4 != param_1)) {
      uVar3 = FUN_00462380();
      *(undefined4 *)(param_1 + 500) = uVar3;
      uVar3 = FUN_00462380();
      FUN_004dc2c0(uVar3);
      uVar3 = (**(code **)(*(int *)(iVar4 + 0x18) + 4))();
      FUN_004db4f0(uVar3);
    }
  }
  return;
}

