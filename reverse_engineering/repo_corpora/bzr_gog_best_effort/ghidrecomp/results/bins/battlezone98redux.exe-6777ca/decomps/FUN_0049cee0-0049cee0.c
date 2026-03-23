
void __thiscall FUN_0049cee0(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  FUN_005e1010(*(undefined4 *)(*(int *)(param_1 + 0x370) + 0x4c));
  iVar2 = FUN_00572a70();
  if (iVar2 != 0) {
    cVar1 = FUN_004b9860();
    if (cVar1 == '\0') {
      iVar2 = FUN_00572a70();
      if (iVar2 != 0) {
        cVar1 = FUN_004b9830();
        if (cVar1 != '\0') {
          FUN_004b9940();
          FUN_004b7bd0();
        }
      }
      goto LAB_0049cf61;
    }
  }
  (**(code **)(*(int *)(param_2 + 0x18) + 0x10))();
LAB_0049cf61:
  *(undefined4 *)(param_1 + 0x3bc) = 0;
  *(undefined4 *)(param_1 + 0x304) = 0;
  return;
}

