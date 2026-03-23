
void FUN_00826c40(char *param_1,undefined4 param_2)

{
  FILE *pFVar1;
  size_t sVar2;
  undefined1 local_e38 [3604];
  undefined1 local_24;
  undefined1 local_23;
  undefined1 uStack_22;
  undefined1 uStack_21;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pFVar1 = fopen(param_1,"rb");
  if (pFVar1 == (FILE *)0x0) {
    pFVar1 = fopen(param_1,"wb");
    if (pFVar1 == (FILE *)0x0) {
      sprintf(&DAT_009467c0,"Could not create file \"%s\"",param_1);
    }
    else {
      local_24 = 0x5a;
      local_23 = 0x46;
      uStack_22 = 0x53;
      uStack_21 = 0x46;
      local_20 = 1;
      local_1c = 0x10;
      local_18 = 100;
      local_14 = 0;
      local_10 = param_2;
      local_c = 0x1c;
      memset(local_e38,0,0xe14);
      sVar2 = fwrite(&local_24,0x1c,1,pFVar1);
      if (sVar2 != 0) {
        sVar2 = fwrite(local_e38,0xe14,1,pFVar1);
        if (sVar2 != 0) {
          fclose(pFVar1);
          goto LAB_00826dd3;
        }
      }
      sprintf(&DAT_009467c0,"Error writing to file \"%s\"",param_1);
      fclose(pFVar1);
    }
  }
  else {
    fclose(pFVar1);
    sprintf(&DAT_009467c0,"File \"%s\" already exists",param_1);
  }
LAB_00826dd3:
  FUN_0083e885();
  return;
}

