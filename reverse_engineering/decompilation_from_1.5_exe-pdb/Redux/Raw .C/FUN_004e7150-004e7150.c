
undefined1 __fastcall FUN_004e7150(int *param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  
  iVar3 = FUN_00462630(param_1[5]);
  param_1[6] = iVar3;
  if (param_1[6] == 0) {
    param_1[3] = 0xd;
    uVar2 = 0;
  }
  else {
    uVar4 = (**(code **)(*(int *)(param_1[6] + 0x18) + 0xc))();
    uVar4 = (**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))(uVar4);
    fVar5 = (float10)FUN_00462010(uVar4);
    param_1[0x56] = (int)(float)fVar5;
    if ((float)param_1[0x56] <= (float)param_1[0x53] && (float)param_1[0x53] != (float)param_1[0x56]
       ) {
      if ((char)param_1[0x54] == '\0') {
        fVar5 = (float10)FUN_00822d80();
        param_1[0x55] = (int)(float)fVar5;
        *(undefined1 *)(param_1 + 0x54) = 1;
      }
      param_1[0x1f] = 0;
      cVar1 = (**(code **)(*param_1 + 0x3c))();
      if (cVar1 == '\0') {
        return 0;
      }
    }
    param_1[0x20] = param_1[6];
    iVar3 = FUN_004643e0(param_1[4],param_1[0x20]);
    param_1[0x1f] = iVar3;
    uVar2 = 1;
  }
  return uVar2;
}

