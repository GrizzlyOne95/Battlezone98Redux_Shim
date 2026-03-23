
void FUN_007fc8d0(uint param_1)

{
  allocator<char> *paVar1;
  byte *pbVar2;
  char *pcVar3;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [10];
  char local_e;
  char local_d;
  char local_c;
  char local_b;
  char local_a;
  char local_9;
  char local_8;
  char local_7;
  char local_6;
  byte local_5;
  
  if (0x10ffff < param_1) {
    FUN_007fad40(param_1);
  }
  if (param_1 < 0x80) {
    local_5 = (byte)param_1;
    pbVar2 = &local_5;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_18,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pbVar2);
  }
  else if (param_1 < 0x800) {
    local_6 = (char)(param_1 >> 6) + -0x40;
    pcVar3 = &local_6;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_1c,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
    local_7 = ((byte)param_1 & 0x3f) + 0x80;
    pcVar3 = &local_7;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_20,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
  }
  else if (param_1 < 0x10000) {
    local_8 = (char)(param_1 >> 0xc) + -0x20;
    pcVar3 = &local_8;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_24,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
    local_9 = ((byte)(param_1 >> 6) & 0x3f) + 0x80;
    pcVar3 = &local_9;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_28,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
    local_a = ((byte)param_1 & 0x3f) + 0x80;
    pcVar3 = &local_a;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_2c,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
  }
  else {
    local_b = (char)(param_1 >> 0x12) + -0x10;
    pcVar3 = &local_b;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_30,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
    local_c = ((byte)(param_1 >> 0xc) & 0x3f) + 0x80;
    pcVar3 = &local_c;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_34,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
    local_d = ((byte)(param_1 >> 6) & 0x3f) + 0x80;
    pcVar3 = &local_d;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_38,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
    local_e = ((byte)param_1 & 0x3f) + 0x80;
    pcVar3 = &local_e;
    paVar1 = (allocator<char> *)FUN_007fcb30(local_3c,0);
    std::allocator<char>::allocator<char>(paVar1);
    FUN_007fcb00(pcVar3);
  }
  return;
}

