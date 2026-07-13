
void __thiscall FUN_00432e40(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  if (param_2 != param_1) {
    local_c = param_1;
    FUN_0042d8c0(&local_10);
    FID_conflict_begin(&local_1c);
    FUN_0042d8c0(&local_8);
    FID_conflict_begin(&local_14);
    while ((cVar1 = FUN_00420f10(&local_1c), cVar1 != '\0' &&
           (cVar1 = FUN_00420f10(&local_14), cVar1 != '\0'))) {
      uVar2 = FUN_0042de50();
      uVar3 = FUN_0042de50(uVar2);
      cVar1 = FUN_00433730(uVar3,uVar2);
      if (cVar1 == '\0') {
        FUN_0042da80();
      }
      else {
        local_18 = local_8;
        puVar4 = (undefined4 *)FUN_0042da80();
        FUN_00432ac0(local_10,param_2,local_8,*puVar4,1);
        local_8 = local_18;
      }
    }
    cVar1 = FUN_00420f10(&local_14);
    if (cVar1 != '\0') {
      FUN_00432ac0(local_1c,param_2,local_8,local_14,*(undefined4 *)(param_2 + 4));
    }
  }
  return;
}

