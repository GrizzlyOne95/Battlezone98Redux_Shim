
void FUN_006ae6f0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int *local_8;
  
  FUN_006c91a0(local_c);
  while( true ) {
    uVar2 = FUN_006c91c0(local_14);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    FUN_00438c10(local_10,0);
    FUN_006ae810(*(int *)*local_8 + 1);
    puVar3 = (undefined4 *)FUN_0042da60();
    *(undefined4 *)(*local_8 + 4 + *(int *)*local_8 * 4) = *puVar3;
    *(int *)*local_8 = *(int *)*local_8 + 1;
  }
  return;
}

