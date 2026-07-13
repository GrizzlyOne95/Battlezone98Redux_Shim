
void __fastcall FUN_005f5830(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined8 uVar6;
  
  iVar2 = FUN_004625b0();
  if (*(int *)(param_1 + 0x36c) != iVar2) {
    FUN_005f5970();
    uVar3 = FUN_004625b0();
    *(undefined4 *)(param_1 + 0x36c) = uVar3;
    puVar4 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
    uVar6 = FUN_0045c460(*puVar4,puVar4[1],puVar4[2]);
    *(undefined8 *)(param_1 + 0x370) = uVar6;
    FUN_00469900(*(undefined4 *)(param_1 + 0x370),*(undefined4 *)(param_1 + 0x374),0x43160000,
                 *(undefined4 *)(param_1 + 0x36c),1);
    fVar5 = (float10)FUN_00462470();
    fVar1 = (float)fVar5;
    FUN_00469840(*(float *)(param_1 + 0x370) - fVar1,*(float *)(param_1 + 0x374) - fVar1,
                 *(float *)(param_1 + 0x370) + fVar1,*(float *)(param_1 + 0x374) + fVar1,1);
  }
  return;
}

