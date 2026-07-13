
undefined1 __thiscall FUN_006f7320(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 local_c;
  
  if ((*param_1 == '\0') || (*param_2 == '\0')) {
    if ((*param_1 == '\0') && (*param_2 == '\0')) {
      iVar2 = FUN_006d8ca0(param_1 + 4);
      iVar3 = FUN_006d8ca0(param_2 + 4);
      if (iVar2 == iVar3) {
        iVar2 = FUN_006ae390(param_1 + 4);
        iVar3 = FUN_006ae390(param_2 + 4);
        if (((iVar2 == iVar3) && (cVar1 = FID_conflict_operator__(param_2 + 0xc), cVar1 != '\0')) &&
           (cVar1 = FID_conflict_operator__(param_2 + 0x10), cVar1 != '\0')) {
          return 1;
        }
      }
    }
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

