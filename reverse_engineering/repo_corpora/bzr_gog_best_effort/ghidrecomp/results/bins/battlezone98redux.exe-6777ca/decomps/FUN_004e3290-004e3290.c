
bool FUN_004e3290(int param_1,char *param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  bool bVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [8];
  undefined4 *local_c;
  int *local_8;
  
  if ((param_2 == (char *)0x0) || (iVar1 = _strnicmp(param_2,"null",4), iVar1 == 0)) {
    if ((param_3 == 0) && (param_4 == 0)) {
      *(undefined4 *)(param_1 + 100) = 0;
      uVar2 = FUN_004e3210(0,0);
      *(undefined4 *)(param_1 + 0x70) = uVar2;
    }
    bVar4 = false;
  }
  else {
    local_8 = (int *)(param_1 + 0x68);
    if (*local_8 == 0) {
      *(undefined4 *)(param_1 + 0x6c) = 10;
      pvVar3 = malloc(*(int *)(param_1 + 0x6c) << 4);
      local_8[3] = (int)pvVar3;
    }
    else if (*local_8 == *(int *)(param_1 + 0x6c)) {
      *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 10;
      pvVar3 = realloc(*(void **)(param_1 + 0x74),*(int *)(param_1 + 0x6c) << 4);
      local_8[3] = (int)pvVar3;
    }
    local_c = (undefined4 *)(*local_8 * 0x10 + local_8[3]);
    *local_8 = *local_8 + 1;
    uVar2 = FUN_004e3210(param_3,param_4);
    *local_c = uVar2;
    FUN_004e3120(param_2,&local_1c,local_14);
    uVar2 = FUN_004e3810(local_1c,local_18);
    local_c[1] = uVar2;
    if (local_c[1] == 0) {
      FUN_007d6370("Missing geometry \"%.8s\"\n",&local_1c);
    }
    local_c[2] = local_1c;
    local_c[3] = local_18;
    if ((param_3 == 0) && (param_4 == 0)) {
      *(undefined4 *)(param_1 + 100) = local_c[1];
      uVar2 = FUN_004e3210(0,0);
      *(undefined4 *)(param_1 + 0x70) = uVar2;
    }
    bVar4 = local_c[1] != 0;
  }
  return bVar4;
}

