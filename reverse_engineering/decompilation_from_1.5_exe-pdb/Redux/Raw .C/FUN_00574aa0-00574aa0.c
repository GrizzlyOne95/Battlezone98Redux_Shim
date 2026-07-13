
void FUN_00574aa0(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c [2];
  
  FUN_005789b0(local_c,&stack0x00000004);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    iVar3 = FUN_00422150();
    FUN_00578950(iVar3 + 8);
    local_10 = local_c[0];
    FUN_00429560(local_18,local_c[0]);
  }
  return;
}

