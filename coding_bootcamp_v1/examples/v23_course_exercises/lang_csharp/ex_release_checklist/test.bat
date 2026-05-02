@echo off
dotnet run | findstr /C:"PASS_RELEASE_CHECKLIST"
