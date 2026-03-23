
void FUN_005060f0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined1 *local_49c;
  short local_498;
  int local_494;
  char local_48d;
  undefined1 local_48c;
  undefined1 local_48b;
  undefined1 local_48a [1150];
  undefined1 local_c [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_498 = FUN_0082c1fd(param_1,1,0);
  iVar2 = FUN_005771b0(local_498);
  if ((local_498 == 0) || (iVar2 != 0)) {
    local_48c = 0x23;
    puVar3 = (undefined1 *)FUN_0082d377(param_1,2,0);
    local_48b = *puVar3;
    local_49c = local_48a;
    iVar4 = FUN_0082c8f6(param_1);
    for (local_494 = 3; local_494 <= iVar4; local_494 = local_494 + 1) {
      puVar3 = local_49c;
      cVar1 = FUN_00505ea0(&local_49c,local_c,param_1,local_494,iVar4,local_49c);
      if (cVar1 == '\0') {
        FUN_007d6c70("Lua Send packet full at arg %d\n",local_494);
        local_49c = puVar3;
        break;
      }
    }
    local_48d = 0;
    if (iVar2 == 0) {
      local_48d = FUN_00575890(&local_48c,(int)local_49c - (int)&local_48c,1,1);
    }
    else {
      local_48d = FUN_005784c0(&local_48c,(int)local_49c - (int)&local_48c,1);
    }
    FUN_0082cbf5(param_1,local_48d != '\0');
  }
  else {
    FUN_0082cbf5(param_1,0);
  }
  FUN_0083e885();
  return;
}

