@echo off
dotnet run | findstr /C:"PASS_INCIDENT_POSTMORTEM"
