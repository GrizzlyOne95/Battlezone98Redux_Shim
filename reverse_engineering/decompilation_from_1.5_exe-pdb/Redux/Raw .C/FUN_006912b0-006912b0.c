
undefined4 FUN_006912b0(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 local_18;
  int local_c;
  
  local_c = 0;
  local_18 = 0;
  do {
    uVar3 = (uint)*(ushort *)(*(int *)(param_2 + 0xc) + local_c * 0xc);
    iVar1 = *(int *)(*(int *)(param_2 + 0xc) + 4 + local_c * 0xc);
    iVar4 = FUN_006a0210(uVar3,(char)*param_1);
    iVar4 = iVar4 + *(int *)(*(int *)(&DAT_00930fc0 + *param_1 * 4) + uVar3 * 4);
    if (iVar4 < iVar1) {
      local_18 = 1;
      cVar2 = FUN_006a01f0(uVar3,(char)*param_1);
      if (cVar2 == '\0') {
        iVar5 = FUN_00691230(uVar3,*param_1);
        if (iVar5 == 0) goto LAB_0069136e;
      }
      FUN_00690df0(param_1,uVar3,param_3,iVar1 - iVar4,0,0);
    }
LAB_0069136e:
    local_c = local_c + 1;
    if (*(int *)(param_2 + 8) <= local_c) {
      return local_18;
    }
  } while( true );
}

