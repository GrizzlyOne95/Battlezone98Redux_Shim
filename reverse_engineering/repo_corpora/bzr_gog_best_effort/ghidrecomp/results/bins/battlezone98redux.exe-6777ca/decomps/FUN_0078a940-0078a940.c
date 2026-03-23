
void __fastcall FUN_0078a940(undefined4 param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 local_8;
  
  uVar1 = FUN_007647a0(param_1);
  FUN_007cb5c0();
  FUN_007cafa0(0xffffffff);
  iVar6 = 0;
  local_8 = 0;
  while( true ) {
    uVar2 = FUN_007564f0(param_1,iVar6,uVar1);
    if (uVar2 <= local_8) break;
    iVar3 = FUN_0078ae80(local_8);
    if (*(char *)(iVar3 + 0x48) == '\0') {
      uVar5 = 0;
      iVar3 = iVar6;
      FUN_0078ae80(local_8);
      uVar4 = FUN_0041f870(iVar6,uVar5);
      FUN_007cabf0(uVar4,iVar6,uVar5);
      iVar6 = iVar3 + 1;
    }
    local_8 = local_8 + 1;
  }
  return;
}

