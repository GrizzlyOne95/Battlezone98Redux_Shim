
/* Library Function - Single Match
    _imaxabs
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2017 Debug, Visual Studio 2019 Debug */

undefined8 __cdecl imaxabs(int param_1,int param_2)

{
  int local_c;
  int local_8;
  
  if ((param_2 < 1) && (param_2 < 0)) {
    local_c = -param_1;
    local_8 = -(param_2 + (uint)(param_1 != 0));
  }
  else {
    local_c = param_1;
    local_8 = param_2;
  }
  return CONCAT44(local_8,local_c);
}

