
undefined4 FUN_00426c30(char *param_1)

{
  undefined4 uVar1;
  FILE *local_8;
  
  local_8 = (FILE *)0x0;
  fopen_s(&local_8,param_1,"rb");
  if (local_8 == (FILE *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    uVar1 = FUN_0042a630(local_8);
    fclose(local_8);
  }
  return uVar1;
}

