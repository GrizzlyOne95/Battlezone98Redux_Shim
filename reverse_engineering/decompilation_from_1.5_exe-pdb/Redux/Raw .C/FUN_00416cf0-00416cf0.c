
int __fastcall FUN_00416cf0(int param_1)

{
  int iVar1;
  char local_5;
  
  if (**(int **)(param_1 + 4) == 0) {
    iVar1 = -0x7ffbfe10;
  }
  else {
    if ((*(int *)(param_1 + 0x28) != 0) &&
       (iVar1 = ov_raw_seek(*(undefined4 *)(param_1 + 0x2c),0,0), iVar1 != 0)) {
      FUN_007d6a70("  ::Reset() got error %d\n",iVar1);
    }
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    FUN_004394a0(**(undefined4 **)(param_1 + 4),&local_5);
    if ((local_5 == '\0') || (iVar1 = FUN_00416e10(**(undefined4 **)(param_1 + 4),0), -1 < iVar1)) {
      iVar1 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 4) + 0x34))
                        (**(undefined4 **)(param_1 + 4),0);
    }
  }
  return iVar1;
}

