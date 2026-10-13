# Focused four-player qualification; regenerate the mission's override
# (misn05-coop / misn06-coop, New-CRFlowOverride.ps1) from current CR/EXU
# before running. Each case prepares four isolated clients and closes them.
param([string]$BZRCoopRoot = 'C:\BZRCoop', [string]$Only = '', [string]$OpenShimRepo = '',
      [ValidateSet('misn05', 'misn06')][string]$Mission = 'misn05')
$cases = if ($Mission -eq 'misn06') {
    @(
        'misn06 win Override=misn06-coop',
        'misn06 lose Override=misn06-coop Destroyed=recycler',
        'misn06 host-leaves Override=misn06-coop'
    )
} else {
    @(
        'misn05 four-services Override=misn05-coop',
        'misn05 win Override=misn05-coop',
        'misn05 win Override=misn05-coop GuestClient=2',
        'misn05 win Override=misn05-coop GuestClient=3',
        'misn05 win Override=misn05-coop Skipper=host',
        'misn05 win Override=misn05-coop Skipper=none',
        'misn05 lose Override=misn05-coop Destroyed=factory',
        'misn05 lose Override=misn05-coop Destroyed=recycler',
        'misn05 host-leaves Override=misn05-coop'
    )
}
& "$PSScriptRoot\Run-BZRCoopSuite.ps1" -Clients 4 -MaxNetworkLogging -MuteClients -OpenShimRepo $OpenShimRepo -StopOnFailure -Cases $cases -Only $Only -BZRCoopRoot $BZRCoopRoot
exit $LASTEXITCODE