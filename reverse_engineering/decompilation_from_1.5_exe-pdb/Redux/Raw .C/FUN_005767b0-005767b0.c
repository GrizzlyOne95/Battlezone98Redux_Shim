
void FUN_005767b0(void)

{
  char cVar1;
  int iVar2;
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  while (cVar1 = FUN_004202c0(), cVar1 == '\0') {
    FUN_00420260(local_14);
    iVar2 = FUN_00422150();
    local_c = *(int *)(iVar2 + 0x10);
    local_8 = local_c;
    if (local_c == 0) {
      local_10 = 0;
    }
    else {
      local_10 = FUN_005715a0(1);
    }
  }
  FUN_00429ce0();
  return;
}

