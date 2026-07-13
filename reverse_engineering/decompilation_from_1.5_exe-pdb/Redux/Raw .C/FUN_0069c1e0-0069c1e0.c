
/* WARNING: Removing unreachable block (ram,0x0069c2c0) */

void FUN_0069c1e0(char *param_1,size_t param_2,int *param_3,int *param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  void *pvVar6;
  int iVar7;
  char *local_14;
  char *local_c;
  
  bVar3 = false;
  bVar4 = false;
  bVar2 = false;
  bVar5 = false;
  pvVar6 = malloc(param_2);
  *param_3 = (int)pvVar6;
  if (*param_3 == 0) {
    FUN_00699180("Unable to allocate memory for buffer while preprocessing script",2);
  }
  local_14 = param_1;
  local_c = (char *)*param_3;
  while( true ) {
    while( true ) {
      while( true ) {
        while( true ) {
          if (local_14 < param_1 + param_2) {
            cVar1 = *local_14;
            local_14 = local_14 + 1;
          }
          else {
            cVar1 = -1;
          }
          iVar7 = FUN_006991d0(cVar1);
          if (bVar2) {
            bVar2 = false;
            if (cVar1 == '/') {
              bVar3 = true;
            }
            else if (cVar1 == '*') {
              bVar4 = true;
            }
            else {
              *local_c = '/';
              local_c = local_c + 1;
              bVar3 = false;
              bVar4 = false;
            }
          }
          if (!bVar3) break;
          if ((cVar1 == '\n') || (cVar1 == '\r')) {
            bVar3 = false;
            *local_c = cVar1;
            local_c = local_c + 1;
          }
        }
        if (!bVar4) break;
        if (bVar5) {
          if (cVar1 == '/') {
            bVar4 = false;
          }
          else {
            bVar5 = false;
          }
        }
        if (cVar1 == '*') {
          bVar5 = true;
        }
      }
      if (iVar7 != 2) break;
      if (cVar1 == '/') {
        bVar2 = true;
      }
      else {
        *local_c = cVar1;
        local_c = local_c + 1;
      }
    }
    if (iVar7 == 3) break;
    *local_c = cVar1;
    local_c = local_c + 1;
  }
  *param_4 = (int)local_c - *param_3;
  return;
}

