
int FUN_0077d5f0(double param_1,double param_2)

{
  ushort *puVar1;
  
  puVar1 = (ushort *)
           FUN_004c0fe0((int)((double)DAT_02cc50e4 * param_1),(int)((double)DAT_02cc50e4 * param_2))
  ;
  return (int)(*puVar1 & 0xf000) >> 0xc;
}

