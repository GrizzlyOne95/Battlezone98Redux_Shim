
uint FUN_00625160(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint *puVar2;
  byte bVar3;
  uint local_8;
  
  puVar2 = (uint *)((param_2 >> 3) + param_1 & 0xfffffffc);
  iVar1 = param_2 + (param_1 - (int)puVar2) * 8;
  bVar3 = (byte)iVar1;
  local_8 = *puVar2 >> (bVar3 & 0x1f);
  if (0x1f < (uint)(iVar1 + param_3)) {
    local_8 = puVar2[1] << (0x20 - bVar3 & 0x1f) | local_8;
  }
  return (1 << ((byte)param_3 & 0x1f)) - 1U & local_8;
}

