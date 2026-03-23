
undefined4 FUN_00691390(undefined4 *param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 local_14;
  int local_8;
  
  local_8 = 0;
  local_14 = 0;
  do {
    uVar1 = *(undefined2 *)(*(int *)(param_2 + 0xc) + local_8 * 0xc);
    iVar2 = *(int *)(*(int *)(param_2 + 0xc) + 8 + local_8 * 0xc);
    if (0 < iVar2) {
      local_14 = 1;
      cVar3 = FUN_006a01f0(uVar1,*(undefined1 *)param_1);
      if (cVar3 == '\0') {
        iVar4 = FUN_00691230(uVar1,*param_1);
        if (iVar4 == 0) goto LAB_0069142d;
      }
      FUN_00690df0(param_1,uVar1,param_3,iVar2,1,*(int *)(param_2 + 0xc) + 8 + local_8 * 0xc);
    }
LAB_0069142d:
    local_8 = local_8 + 1;
    if (*(int *)(param_2 + 8) <= local_8) {
      return local_14;
    }
  } while( true );
}

