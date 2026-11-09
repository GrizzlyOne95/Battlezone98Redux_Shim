# Minimal scenario: let the lobby hook do the work; just wait for the mission.
param([int]$PlaySeconds = 20)
Invoke-CRFlowStep 'play' { Start-Sleep -Seconds $PlaySeconds; 'ok' }
