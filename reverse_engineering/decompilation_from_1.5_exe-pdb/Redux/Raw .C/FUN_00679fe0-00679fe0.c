
void __fastcall FUN_00679fe0(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  
  FUN_00679f10();
  FUN_00679800();
  uVar5 = *(int *)(param_1 + 400) + 1;
  *(uint *)(param_1 + 400) = uVar5;
  uVar3 = size();
  if (uVar3 <= uVar5) {
    FUN_006783d0();
  }
  uVar5 = *(int *)(param_1 + 0x194) + 1;
  *(uint *)(param_1 + 0x194) = uVar5;
  uVar3 = size();
  if (uVar3 <= uVar5) {
    FUN_00678410();
  }
  *(undefined4 *)(param_1 + 0x1d4) = 0;
  *(undefined4 *)(param_1 + 0x1d8) = 0;
  FUN_00679700();
  if (*(int *)(param_1 + 0x1c8) != 0) {
    uVar4 = (**(code **)(**(int **)(param_1 + 0x1c8) + 4))();
    uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x1c8) + 0x94);
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x1c8) + 0xb0);
    if (*(int *)(*(int *)(param_1 + 0x1c8) + 0x58) != 0) {
      FUN_00679830(0);
    }
    FUN_00679ac0(uVar4,uVar2,uVar1);
  }
  return;
}

