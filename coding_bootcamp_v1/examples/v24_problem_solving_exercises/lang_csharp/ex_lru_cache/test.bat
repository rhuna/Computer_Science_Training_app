@echo off
dotnet run | findstr /C:"PASS_LRU_CACHE"
