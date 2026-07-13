
void __fastcall FUN_007cb400(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 local_c;
  
  local_c = 0;
  while( true ) {
    uVar3 = size();
    if (uVar3 <= local_c) break;
    iVar1 = *(int *)(param_1 + 0x150);
    puVar4 = (undefined4 *)FUN_004200d0(local_c);
    piVar2 = (int *)*puVar4;
    FUN_0066b170(local_c + iVar1);
    uVar5 = FUN_0041f870();
    (**(code **)(*piVar2 + 0x3c))(uVar5);
    uVar5 = *(undefined4 *)(param_1 + 0x174);
    FUN_004200d0(local_c);
    FUN_007cc6b0(uVar5);
    FUN_004200d0(local_c);
    uVar5 = FUN_007ccaf0();
    FUN_004200d0(local_c);
    FUN_007cca20(uVar5);
    local_c = local_c + 1;
  }
  FUN_007cafa0(*(undefined4 *)(param_1 + 0x14c));
  return;
}

