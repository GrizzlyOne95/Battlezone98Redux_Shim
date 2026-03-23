
void FUN_0075f550(undefined4 *param_1,undefined4 *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  *param_1 = 0;
  *param_2 = 0;
  iVar2 = get();
  FUN_0075fd00(local_c,iVar2 + 0xc18);
  uVar3 = FID_conflict_begin(local_10);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    *param_1 = 0;
    *param_2 = 0;
  }
  else {
    iVar2 = FUN_00422150();
    *param_1 = *(undefined4 *)(*(int *)(iVar2 + 0x1c) + 0x84);
    iVar2 = FUN_00422150();
    *param_2 = *(undefined4 *)(*(int *)(iVar2 + 0x1c) + 0x88);
  }
  return;
}

