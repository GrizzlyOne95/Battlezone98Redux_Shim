
undefined4 FUN_0062b3c0(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  int local_8;
  
  iVar1 = *(int *)(param_3 + 4);
  do {
    if (param_1 == 0) {
      return 0;
    }
    for (local_8 = 0; local_8 < *(int *)(iVar1 + 0x14); local_8 = local_8 + 1) {
      piVar2 = (int *)(local_8 * 0x84 + *(int *)(iVar1 + 0x28));
      if ((*piVar2 == *(int *)(param_1 + 8)) && (piVar2[1] == *(int *)(param_1 + 0xc))) {
        FUN_0062afe0(param_1,piVar2,param_3,param_4);
        break;
      }
    }
    if (*(int *)(param_1 + 0x80) != 0) {
      FUN_0062b3c0(*(undefined4 *)(param_1 + 0x80),param_2,param_3,param_4);
    }
    param_1 = *(int *)(param_1 + 0x7c);
  } while( true );
}

