
undefined4 __thiscall
FUN_00705c60(undefined4 param_1,undefined4 param_2,undefined4 param_3,char param_4,char param_5)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = FUN_006ba430(param_3,param_1);
  cVar1 = FUN_006ba0d0(iVar3);
  if ((cVar1 != '\0') && (bVar2 = FUN_006ba470(param_3), 0x7d < bVar2)) {
    make_error_code(param_2,8);
    return param_2;
  }
  cVar1 = FUN_006ba3a0(param_3);
  if ((cVar1 != '\0') &&
     ((cVar1 = FUN_0044bb90(), cVar1 == '\0' || (cVar1 = FUN_006ba0d0(iVar3), cVar1 != '\0')))) {
    make_error_code(param_2,9);
    return param_2;
  }
  cVar1 = FUN_006ba3d0(param_3);
  if ((cVar1 != '\0') || (cVar1 = FUN_006ba400(param_3), cVar1 != '\0')) {
    make_error_code(param_2,9);
    return param_2;
  }
  cVar1 = FUN_006ba060(iVar3);
  if (cVar1 != '\0') {
    make_error_code(param_2,7);
    return param_2;
  }
  cVar1 = FUN_006ba0a0(iVar3);
  if (cVar1 != '\0') {
    make_error_code(param_2,7);
    return param_2;
  }
  cVar1 = FUN_006ba0d0(iVar3);
  if ((cVar1 != '\0') && (cVar1 = FUN_006ba370(param_3), cVar1 == '\0')) {
    make_error_code(param_2,10);
    return param_2;
  }
  if ((param_5 != '\0') && (iVar3 == 0)) {
    make_error_code(param_2,0xb);
    return param_2;
  }
  if ((param_5 == '\0') && ((cVar1 = FUN_006ba0d0(iVar3), cVar1 == '\0' && (iVar3 != 0)))) {
    make_error_code(param_2,0xb);
    return param_2;
  }
  if ((param_4 != '\0') && (cVar1 = FUN_006ba440(param_3), cVar1 == '\0')) {
    make_error_code(param_2,0xc);
    return param_2;
  }
  if ((param_4 == '\0') && (cVar1 = FUN_006ba440(param_3), cVar1 != '\0')) {
    make_error_code(param_2,0xd);
    return param_2;
  }
  FUN_006ab750();
  return param_2;
}

