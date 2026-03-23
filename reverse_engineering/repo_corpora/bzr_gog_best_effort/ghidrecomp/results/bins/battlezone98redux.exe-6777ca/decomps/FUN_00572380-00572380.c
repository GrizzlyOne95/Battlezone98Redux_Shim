
bool FUN_00572380(void)

{
  void *pvVar1;
  int iVar2;
  undefined4 local_c;
  
  pvVar1 = operator_new(0x870);
  if (pvVar1 == (void *)0x0) {
    local_c = 0;
  }
  else {
    local_c = FUN_0056fd20();
  }
  DAT_00917f48 = local_c;
  iVar2 = FUN_004b0190(&DAT_00917f58);
  return iVar2 == DAT_009180cc;
}

