
void __thiscall FUN_00448d00(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_8;
  
  *param_2 = *param_2 & 0x7fffffff;
  *param_2 = *param_2 | 0x40000000;
  while( true ) {
    if ((*param_2 & 0x80000000) == 0) {
      local_8 = *param_2 - 1 | 0x80000000;
    }
    else {
      local_8 = *param_2;
    }
    uVar1 = *param_2;
    LOCK();
    uVar2 = *param_1;
    if (uVar1 == uVar2) {
      *param_1 = local_8 & 0xbfffffff;
      uVar2 = uVar1;
    }
    UNLOCK();
    if (uVar2 == *param_2) break;
    *param_2 = uVar2;
  }
  return;
}

