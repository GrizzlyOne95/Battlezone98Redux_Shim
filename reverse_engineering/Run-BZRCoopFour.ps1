# Focused four-player qualification; regenerate the mission's override
# (misn05-coop / misn06-coop, New-CRFlowOverride.ps1) from current CR/EXU
# before running. Each case prepares four isolated clients and closes them.
param([string]$BZRCoopRoot = 'C:\BZRCoop', [string]$Only = '', [string]$OpenShimRepo = '',
      [ValidateSet('misn05', 'misn06', 'misn07', 'misn08', 'misn09')][string]$Mission = 'misn05')
$cases = if ($Mission -eq 'misn07') {
    @(
        'misn07 coop-smoke Override=misn07-coop',
        'misn07 host-leaves Override=misn07-coop'
    )
} elseif ($Mission -eq 'misn09') {
    @(
        'misn09 coop-smoke Override=misn09-coop',
        # Test assists: convoy launch + scaling, Prescott's platoon + victory, team-5 AIP.
        'misn09 assists Override=misn09-coop',
        'misn09 host-leaves Override=misn09-coop'
    )
} elseif ($Mission -eq 'misn08') {
    @(
        # Aip=1 also forces the story beat that gives team 5 its AIP and watches team 5.
        'misn08 coop-smoke Override=misn08-coop Aip=1',
        'misn08 host-leaves Override=misn08-coop'
    )
} elseif ($Mission -eq 'misn06') {
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