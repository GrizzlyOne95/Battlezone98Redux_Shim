
undefined4 FUN_0082d8f0(undefined4 param_1,char *param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = 1;
  if (param_4 == 0) {
    FUN_0082dd72(param_3);
  }
  else {
    cVar1 = *param_2;
    while (cVar1 != '\0') {
      if (cVar1 != 'L') {
        if (cVar1 == 'S') {
          FUN_0082db70(param_3,param_4);
        }
        else if (cVar1 != 'f') {
          if (cVar1 == 'l') {
            if (param_5 == 0) {
              uVar3 = 0xffffffff;
            }
            else {
              uVar3 = FUN_0082da9d(param_1,param_5);
            }
            *(undefined4 *)(param_3 + 0x14) = uVar3;
          }
          else if (cVar1 == 'n') {
            if (param_5 == 0) {
              iVar2 = 0;
            }
            else {
              iVar2 = FUN_0082dbdc(param_1,param_5,param_3 + 4);
            }
            *(int *)(param_3 + 8) = iVar2;
            if (iVar2 == 0) {
              *(undefined4 *)(param_3 + 4) = 0;
              *(undefined1 **)(param_3 + 8) = &DAT_008a1ad8;
            }
          }
          else if (cVar1 == 'u') {
            *(uint *)(param_3 + 0x18) = (uint)*(byte *)(param_4 + 7);
          }
          else {
            uVar4 = 0;
          }
        }
      }
      param_2 = param_2 + 1;
      cVar1 = *param_2;
    }
  }
  return uVar4;
}

