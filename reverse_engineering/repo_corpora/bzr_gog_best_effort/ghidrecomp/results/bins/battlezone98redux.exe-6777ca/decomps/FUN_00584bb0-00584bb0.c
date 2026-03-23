
void FUN_00584bb0(uint param_1,int param_2)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_20 [4];
  int local_1c;
  undefined1 local_18 [4];
  uint local_14;
  undefined1 local_10 [4];
  uint local_c;
  uint local_8;
  
  local_8 = param_1;
  local_14 = param_1 + param_2;
  while (uVar1 = local_8, local_8 < local_14) {
    local_c = local_8;
    local_8 = local_8 + 2;
    FUN_004bcc60(&stack0x0000000c,uVar1);
    FUN_00585840(local_10,local_18);
    uVar3 = FID_conflict_begin(local_20);
    cVar2 = FUN_00420f10(uVar3);
    if (cVar2 != '\0') {
      iVar4 = FUN_00422150();
      local_1c = *(int *)(iVar4 + 4);
      *(undefined4 *)(local_1c + 0x78) = 0;
    }
  }
  return;
}

