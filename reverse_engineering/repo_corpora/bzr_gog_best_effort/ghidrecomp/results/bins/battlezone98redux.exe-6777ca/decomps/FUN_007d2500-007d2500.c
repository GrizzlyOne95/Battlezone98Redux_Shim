
uint FUN_007d2500(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = size();
    if ((int)uVar1 <= local_8) break;
    uVar3 = extraout_var;
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    (**(code **)(*(int *)*puVar2 + 0x18))(param_1,param_2,(int *)*puVar2,uVar3);
    local_8 = local_8 + 1;
  }
  return uVar1 & 0xffffff00;
}

