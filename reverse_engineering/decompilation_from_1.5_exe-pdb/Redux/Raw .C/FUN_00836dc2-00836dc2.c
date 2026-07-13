
void FUN_00836dc2(undefined4 param_1)

{
  undefined4 uVar1;
  uint uVar2;
  code *pcVar3;
  uint uVar4;
  bool bVar5;
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_008376b6(param_1,local_14);
  uVar2 = FUN_0082e07f(uVar1);
  pcVar3 = (code *)FUN_0082e069(uVar1);
  if ((pcVar3 == (code *)0x0) || (pcVar3 == FUN_008376eb)) {
    FUN_00837655(param_1);
    FUN_0082cced(param_1,uVar1);
    FUN_0082ce65(param_1,0xfffffffe);
    FUN_0082cf99(param_1,0xfffffffe);
  }
  else {
    FUN_0082cd08(param_1,"external hook",0xd);
  }
  bVar5 = (uVar2 & 1) != 0;
  if (bVar5) {
    local_10[0] = 99;
  }
  uVar4 = (uint)bVar5;
  if ((uVar2 & 2) != 0) {
    local_10[uVar4] = 0x72;
    uVar4 = uVar4 + 1;
  }
  if ((uVar2 & 4) != 0) {
    local_10[uVar4] = 0x6c;
    uVar4 = uVar4 + 1;
  }
  local_10[uVar4] = 0;
  FUN_0082cd77(param_1,local_10);
  uVar1 = FUN_0082e074(uVar1);
  FUN_0082ccca(param_1,uVar1);
  FUN_0083e885();
  return;
}

