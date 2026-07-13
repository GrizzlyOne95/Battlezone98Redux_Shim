
char __thiscall FUN_005b4b80(int param_1,undefined4 param_2)

{
  char cVar1;
  char local_10;
  char local_5;
  
  cVar1 = FUN_004cf640(param_2,param_1 + 0x3c,4,"RecyclerFriend::fCraft",param_1);
  if (cVar1 != '\0') {
    cVar1 = FUN_0045c370(param_2,param_1 + 0x40,4);
    if (cVar1 != '\0') {
      cVar1 = FUN_004ce910(param_2,param_1 + 0x44,4);
      if (cVar1 != '\0') {
        cVar1 = FUN_004ceb10(param_2,param_1 + 0x48,4);
        if (cVar1 != '\0') {
          cVar1 = FUN_004ceb10(param_2,param_1 + 0x4c,4);
          if (cVar1 != '\0') {
            local_10 = '\x01';
            goto LAB_005b4c2e;
          }
        }
      }
    }
  }
  local_10 = '\0';
LAB_005b4c2e:
  local_5 = local_10;
  if (local_10 != '\0') {
    local_5 = FUN_005b3370(param_2);
  }
  return local_5;
}

