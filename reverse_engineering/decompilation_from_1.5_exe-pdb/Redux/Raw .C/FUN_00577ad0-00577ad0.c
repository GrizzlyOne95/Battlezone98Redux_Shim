
undefined4 FUN_00577ad0(short param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  FUN_00430590();
  if (param_1 == 0) {
    puVar2 = (undefined4 *)FUN_00420260(local_c);
    local_8 = *puVar2;
  }
  else {
    puVar2 = (undefined4 *)FUN_00578dd0(local_10,&param_1);
    local_8 = *puVar2;
  }
  uVar3 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else {
    iVar4 = FUN_00422150();
    uVar3 = *(undefined4 *)(iVar4 + 4);
  }
  return uVar3;
}

