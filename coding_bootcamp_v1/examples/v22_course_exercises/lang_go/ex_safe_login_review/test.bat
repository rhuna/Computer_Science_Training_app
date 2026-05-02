@echo off
go run . | findstr /C:"PASS_SAFE_LOGIN_REVIEW"
