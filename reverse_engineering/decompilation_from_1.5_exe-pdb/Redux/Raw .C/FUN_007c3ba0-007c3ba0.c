
void FUN_007c3ba0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    iVar1 = size();
    if (iVar1 <= local_8) break;
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    operator_delete((void *)*puVar2);
    local_8 = local_8 + 1;
  }
  FUN_0041ff50();
  return;
}

