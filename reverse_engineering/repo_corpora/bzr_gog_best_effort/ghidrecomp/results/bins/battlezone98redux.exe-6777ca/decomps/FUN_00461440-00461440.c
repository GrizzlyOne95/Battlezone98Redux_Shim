
void FUN_00461440(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int local_14;
  
  local_14 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
  if (local_14 == -0x84) {
    return;
  }
  iVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
  if (iVar2 != 0) {
    iVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
    iVar3 = FUN_00461430();
    if (iVar2 != iVar3) {
      bVar1 = false;
      goto LAB_004614ab;
    }
  }
  bVar1 = true;
LAB_004614ab:
  if (bVar1) {
    local_14 = local_14 + 0x84;
  }
  else {
    local_14 = local_14 + 0xa4;
  }
  iVar2 = FUN_005d7230(local_14);
  if (iVar2 != 0) {
    piVar4 = (int *)(**(code **)(iVar2 + 8))();
    (**(code **)(*piVar4 + 0x18))(param_1,param_2);
  }
  return;
}

