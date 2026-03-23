
undefined4 FUN_007d23b0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 extraout_var;
  undefined4 uVar4;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    iVar2 = size();
    if (iVar2 <= local_8) {
      return 0;
    }
    uVar4 = extraout_var;
    puVar3 = (undefined4 *)FUN_004200d0(local_8);
    cVar1 = (**(code **)(*(int *)*puVar3 + 0xc))(param_1,(int *)*puVar3,uVar4);
    if (cVar1 != '\0') break;
    local_8 = local_8 + 1;
  }
  return 1;
}

