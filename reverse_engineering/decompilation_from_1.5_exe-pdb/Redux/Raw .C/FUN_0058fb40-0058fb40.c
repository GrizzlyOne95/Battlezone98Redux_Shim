
void __thiscall FUN_0058fb40(undefined4 param_1,int param_2,undefined4 param_3)

{
  ushort uVar1;
  
  DAT_008e8e04 = param_2;
  DAT_008e8e0c = param_3;
  FUN_005e0bc0(param_3,param_1);
  uVar1 = FUN_00462590();
  DAT_00918158 = ~uVar1;
  DAT_00918174 = 0x3f800000;
  DAT_00918178 = 0x40000000;
  DAT_0091817c = 0x41200000;
  DAT_0091818c = 0x47c34f80;
  DAT_00918184 = 0x41200000;
  DAT_00918188 = 0x47c34f80;
  if (DAT_008e8e04 == 1) {
    DAT_00918180 = 0x47c34f80;
  }
  else if (DAT_008e8e04 == 2) {
    DAT_00918180 = 0x47c34f80;
  }
  else if (DAT_008e8e04 == 3) {
    DAT_00918180 = 0x3f8ccccd;
  }
  else {
    DAT_00918180 = DAT_008e8e08;
  }
  return;
}

