
void FUN_0082f5f3(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  if (1 < param_2) {
    if (param_2 < 4) {
      iVar1 = *(int *)(param_1 + 8);
      *param_3 = *(undefined4 *)(iVar1 + -0x10);
      param_3[1] = *(undefined4 *)(iVar1 + -0xc);
      param_3[2] = *(undefined4 *)(iVar1 + -8);
    }
    else {
      if (param_2 == 4) {
        uVar3 = 0x11;
        pcVar2 = "not enough memory";
      }
      else {
        if (param_2 != 5) goto LAB_0082f64c;
        uVar3 = 0x17;
        pcVar2 = "error in error handling";
      }
      uVar3 = FUN_008309f4(param_1,pcVar2,uVar3);
      *param_3 = uVar3;
      param_3[2] = 4;
    }
  }
LAB_0082f64c:
  *(undefined4 **)(param_1 + 8) = param_3 + 4;
  return;
}

