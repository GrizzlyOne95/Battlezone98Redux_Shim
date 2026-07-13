
void __fastcall FUN_005b60e0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_58," RecycleTask:");
  FUN_004b70f0(local_58,DAT_0091755c);
  sprintf(local_58," curState (%s)");
  FUN_004b70f0(local_58,DAT_0091755c);
  sprintf(local_58," nextState (%s)");
  FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  if (*(int *)(param_1 + 0x48) == 2) {
    iVar1 = FUN_00462630();
    if (iVar1 != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 0xc))();
      uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
      FUN_00462010(uVar2);
      fVar3 = (float10)FUN_00417910();
      sprintf(local_58," Scrap dist (%f)",(double)(float)fVar3);
      FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    }
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    (**(code **)(**(int **)(param_1 + 0x30) + 0x20))();
  }
  FUN_0083e885();
  return;
}

