/*
 * Entry: 00463d19
 * Name: PlayReminder
 * Namespace: Global
 * Signature: float PlayReminder(float param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl PlayReminder(float param_1,int param_2)

{
  float fVar1;
  char *pcVar2;
  float local_8;
  
  fVar1 = Get_Time();
  if (fVar1 <= param_1) {
    return param_1;
  }
  local_8 = Get_Time();
  local_8 = local_8 + 15.0;
  switch(param_2) {
  case 1:
    pcVar2 = "tran0202.wav";
    break;
  case 2:
    pcVar2 = "tran0203.wav";
    break;
  case 3:
    pcVar2 = "tran0204.wav";
    break;
  case 4:
    pcVar2 = "tran0211.wav";
    break;
  case 5:
    pcVar2 = "tran0206.wav";
    break;
  case 6:
    pcVar2 = "misn0109.wav";
    break;
  case 7:
    pcVar2 = "tran0207.wav";
    break;
  case 8:
    AudioMessage("tran0208.wav");
    local_8 = 99999.0;
  default:
    goto switchD_00463d49_default;
  }
  AudioMessage(pcVar2);
switchD_00463d49_default:
  return local_8;
}
