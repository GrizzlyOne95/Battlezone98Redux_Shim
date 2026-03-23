
void __thiscall FUN_005ed5c0(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((char)param_2[1] == '\0') {
    (**(code **)(*(int *)(param_1 + -0x18) + 100))();
  }
  else if ((char)param_2[1] == '\x01') {
    (**(code **)(*(int *)(param_1 + -0x18) + 0x60))();
  }
  else if ((char)param_2[1] == '\x02') {
    (**(code **)(*(int *)(param_1 + -0x18) + 0x60))();
  }
  else if ((char)param_2[1] == '\x03') {
    (**(code **)(*(int *)(param_1 + -0x18) + 100))();
  }
  if (*param_2 == 0) {
    FUN_005ed4b0(0);
  }
  else {
    if (*(int *)(param_1 + 0x2e8) != 0) {
      iVar1 = FUN_004b9a90();
      if (iVar1 == *param_2) goto LAB_005ed69d;
    }
    uVar2 = FUN_004b9ab0(*param_2);
    FUN_005ed4b0(uVar2);
  }
LAB_005ed69d:
  *param_3 = *param_3 + -8;
  FUN_004ef240(param_2 + 2,param_3);
  return;
}

