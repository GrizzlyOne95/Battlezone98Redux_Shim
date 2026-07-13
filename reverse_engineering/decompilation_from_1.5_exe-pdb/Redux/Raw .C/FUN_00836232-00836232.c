
void FUN_00836232(undefined4 param_1,int param_2)

{
  char cVar1;
  char *_Str;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int local_124;
  uint local_120;
  int local_11c;
  int local_118;
  uint local_114;
  undefined4 local_110;
  undefined4 local_10c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_11c = FUN_0082ba59(param_1,1,&local_120);
  _Str = (char *)FUN_0082ba59(param_1,2,&local_124);
  uVar2 = FUN_0082c1fd(param_1,3,1,local_120);
  iVar3 = FUN_00835ff6(uVar2);
  uVar6 = iVar3 - 1;
  if ((int)uVar6 < 0) {
    uVar6 = 0;
  }
  else if (local_120 < uVar6) {
    uVar6 = local_120;
  }
  if ((param_2 == 0) ||
     ((iVar3 = FUN_0082d2e8(param_1,4), iVar3 == 0 &&
      (pcVar4 = strpbrk(_Str,"^$*+?.([%-"), pcVar4 != (char *)0x0)))) {
    cVar1 = *_Str;
    if (cVar1 == '^') {
      _Str = _Str + 1;
    }
    local_118 = local_11c;
    local_114 = local_11c + local_120;
    local_110 = param_1;
    uVar6 = uVar6 + local_11c;
    do {
      local_10c = 0;
      iVar3 = FUN_00835b72(&local_118,uVar6,_Str);
      if (iVar3 != 0) {
        if (param_2 == 0) {
          FUN_0083600d(&local_118,uVar6,iVar3);
        }
        else {
          FUN_0082ccca(param_1,(uVar6 - local_11c) + 1);
          FUN_0082ccca(param_1,iVar3 - local_11c);
          FUN_0083600d(&local_118,0,0);
        }
        goto LAB_008363ef;
      }
    } while ((uVar6 < local_114) && (uVar6 = uVar6 + 1, cVar1 != '^'));
  }
  else {
    iVar3 = local_11c;
    iVar5 = FUN_00835a7d(uVar6 + local_11c,local_120 - uVar6,_Str,local_124);
    if (iVar5 != 0) {
      FUN_0082ccca(param_1,(iVar5 - iVar3) + 1);
      FUN_0082ccca(param_1,local_124 + (iVar5 - iVar3));
      goto LAB_008363ef;
    }
  }
  FUN_0082cd45(param_1);
LAB_008363ef:
  FUN_0083e885();
  return;
}

