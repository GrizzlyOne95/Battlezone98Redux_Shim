
undefined4 FUN_008249a0(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_c [4];
  undefined4 local_8;
  
  local_8 = 0;
  if ((DAT_02cc1b44 == 0) && (iVar1 = FUN_00824960(), iVar1 == 0)) {
    return local_8;
  }
  if ((param_3 & 2) == 0) {
    if ((param_3 & 4) != 0) {
      uVar2 = FUN_0082afb0(param_1,param_2,param_4,local_c,0,"1y decompression");
      local_8 = FUN_00824930(uVar2);
    }
  }
  else {
    uVar2 = FUN_0082aab0(param_1,param_2,param_4,local_c,0,"1x decompression");
    local_8 = FUN_00824930(uVar2);
  }
  return local_8;
}

