
void FUN_00830437(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  while( true ) {
    *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) & 0xfc;
    cVar1 = *(char *)(param_2 + 4);
    if (cVar1 == '\x04') {
      return;
    }
    if (cVar1 == '\x05') break;
    if (cVar1 == '\x06') {
      *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 0x24);
      goto LAB_008304d5;
    }
    if (cVar1 != '\a') {
      if (cVar1 == '\b') {
        *(undefined4 *)(param_2 + 0x6c) = *(undefined4 *)(param_1 + 0x24);
      }
      else {
        if (cVar1 != '\t') {
          if (cVar1 != '\n') {
            return;
          }
          if ((3 < (*(int **)(param_2 + 8))[2]) &&
             (iVar2 = **(int **)(param_2 + 8), (*(byte *)(iVar2 + 5) & 3) != 0)) {
            FUN_00830437(param_1,iVar2);
          }
          if (*(int *)(param_2 + 8) != param_2 + 0x10) {
            return;
          }
          *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) | 4;
          return;
        }
        *(undefined4 *)(param_2 + 0x44) = *(undefined4 *)(param_1 + 0x24);
      }
      goto LAB_008304d5;
    }
    iVar2 = *(int *)(param_2 + 8);
    *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) | 4;
    if ((iVar2 != 0) && ((*(byte *)(iVar2 + 5) & 3) != 0)) {
      FUN_00830437(param_1,iVar2);
    }
    param_2 = *(int *)(param_2 + 0xc);
    if ((*(byte *)(param_2 + 5) & 3) == 0) {
      return;
    }
  }
  *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x24);
LAB_008304d5:
  *(int *)(param_1 + 0x24) = param_2;
  return;
}

