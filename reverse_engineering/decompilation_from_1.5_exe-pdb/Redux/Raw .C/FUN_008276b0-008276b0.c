
void FUN_008276b0(char *param_1,int param_2,FILE *param_3)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  char *local_110;
  char *local_10c;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  bVar2 = false;
  bVar1 = true;
  do {
    pcVar3 = fgets(local_108,param_2,param_3);
    if (pcVar3 == (char *)0x0) goto LAB_0082789d;
    local_10c = param_1;
    for (local_110 = local_108; *local_110 != '\0'; local_110 = local_110 + 1) {
      if (*local_110 == '\'') {
        bVar1 = !bVar1;
      }
      if ((*local_110 == '\n') || (*local_110 == '#')) {
        *local_110 = '\0';
        break;
      }
      if (bVar2) {
        if (bVar1) {
          iVar4 = tolower((int)*local_110);
          *local_10c = (char)iVar4;
          local_10c = local_10c + 1;
        }
        else {
          *local_10c = *local_110;
          local_10c = local_10c + 1;
        }
      }
      else {
        iVar4 = isspace((int)*local_110);
        if (iVar4 == 0) {
          if (bVar1) {
            iVar4 = tolower((int)*local_110);
            *local_10c = (char)iVar4;
          }
          else {
            *local_10c = *local_110;
          }
          local_10c = local_10c + 1;
          bVar2 = true;
        }
      }
    }
  } while (!bVar2);
  *local_10c = '\0';
LAB_0082789d:
  FUN_0083e885();
  return;
}

