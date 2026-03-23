
void __fastcall FUN_0078a560(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_c;
  
  local_c = 0;
  uVar5 = 0;
  while( true ) {
    FUN_00764790(uVar5);
    iVar1 = FUN_004170c0();
    if (iVar1 <= local_c) break;
    uVar4 = 0;
    iVar1 = local_c;
    iVar3 = local_c;
    FUN_00764790(local_c,local_c,0);
    FUN_00752d30(iVar1);
    uVar2 = FUN_0041f870();
    FUN_007cabf0(uVar2,iVar3,uVar4);
    local_c = local_c + 1;
  }
  FUN_00764790(uVar5);
  iVar1 = FUN_004170c0();
  if (iVar1 == 0) {
    uVar4 = 0;
    uVar2 = 0;
    uVar5 = FUN_0081cb40("missions","none_found",0,0);
    FUN_007cabf0(uVar5,uVar2,uVar4);
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x24))(0);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x24))(1);
  }
  return;
}

