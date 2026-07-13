
void __thiscall FUN_004dc2f0(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  bool bVar8;
  bool local_7;
  
  iVar5 = FUN_00572a70();
  if (iVar5 != 0) {
    return;
  }
  if ((1 < DAT_025cfa1c) && (iVar5 = FUN_004344a0(), iVar5 != 2)) {
    return;
  }
  bVar1 = false;
  bVar2 = false;
  local_7 = false;
  bVar8 = false;
  bVar3 = false;
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
    if ((*(ushort *)(param_2 + 8) >> 4 & 1) == 0) {
      uVar6 = FUN_00461430();
      cVar4 = FUN_004db560(uVar6);
      if ((cVar4 != '\0') &&
         (cVar4 = FUN_004db600(*(ushort *)(param_2 + 8) >> 6 & 0xf), cVar4 != '\0')) {
        bVar3 = true;
      }
    }
    else {
      uVar6 = FUN_0047e9a0(*(undefined4 *)(param_2 + 4));
      cVar4 = FUN_004db560(uVar6);
      bVar8 = cVar4 == '\0';
      local_7 = !bVar8;
    }
  }
  else {
    if (*(int *)(param_2 + 4) != 0) {
      uVar6 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
      uVar7 = FUN_0047e9a0(*(undefined4 *)(param_2 + 4),uVar6);
      FUN_005e0bc0(uVar7);
      cVar4 = FUN_005e1310(uVar6);
      if (cVar4 != '\0') {
        bVar1 = true;
        goto LAB_004dc40d;
      }
    }
    bVar2 = true;
  }
LAB_004dc40d:
  iVar5 = FUN_004344a0();
  if (iVar5 == 2) {
    if (bVar1) {
      if (DAT_025cfa1c == 0) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.0;
      }
      if (DAT_025cfa1c == 1) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.0;
      }
      if (DAT_025cfa1c == 2) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.5;
      }
    }
    else if (bVar2) {
      if (DAT_025cfa1c == 0) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.25;
      }
      if (DAT_025cfa1c == 1) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.5;
      }
      if (DAT_025cfa1c == 2) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.75;
      }
    }
    else if (local_7) {
      if (DAT_025cfa1c == 0) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.0;
      }
      if (DAT_025cfa1c == 1) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.0;
      }
      if (DAT_025cfa1c == 2) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.5;
      }
    }
    else if (bVar8) {
      if (DAT_025cfa1c == 0) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 3.5;
      }
      if (DAT_025cfa1c == 1) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 3.0;
      }
      if (DAT_025cfa1c == 2) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 2.5;
      }
    }
    else if (bVar3) {
      if (DAT_025cfa1c == 0) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.25;
      }
      if (DAT_025cfa1c == 1) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.5;
      }
      if (DAT_025cfa1c == 2) {
        *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) * 0.75;
      }
    }
  }
  else if (bVar1) {
    *(float *)(param_2 + 0xc) = (float)DAT_025cfa1c * 0.5 * *(float *)(param_2 + 0xc);
  }
  else if (bVar2) {
    *(float *)(param_2 + 0xc) = ((float)DAT_025cfa1c * 0.25 + 0.5) * *(float *)(param_2 + 0xc);
  }
  else if (local_7) {
    *(float *)(param_2 + 0xc) = (float)DAT_025cfa1c * 0.5 * *(float *)(param_2 + 0xc);
  }
  else if (bVar8) {
    *(float *)(param_2 + 0xc) = (1.5 - (float)DAT_025cfa1c * 0.25) * *(float *)(param_2 + 0xc);
  }
  return;
}

