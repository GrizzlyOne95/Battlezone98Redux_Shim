
int FUN_00460330(void)

{
  undefined4 *puVar1;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  FUN_00430590();
  local_c = local_8;
  puVar1 = (undefined4 *)FID_conflict_begin(local_14);
  local_10 = *puVar1;
  puVar1 = (undefined4 *)FUN_004613b0(local_18,local_10,&local_c);
  *(undefined4 *)(local_8 + 0x14) = *puVar1;
  *(undefined1 *)(local_8 + 0xc) = 0;
  return local_8;
}

