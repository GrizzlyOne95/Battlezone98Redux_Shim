
uint FUN_006ba750(uint param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = FUN_006b9e90();
  if (cVar1 == '\0') {
    uVar2 = param_1 << ((byte)(param_2 << 3) & 0x1f) |
            param_1 >> (('\x04' - (char)param_2) * '\b' & 0x1fU);
  }
  else {
    uVar2 = param_1 >> ((byte)(param_2 << 3) & 0x1f) |
            param_1 << (('\x04' - (char)param_2) * '\b' & 0x1fU);
  }
  return uVar2;
}

