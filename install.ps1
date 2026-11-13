Write-Output ">> Installing dependencies"
Start-Sleep -Seconds 1
winget install chezmoi
winget install starship
Write-Output ">> Copying chezmoi config"
Start-Sleep -Seconds 1
cp -r chezmoi ~/.local/share/chezmoi
Write-Output ">> Applying chezmoi theme"
Start-Sleep -Seconds 1
. "$PSScriptRoot\update-theme.ps1"
