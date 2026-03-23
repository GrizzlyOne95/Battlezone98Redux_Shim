
void FUN_0045e290(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10 [2];
  undefined4 local_8;
  
  FID_conflict_begin(local_10);
  FUN_0042d8c0(&local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_1c);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_0042de50();
    if (*piVar3 == *param_1) {
      uVar2 = FUN_0042de50();
      iVar4 = FUN_00417780(uVar2);
      iVar5 = FUN_00417780(param_1);
      if (iVar4 == iVar5) {
        puVar6 = (undefined4 *)FUN_00438c10(local_20,0);
        local_10[0] = *puVar6;
      }
      else {
        local_14 = local_8;
        puVar6 = (undefined4 *)FUN_0042d920(local_24,local_8);
        local_8 = *puVar6;
      }
    }
    else {
      FUN_0042da80();
    }
  }
  uVar2 = FID_conflict_begin(local_28);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    local_18 = local_10[0];
    FUN_0042d920(local_2c,local_10[0]);
  }
  return;
}

