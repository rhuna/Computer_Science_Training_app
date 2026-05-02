@echo off
go run . | findstr /C:"PASS_RELEASE_CHECKLIST"
