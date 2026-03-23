
void __thiscall FUN_007cb1e0(int param_1,byte param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  int local_c;
  
  FUN_007d3310(param_2);
  for (local_c = 0; iVar1 = size(), local_c < iVar1; local_c = local_c + 1) {
    if (param_2 == 0) {
      puVar2 = (undefined4 *)FUN_004200d0(local_c);
      (**(code **)(*(int *)*puVar2 + 0x24))(0);
    }
    else if (*(int *)(param_1 + 0x14c) - *(int *)(param_1 + 0x150) == local_c) {
      puVar2 = (undefined4 *)FUN_004200d0(local_c);
      (**(code **)(*(int *)*puVar2 + 0x24))(1);
    }
    else {
      puVar2 = (undefined4 *)FUN_004200d0(local_c);
      (**(code **)(*(int *)*puVar2 + 0x24))(0);
    }
    uVar3 = (uint)param_2;
    FUN_004200d0(local_c);
    FUN_007cc5c0(uVar3);
  }
  if (param_2 != 0) {
    uVar3 = FUN_0066b150();
    uVar4 = size();
    if (uVar4 < uVar3) {
      (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(1);
      (**(code **)(**(int **)(param_1 + 0x17c) + 0x24))(1);
      return;
    }
  }
  (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(0);
  (**(code **)(**(int **)(param_1 + 0x17c) + 0x24))(0);
  return;
}

