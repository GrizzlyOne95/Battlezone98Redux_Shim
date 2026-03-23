
void __fastcall FUN_00606e20(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float10 fVar5;
  int local_40;
  int local_30;
  int local_20;
  
  uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0x30))();
  uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0x30))(uVar3);
  FUN_00477290(uVar4,uVar3);
  uVar3 = *(undefined4 *)(&DAT_008ea540 + local_20 * 4 + local_30 * 0x20 + local_40 * 0x100);
  *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x18);
  FUN_00606980(uVar3);
  iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  if (0.2 < *(float *)(iVar2 + 0xd0)) {
    *(undefined4 *)(iVar2 + 0xd0) = 0x3f800000;
  }
  iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  fVar1 = *(float *)(param_1 + 0xdc);
  fVar5 = (float10)FUN_00822d60(0xbf800000,0x3f800000);
  fVar5 = (float10)FUN_00447ed0(fVar1 * 20.0 * (float)fVar5 + *(float *)(param_1 + 0xb0));
  *(float *)(param_1 + 0xb0) = (float)fVar5;
  *(undefined4 *)(iVar2 + 200) = *(undefined4 *)(param_1 + 0xb0);
  return;
}

