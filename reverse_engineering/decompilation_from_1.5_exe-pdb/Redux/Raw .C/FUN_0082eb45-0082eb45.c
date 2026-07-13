
bool FUN_0082eb45(byte *param_1,double *param_2)

{
  byte bVar1;
  ulong uVar2;
  int iVar3;
  bool bVar4;
  double dVar5;
  byte *local_8;
  
  dVar5 = strtod((char *)param_1,(char **)&local_8);
  *param_2 = dVar5;
  if (local_8 == param_1) {
    bVar4 = false;
  }
  else {
    if ((*local_8 == 0x78) || (*local_8 == 0x58)) {
      uVar2 = strtoul((char *)param_1,(char **)&local_8,0x10);
      *param_2 = (double)(int)uVar2 + (double)(&DAT_008a2fd0)[-((int)uVar2 >> 0x1f)];
    }
    bVar1 = *local_8;
    if (bVar1 == 0) {
      bVar4 = true;
    }
    else {
      while (iVar3 = isspace((uint)bVar1), iVar3 != 0) {
        local_8 = local_8 + 1;
        bVar1 = *local_8;
      }
      bVar4 = *local_8 == 0;
    }
  }
  return bVar4;
}

