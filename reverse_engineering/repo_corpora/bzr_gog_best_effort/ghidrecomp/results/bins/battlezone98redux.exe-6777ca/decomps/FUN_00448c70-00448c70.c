
void __thiscall FUN_00448c70(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  uint local_c;
  
  while( true ) {
    bVar3 = (*param_2 & 0x80000000) != 0;
    if (bVar3) {
      local_c = *param_2 + 1;
    }
    else {
      local_c = *param_2 | 0x80000000;
    }
    uVar1 = *param_2;
    LOCK();
    uVar2 = *param_1;
    if (uVar1 == uVar2) {
      *param_1 = local_c;
      uVar2 = uVar1;
    }
    UNLOCK();
    if (uVar2 == *param_2) break;
    *param_2 = uVar2;
  }
  if (bVar3) {
    *param_2 = local_c;
  }
  return;
}

