
void __thiscall FUN_005788e0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00577200(param_2,param_1);
  if (iVar1 != 0) {
    uVar2 = FUN_0041f870();
    uVar2 = FUN_0041f870(uVar2);
    uVar2 = FUN_0081cb40("multi_message",&DAT_00884a48,uVar2);
    FUN_0056fcb0("%s: %s => %s",uVar2);
    FID_conflict_operator_(param_3);
  }
  return;
}

