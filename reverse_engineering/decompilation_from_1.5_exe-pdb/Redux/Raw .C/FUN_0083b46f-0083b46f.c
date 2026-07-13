
undefined4 FUN_0083b46f(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  switch(*(undefined4 *)(param_1 + 0x10)) {
  case 0x102:
    FUN_00838ffd(param_1);
    FUN_00839a51(param_1);
    return 1;
  case 0x103:
    FUN_00838ffd(param_1);
    FUN_00839934(param_1);
    FUN_00839b38(param_1,0x106,0x103,uVar1);
    break;
  default:
    FUN_0083a167(param_1);
    break;
  case 0x108:
    FUN_0083a4e0(param_1,uVar1);
    break;
  case 0x109:
    FUN_0083a68b(param_1,uVar1);
    break;
  case 0x10a:
    FUN_0083a7a5(param_1,uVar1);
    break;
  case 0x10c:
    FUN_00838ffd(param_1);
    iVar2 = FUN_0083b6c3(param_1,0x109);
    if (iVar2 == 0) {
      FUN_0083aa68(param_1);
    }
    else {
      FUN_0083a9d0();
    }
    break;
  case 0x110:
    FUN_0083b0da(param_1,uVar1);
    break;
  case 0x111:
    FUN_0083b18d(param_1);
    return 1;
  case 0x115:
    FUN_0083b6e1(param_1,uVar1);
  }
  return 0;
}

