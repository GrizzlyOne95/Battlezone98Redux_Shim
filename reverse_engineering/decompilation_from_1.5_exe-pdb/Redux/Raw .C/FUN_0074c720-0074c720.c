
void FUN_0074c720(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00578c20(local_8,param_2);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    puVar4 = local_c;
    FUN_00422150(puVar4,param_1);
    FUN_00578c20(puVar4,param_1);
    puVar4 = local_18;
    FUN_00422150(puVar4);
    uVar2 = FID_conflict_begin(puVar4);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 != '\0') {
      iVar3 = FUN_00422150();
      iVar3 = iVar3 + 0x10;
      get(param_2,iVar3);
      FUN_0075d090(param_2,iVar3);
    }
  }
  return;
}

