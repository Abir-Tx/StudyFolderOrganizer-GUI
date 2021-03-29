# Script for creating checksums of the exe files



# Compressing the files to zip
Compress-Archive -Path * -DestinationPath StudyFolderOrganizer.zip


# EXE Files
Write-Output EXE
Write-Output ---------
Get-FileHash .\*.exe
Get-FileHash .\*.exe -Algorithm md5

# Zip Files
Write-Output Zip
Write-Output ---------
Get-FileHash .\*.zip -Algorithm md5
Get-FileHash .\*.zip

Pause
