
void FUN_00687d80(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  FID_conflict_begin(local_c);
  while( true ) {
    cVar1 = FUN_00420f10(local_c);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_0042de50();
    FUN_00688110(*puVar2);
    FUN_0042da80();
  }
  FUN_00428a90();
  return;
}

