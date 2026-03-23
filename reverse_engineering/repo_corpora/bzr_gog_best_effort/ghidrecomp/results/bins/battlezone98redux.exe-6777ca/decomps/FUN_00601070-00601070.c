
void __fastcall FUN_00601070(int param_1)

{
  float *pfVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  
  fVar5 = (float10)FUN_00822d80();
  *(float *)(param_1 + 0x84) = (float)fVar5 + 5.0;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
  *(undefined4 *)(param_1 + 0x88) = *puVar2;
  *(undefined4 *)(param_1 + 0x8c) = puVar2[1];
  *(undefined4 *)(param_1 + 0x90) = puVar2[2];
  if (*(int *)(param_1 + 0x40) == 0) {
    uVar3 = FUN_004666c0();
    *(undefined4 *)(param_1 + 0x40) = uVar3;
  }
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0x40) + 8) + -8 +
                    *(int *)(*(int *)(param_1 + 0x40) + 4) * 8);
  *(float *)(param_1 + 0x34) = *pfVar1;
  iVar4 = FUN_0077d560((double)*pfVar1,(double)pfVar1[1]);
  if (iVar4 == 0) {
    *(undefined4 *)(param_1 + 0x38) = 0;
    FUN_007d6c70("UnitTask::InitGoto received invalid point (x,y,z) of (%f,%f,%f)",
                 (double)*(float *)(param_1 + 0x34),(double)*(float *)(param_1 + 0x38),
                 (double)*(float *)(param_1 + 0x3c));
  }
  else {
    fVar5 = (float10)FUN_007855e0((double)*pfVar1,(double)pfVar1[1]);
    *(float *)(param_1 + 0x38) = (float)fVar5;
  }
  *(float *)(param_1 + 0x3c) = pfVar1[1];
  return;
}

