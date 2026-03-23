
void FUN_007c5490(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00420260(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    puVar3 = &stack0x00000004;
    FUN_00422150(puVar3);
    FUN_007c5510(puVar3);
    FUN_004305b0(local_c,0);
  }
  return;
}

