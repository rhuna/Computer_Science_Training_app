@echo off
dotnet run | findstr /C:"PASS_DOCKER_PLAN"
