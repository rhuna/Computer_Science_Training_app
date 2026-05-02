@echo off
go run . | findstr /C:"PASS_FRONTEND_STATES"
