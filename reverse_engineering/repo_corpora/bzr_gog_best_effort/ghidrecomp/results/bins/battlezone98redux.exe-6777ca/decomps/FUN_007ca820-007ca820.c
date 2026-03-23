
undefined4 __thiscall FUN_007ca820(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_c;
  
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') && (cVar1 = FUN_007d2810((float)param_2,(float)param_3), cVar1 != '\0')) {
    *(undefined1 *)(param_1 + 0x148) = 1;
    cVar1 = FUN_007d3360();
    if ((cVar1 != '\0') &&
       (cVar1 = (**(code **)(**(int **)(param_1 + 0x178) + 0x1c))(param_2,param_3,param_4),
       cVar1 != '\0')) {
      return 1;
    }
    cVar1 = FUN_007d3360();
    if ((cVar1 != '\0') &&
       (cVar1 = (**(code **)(**(int **)(param_1 + 0x17c) + 0x1c))(param_2,param_3,param_4),
       cVar1 != '\0')) {
      return 1;
    }
    if (*(char *)(param_1 + 0x158) != '\0') {
      for (local_c = 0; iVar2 = size(), local_c < iVar2; local_c = local_c + 1) {
        puVar3 = (undefined4 *)FUN_004200d0(local_c);
        (**(code **)(*(int *)*puVar3 + 0x1c))(param_2,param_3,param_4);
      }
      return 1;
    }
  }
  return 0;
}

