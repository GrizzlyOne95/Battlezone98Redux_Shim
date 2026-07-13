
void FUN_008356a9(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint local_8;
  
  iVar1 = FUN_0082d377(*(undefined4 *)(param_1 + 8),3,&local_8);
  uVar3 = 0;
  if (local_8 != 0) {
    do {
      if (*(char *)(uVar3 + iVar1) == '%') {
        uVar3 = uVar3 + 1;
        iVar2 = isdigit((uint)*(byte *)(uVar3 + iVar1));
        if (iVar2 == 0) goto LAB_008356e7;
        if (*(char *)(uVar3 + iVar1) == '0') {
          FUN_0082b81b(param_2,param_3,param_4 - param_3);
        }
        else {
          FUN_00836056(param_1,*(char *)(uVar3 + iVar1) + -0x31,param_3,param_4);
          FUN_0082b87b(param_2);
        }
      }
      else {
LAB_008356e7:
        if (param_2 + 0x83 <= (int *)*param_2) {
          FUN_0082c2ac(param_2);
        }
        *(undefined1 *)*param_2 = *(undefined1 *)(uVar3 + iVar1);
        *param_2 = *param_2 + 1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < local_8);
  }
  return;
}

