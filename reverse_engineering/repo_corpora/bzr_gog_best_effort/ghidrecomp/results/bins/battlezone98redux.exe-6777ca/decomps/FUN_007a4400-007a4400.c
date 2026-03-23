
void __fastcall FUN_007a4400(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = FUN_004170c0(param_1);
    if (uVar1 <= local_8) break;
    uVar3 = 0;
    uVar1 = local_8;
    FUN_00752d30(local_8);
    uVar2 = FUN_0041f870(uVar1,uVar3);
    FUN_007cabf0(uVar2,uVar1,uVar3);
    local_8 = local_8 + 1;
  }
  return;
}

