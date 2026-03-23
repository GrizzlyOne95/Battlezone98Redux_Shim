
/* WARNING: Type propagation algorithm not settling */

void __thiscall FUN_006b1ff0(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c [2];
  undefined2 local_14;
  undefined2 local_12;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20 = param_1;
  if ((param_3 == 1) || (param_3 == 5)) {
    local_1c[0] = FUN_006b20f0(param_1 + 0xc,0,0);
    if (local_1c[0] == 0) {
      local_1c[1] = 0x25a207b9;
      local_14 = 0xddf3;
      local_12 = 0x4660;
      local_10 = 0x8e;
      local_f = 0xe9;
      local_e = 0x76;
      local_d = 0xe5;
      local_c = 0x8c;
      local_b = 0x74;
      local_a = 6;
      local_9 = 0x3e;
      local_28 = 0;
      iVar1 = WSAIoctl(*param_2,0xc8000006,local_1c + 1,0x10,local_1c,4,&local_28,0,0);
      if (iVar1 != 0) {
        local_1c[0] = local_20;
      }
      FUN_006b2110(local_20 + 0xc,local_1c[0]);
    }
    if (local_1c[0] == local_20) {
      local_24 = 0;
    }
    else {
      local_24 = local_1c[0];
    }
  }
  FUN_0083e885();
  return;
}

