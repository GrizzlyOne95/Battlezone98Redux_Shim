
void FUN_00572650(void)

{
  undefined2 uVar1;
  char cVar2;
  int local_c;
  
  local_c = FUN_0056f950();
  while (local_c != 0) {
    uVar1 = *(undefined2 *)(local_c + 0x28);
    if (*(char *)(local_c + 0x8e) == '\0') {
      cVar2 = FUN_0056fc40(uVar1);
      if (cVar2 != '\0') {
        FUN_004b7800(uVar1);
      }
      FUN_004b78a0(uVar1);
    }
    local_c = FUN_00577ad0(uVar1);
  }
  return;
}

