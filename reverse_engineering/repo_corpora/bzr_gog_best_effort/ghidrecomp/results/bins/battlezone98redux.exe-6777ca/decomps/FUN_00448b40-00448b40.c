
bool FUN_00448b40(int param_1,uint param_2)

{
  byte *pbVar1;
  byte bVar2;
  
  LOCK();
  pbVar1 = (byte *)(param_1 + ((int)param_2 >> 3));
  bVar2 = *pbVar1;
  *pbVar1 = *pbVar1 | '\x01' << (param_2 & 7);
  UNLOCK();
  return (bVar2 >> (param_2 & 7) & 1) != 0;
}

