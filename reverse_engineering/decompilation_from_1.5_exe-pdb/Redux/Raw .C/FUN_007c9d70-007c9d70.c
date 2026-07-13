
void __fastcall FUN_007c9d70(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = size(param_1);
    if (uVar1 <= local_8) break;
    uVar1 = FUN_007c19b0();
    iVar2 = (uVar1 & 0xff) + 2;
    FUN_004200d0(local_8);
    FUN_007d3f20(iVar2);
    local_8 = local_8 + 1;
  }
  FUN_00417c60();
  return;
}

