
bool FUN_0045d4f0(void)

{
  char cVar1;
  bool local_5;
  
  local_5 = true;
  FUN_006a31e0();
  cVar1 = FUN_00571c40();
  if (cVar1 == '\0') {
    cVar1 = (**(code **)(*DAT_00915694 + 8))();
    local_5 = cVar1 != '\0';
  }
  return local_5;
}

