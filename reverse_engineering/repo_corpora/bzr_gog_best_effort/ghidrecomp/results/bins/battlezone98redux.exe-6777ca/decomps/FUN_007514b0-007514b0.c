
void FUN_007514b0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_24 [16];
  undefined1 local_14 [8];
  int *local_c;
  
  FUN_005d4930();
  cVar1 = FUN_0073a900();
  if (cVar1 != '\0') {
    local_c = (int *)FUN_006aa1b0();
    uVar2 = (**(code **)(*local_c + 8))(local_14);
    FUN_0073a6e0(uVar2);
    FUN_00578640(local_24,0);
    FUN_00740a90(1);
    FUN_007476a0();
  }
  return;
}

