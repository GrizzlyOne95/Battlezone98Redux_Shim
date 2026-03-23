
void FUN_006d7640(void)

{
  char cVar1;
  int iVar2;
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  
  FUN_006bb740(local_10);
  iVar2 = FUN_00667170();
  if (iVar2 != 0) {
    FUN_006d8cc0(0x273d,0);
    cVar1 = FUN_006ab920(local_10,local_18);
    if (cVar1 == '\0') {
      FUN_006dee50(8,"socket cancel failed",local_10);
    }
    else {
      FUN_006d08b0(0x400,"socket cancel not supported");
    }
  }
  return;
}

