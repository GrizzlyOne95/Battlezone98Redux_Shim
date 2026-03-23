
void FUN_007d37f0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    iVar1 = size();
    if (iVar1 <= local_8) break;
    uVar3 = extraout_var;
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    (**(code **)(*(int *)*puVar2 + 0x34))((int *)*puVar2,uVar3);
    local_8 = local_8 + 1;
  }
  return;
}

