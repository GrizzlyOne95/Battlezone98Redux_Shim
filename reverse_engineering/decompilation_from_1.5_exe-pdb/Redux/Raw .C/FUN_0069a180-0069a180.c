
void FUN_0069a180(int *param_1,code *param_2)

{
  void *_Memory;
  int iVar1;
  int local_10;
  undefined1 *local_c;
  int local_8;
  
  local_8 = 0;
  local_10 = 0;
  local_c = malloc(1);
  *local_c = 0;
  for (; *(char *)(*param_1 + local_8) != '\0'; local_8 = local_8 + 1) {
    iVar1 = (*param_2)(*(undefined1 *)(*param_1 + local_8));
    if (iVar1 == 1) {
      FUN_0069a090(&local_c,&local_10,*(undefined1 *)(*param_1 + local_8));
    }
    else if (iVar1 == 2) {
      if (*(char *)(*param_1 + local_8) == '\"') {
        FUN_0069a120(&local_c,&local_10,*(undefined1 *)(*param_1 + local_8));
        while ((local_8 = local_8 + 1, *(char *)(*param_1 + local_8) != '\0' &&
               (*(char *)(*param_1 + local_8) != '\"'))) {
          FUN_0069a120(&local_c,&local_10,*(undefined1 *)(*param_1 + local_8));
        }
        if (*(char *)(*param_1 + local_8) == '\"') {
          FUN_0069a120(&local_c,&local_10,*(undefined1 *)(*param_1 + local_8));
        }
      }
      else {
        FUN_0069a090(&local_c,&local_10,0x20);
        FUN_0069a090(&local_c,&local_10,*(undefined1 *)(*param_1 + local_8));
        FUN_0069a090(&local_c,&local_10,0x20);
      }
    }
    else {
      FUN_0069a090(&local_c,&local_10,0x20);
    }
  }
  local_c = realloc(local_c,local_10 + 1);
  local_c[local_10] = 0;
  _Memory = (void *)*param_1;
  *param_1 = (int)local_c;
  free(_Memory);
  return;
}

