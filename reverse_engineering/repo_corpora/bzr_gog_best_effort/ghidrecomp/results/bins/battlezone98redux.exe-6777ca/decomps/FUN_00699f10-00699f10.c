
undefined4 FUN_00699f10(int param_1,int *param_2,int param_3,char *param_4,int *param_5)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  void *pvVar4;
  undefined4 uVar5;
  int local_14;
  char *local_10;
  size_t local_c;
  char local_5;
  
  bVar3 = false;
  bVar2 = false;
  local_c = 1;
  local_14 = 1;
  while (!bVar2) {
    local_5 = *(char *)(param_1 + *param_2);
    *param_2 = *param_2 + 1;
    if (param_3 < *param_2) {
      local_5 = -1;
      bVar2 = true;
    }
    else {
      *(char *)(*param_5 + -1 + local_c) = local_5;
      local_c = local_c + 1;
      pvVar4 = realloc((void *)*param_5,local_c);
      *param_5 = (int)pvVar4;
      if (bVar3) {
        if (param_4[local_14] == local_5) {
          local_14 = local_14 + 1;
          if (param_4[local_14] == '\0') {
            bVar2 = true;
            local_10 = param_4;
            do {
              cVar1 = *local_10;
              local_10 = local_10 + 1;
            } while (cVar1 != '\0');
            local_c = local_c - (int)(local_10 + (1 - (int)(param_4 + 1)));
          }
        }
        else {
          bVar3 = false;
        }
      }
      if ((local_5 == *param_4) && (bVar3 = true, param_4[1] == '\0')) {
        bVar2 = true;
        local_c = local_c - 2;
      }
    }
  }
  if (local_5 == -1) {
    uVar5 = 0xffffffff;
  }
  else {
    *(undefined1 *)(*param_5 + local_c) = 0;
    uVar5 = 0;
  }
  return uVar5;
}

