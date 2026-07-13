/*
 * Entry: 005b7ed8
 * Name: luaO_str2d
 * Namespace: Global
 * Signature: int luaO_str2d(char * param_1, double * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaO_str2d(char *param_1,double *param_2)

{
  byte bVar1;
  uint uVar2;
  ulong uVar3;
  int iVar4;
  double dVar5;
  byte *local_8;
  
  dVar5 = strtod(param_1,(char **)&local_8);
  *param_2 = dVar5;
  if (local_8 == (byte *)param_1) {
    uVar2 = 0;
  }
  else {
    if ((*local_8 == 0x78) || (*local_8 == 0x58)) {
      uVar3 = strtoul(param_1,(char **)&local_8,0x10);
      dVar5 = (double)(int)uVar3;
      if ((int)uVar3 < 0) {
        dVar5 = dVar5 + 4294967296.0;
      }
      *param_2 = dVar5;
    }
    bVar1 = *local_8;
    if (bVar1 == 0) {
      uVar2 = 1;
    }
    else {
      while (iVar4 = isspace((uint)bVar1), iVar4 != 0) {
        local_8 = local_8 + 1;
        bVar1 = *local_8;
      }
      uVar2 = (uint)(*local_8 == 0);
    }
  }
  return uVar2;
}
