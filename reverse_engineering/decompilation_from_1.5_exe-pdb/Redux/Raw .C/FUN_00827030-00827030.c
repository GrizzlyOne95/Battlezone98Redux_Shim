
void FUN_00827030(char *param_1,FILE *param_2)

{
  size_t sVar1;
  undefined4 *_Memory;
  int iVar2;
  char local_24;
  char local_23;
  char cStack_22;
  char cStack_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fseek(param_2,0,0);
  sVar1 = fread(&local_24,0x1c,1,param_2);
  if (sVar1 == 0) {
    sprintf(&DAT_009467c0,"Could not read header of file \"%s\"",param_1);
  }
  else if ((((local_24 == 'Z') && (local_23 == 'F')) && (cStack_22 == 'S')) &&
          (((cStack_21 == 'F' && (local_20 == 1)) && ((local_1c == 0x10 && (local_18 == 100)))))) {
    _Memory = malloc(0x2c);
    strncpy((char *)(_Memory + 1),param_1,0x10);
    *_Memory = param_2;
    _Memory[5] = local_14 / 100 + 1;
    _Memory[6] = local_14;
    _Memory[8] = local_14;
    _Memory[7] = local_10;
    iVar2 = FUN_00826df0(_Memory,&local_24);
    if (iVar2 == 0) {
      free(_Memory);
    }
    else {
      qsort((void *)_Memory[10],_Memory[6],0x24,FUN_00827010);
    }
  }
  else {
    sprintf(&DAT_009467c0,"Invalid header in file \"%s\"",param_1);
  }
  FUN_0083e885();
  return;
}

