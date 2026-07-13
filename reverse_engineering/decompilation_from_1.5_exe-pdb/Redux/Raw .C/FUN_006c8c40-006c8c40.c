
undefined4 FUN_006c8c40(void)

{
  int iVar1;
  undefined4 local_c;
  
  iVar1 = FUN_006cd800();
  if (iVar1 == 0) {
    local_c = 0;
  }
  else {
    local_c = *(undefined4 *)(iVar1 + 4);
  }
  return local_c;
}

