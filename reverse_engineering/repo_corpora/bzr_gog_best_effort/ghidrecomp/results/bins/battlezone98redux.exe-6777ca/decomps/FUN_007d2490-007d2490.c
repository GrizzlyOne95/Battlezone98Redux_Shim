
uint FUN_007d2490(undefined4 param_1,undefined2 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 extraout_var;
  undefined4 uVar4;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    uVar2 = size();
    if ((int)uVar2 <= local_8) {
      return uVar2 & 0xffffff00;
    }
    uVar4 = extraout_var;
    puVar3 = (undefined4 *)FUN_004200d0(local_8);
    cVar1 = (**(code **)(*(int *)*puVar3 + 0x14))(param_1,param_2,(int *)*puVar3,uVar4);
    if (cVar1 != '\0') break;
    local_8 = local_8 + 1;
  }
  return 1;
}

