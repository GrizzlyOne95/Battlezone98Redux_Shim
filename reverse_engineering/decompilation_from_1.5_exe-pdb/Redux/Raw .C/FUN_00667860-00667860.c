
undefined1 FUN_00667860(byte *param_1)

{
  int iVar1;
  undefined1 local_8;
  
  iVar1 = isalpha((uint)*param_1);
  if ((iVar1 == 0) || (param_1[1] != 0x3a)) {
    if ((*param_1 == 0x2f) || (*param_1 == 0x5c)) {
      local_8 = 1;
    }
    else {
      local_8 = 0;
    }
  }
  else {
    local_8 = 1;
  }
  return local_8;
}

