
int FUN_005d31c0(void)

{
  int iVar1;
  undefined1 local_14 [4];
  int *local_10;
  int local_c;
  undefined4 local_8;
  
  iVar1 = FUN_00416410();
  if (iVar1 == 0) {
    local_c = 0;
  }
  else {
    FUN_00424640(&local_8);
    local_10 = (int *)FUN_004237d0();
    local_c = *local_10;
    FUN_0045e7a0(local_14,local_8);
    *(undefined1 *)(local_c + 0x18) = 0;
  }
  return local_c;
}

