
undefined4 __thiscall FUN_007ca970(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  bool bVar5;
  uint local_20;
  byte *local_18;
  byte *local_14;
  int local_10;
  
  cVar2 = FUN_007d3360();
  if ((((cVar2 != '\0') && (cVar2 = FUN_007d2810((float)param_2,(float)param_3), cVar2 != '\0')) &&
      (*(char *)(param_1 + 0x148) != '\0')) && (param_4 == 0)) {
    cVar2 = FUN_007d3360();
    if ((cVar2 != '\0') &&
       (cVar2 = (**(code **)(**(int **)(param_1 + 0x178) + 0x20))(param_2,param_3,0), cVar2 != '\0')
       ) {
      return 1;
    }
    cVar2 = FUN_007d3360();
    if ((cVar2 != '\0') &&
       (cVar2 = (**(code **)(**(int **)(param_1 + 0x17c) + 0x20))(param_2,param_3,0), cVar2 != '\0')
       ) {
      return 1;
    }
    if (*(char *)(param_1 + 0x158) != '\0') {
      local_10 = 0;
      while( true ) {
        iVar3 = size();
        if (iVar3 <= local_10) {
          return 1;
        }
        puVar4 = (undefined4 *)FUN_004200d0(local_10);
        cVar2 = (**(code **)(*(int *)*puVar4 + 0x20))(param_2,param_3,0);
        if (cVar2 != '\0') break;
        local_10 = local_10 + 1;
      }
      FUN_004200d0(local_10);
      local_18 = (byte *)FUN_007cc6f0();
      local_14 = &DAT_008a1ad8;
      do {
        bVar1 = *local_14;
        bVar5 = bVar1 < *local_18;
        if (bVar1 != *local_18) {
LAB_007cab37:
          local_20 = -(uint)bVar5 | 1;
          goto LAB_007cab3f;
        }
        if (bVar1 == 0) break;
        bVar1 = local_14[1];
        bVar5 = bVar1 < local_18[1];
        if (bVar1 != local_18[1]) goto LAB_007cab37;
        local_14 = local_14 + 2;
        local_18 = local_18 + 2;
      } while (bVar1 != 0);
      local_20 = 0;
LAB_007cab3f:
      if (local_20 != 0) {
        *(int *)(param_1 + 0x14c) = local_10 + *(int *)(param_1 + 0x150);
        FUN_007cafa0(*(undefined4 *)(param_1 + 0x14c));
        if (*(int *)(param_1 + 0x144) != 0) {
          (**(code **)(param_1 + 0x144))();
        }
      }
      return 1;
    }
  }
  return 0;
}

