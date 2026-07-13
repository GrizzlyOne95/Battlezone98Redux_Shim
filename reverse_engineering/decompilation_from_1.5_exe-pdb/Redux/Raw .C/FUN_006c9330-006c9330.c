
void FUN_006c9330(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_c [8];
  
  FUN_006cd9d0(local_c);
  while( true ) {
    uVar2 = FUN_006cd9f0(local_14);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    FUN_00438c10(&local_10,0);
    iVar3 = FUN_0042da60();
    FUN_006d8a70(iVar3 + 4);
    FUN_006cdcc0(local_10);
  }
  return;
}

