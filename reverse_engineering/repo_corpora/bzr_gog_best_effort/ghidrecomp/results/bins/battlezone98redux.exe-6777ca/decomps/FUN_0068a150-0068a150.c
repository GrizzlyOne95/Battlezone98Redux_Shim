
void FUN_0068a150(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_a8 [64];
  undefined1 local_68 [12];
  float local_5c;
  undefined4 *local_58;
  undefined4 local_54 [16];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = 0;
  local_10 = 0x3f800000;
  local_c = 0;
  local_58 = (undefined4 *)FUN_0068a070();
  fVar4 = (float10)FUN_0068a130();
  local_5c = (float)fVar4;
  puVar1 = (undefined4 *)FUN_0081f490(local_a8,local_5c,*local_58,local_58[1],local_58[2]);
  puVar3 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)FUN_00440210(local_68,&local_14,local_54);
  DAT_02ceb830 = *puVar1;
  DAT_02ceb834 = puVar1[1];
  DAT_02ceb838 = puVar1[2];
  FUN_0083e885();
  return;
}

