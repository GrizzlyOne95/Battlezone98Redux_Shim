
undefined2
FUN_00577c90(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
            undefined4 *param_5)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00578dd0(local_8,&param_1);
  uVar3 = FID_conflict_begin(local_c);
  cVar1 = FUN_004221b0(uVar3);
  if (cVar1 == '\0') {
    if (param_2 != (undefined4 *)0x0) {
      FUN_00422150();
      uVar3 = FUN_0041f870();
      *param_2 = uVar3;
    }
    if (param_3 != (undefined4 *)0x0) {
      iVar4 = FUN_00422150();
      *param_3 = *(undefined4 *)(*(int *)(iVar4 + 4) + 0x6c);
    }
    if (param_4 != (undefined4 *)0x0) {
      iVar4 = FUN_00422150();
      *param_4 = *(undefined4 *)(*(int *)(iVar4 + 4) + 0x70);
    }
    if (param_5 != (undefined4 *)0x0) {
      FUN_00422150();
      uVar3 = FUN_00575f80();
      *param_5 = uVar3;
    }
    puVar5 = (undefined2 *)FUN_00422150();
    uVar2 = *puVar5;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

