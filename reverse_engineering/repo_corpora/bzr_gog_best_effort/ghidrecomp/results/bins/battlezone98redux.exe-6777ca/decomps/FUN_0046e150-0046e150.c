
void FUN_0046e150(void)

{
  char cVar1;
  int *piVar2;
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  while (cVar1 = FUN_0041fc90(), cVar1 == '\0') {
    FID_conflict_begin(local_14);
    piVar2 = (int *)FUN_00421ec0();
    local_c = *piVar2;
    local_8 = local_c;
    if (local_c == 0) {
      local_10 = 0;
    }
    else {
      local_10 = FUN_0046e1b0(1);
    }
  }
  return;
}

