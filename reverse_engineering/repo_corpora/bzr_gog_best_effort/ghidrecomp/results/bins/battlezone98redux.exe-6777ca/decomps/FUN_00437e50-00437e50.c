
void __fastcall FUN_00437e50(int param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *local_18;
  int *local_10;
  int *local_c;
  int local_8;
  
  if (*(char *)(param_1 + 0x40) != '\0') {
    local_8 = param_1;
    iVar2 = FUN_0061a050();
    if (iVar2 == 0) {
      cVar1 = FUN_0042d8f0();
      if (cVar1 == '\0') {
        piVar3 = (int *)FUN_00438b60();
        FUN_00437fc0(*(undefined4 *)(*piVar3 + 4));
      }
      local_c = operator_new(8);
      if (local_c == (int *)0x0) {
        local_18 = (int *)0x0;
      }
      else {
        memset(local_c,0,8);
        local_18 = local_c;
      }
      local_10 = local_18;
      *local_18 = local_8 + 0x40;
      local_18[1] = *(int *)(local_8 + 0x30);
      *(int *)(local_8 + 0x30) = *(int *)(local_8 + 0x30) + 1;
      FUN_00438b80(&local_10);
    }
  }
  return;
}

