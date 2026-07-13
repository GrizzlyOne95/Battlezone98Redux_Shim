
void __thiscall FUN_006ce9d0(int param_1,int param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar1 = *(uint *)(param_2 + 8);
  cVar2 = FUN_0041fc90();
  if (cVar2 == '\0') {
    uVar3 = FUN_0046b240();
    if (uVar1 < uVar3) {
      iVar4 = FUN_0046b240();
      if (uVar1 == iVar4 - 1U) {
        FUN_006d23d0();
      }
      else {
        iVar4 = FUN_0046b240();
        FUN_006d2300(uVar1,iVar4 + -1);
        FUN_006d23d0();
        if (uVar1 != 0) {
          uVar5 = FUN_005111d0(uVar1 - 1 >> 1);
          uVar6 = FUN_005111d0(uVar1);
          cVar2 = FUN_006b2ad0(uVar6,uVar5);
          if (cVar2 != '\0') {
            FUN_006ce960(uVar1);
            goto LAB_006ceaa6;
          }
        }
        FUN_006d2210(uVar1);
      }
    }
  }
LAB_006ceaa6:
  if (*(int *)(param_1 + 8) == param_2) {
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 0xc);
  }
  if (*(int *)(param_2 + 0x10) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0x10) + 0xc) = *(undefined4 *)(param_2 + 0xc);
  }
  if (*(int *)(param_2 + 0xc) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0xc) + 0x10) = *(undefined4 *)(param_2 + 0x10);
  }
  *(undefined4 *)(param_2 + 0xc) = 0;
  *(undefined4 *)(param_2 + 0x10) = 0;
  return;
}

