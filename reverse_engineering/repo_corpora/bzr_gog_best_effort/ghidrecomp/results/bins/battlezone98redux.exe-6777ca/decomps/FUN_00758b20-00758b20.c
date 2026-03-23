
void FUN_00758b20(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_8;
  
  FUN_00753a00(&local_8,&param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    iVar3 = FUN_00422150();
    if (*(int *)(iVar3 + 4) == param_2) {
      local_10 = local_8;
      FUN_00429560(local_18,local_8);
    }
  }
  return;
}

