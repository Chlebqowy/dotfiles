Write-Output ">> Installing dependencies (assumes winget)"
Start-Sleep -Seconds 1
winget install chezmoi
winget install --id Starship.Starship
Write-Output ">> Copying chezmoi config"
Start-Sleep -Seconds 1
cp -r chezmoi ~/.local/share/chezmoi
Write-Output ">> Applying chezmoi theme"
Start-Sleep -Seconds 1
. "$PSScriptRoot\update-theme.ps1"
Write-Output ">> Setting powershell profile"
Start-Sleep -Seconds 1
New-Item -ItemType Directory -Force ~/Documents
New-Item -ItemType Directory -Force ~/Documents/WindowsPowerShell
cat profile.ps1 | Add-Content -Path ~/Documents/WindowsPowerShell/Microsoft.PowerShell_profile.ps1
