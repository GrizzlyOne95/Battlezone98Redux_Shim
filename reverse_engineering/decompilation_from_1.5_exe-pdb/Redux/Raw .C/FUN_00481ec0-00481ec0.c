
void FUN_00481ec0(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    local_8 = &DAT_0091739c;
  }
  else {
    local_8 = param_1;
  }
  iVar1 = FUN_004817a0(local_8,param_2);
  if (iVar1 != 0) {
    FUN_00481880(local_8,iVar1);
  }
  return;
}

