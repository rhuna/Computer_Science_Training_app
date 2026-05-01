@echo off
go run . | findstr /C:"PASS_HTTP_CLIENT"
