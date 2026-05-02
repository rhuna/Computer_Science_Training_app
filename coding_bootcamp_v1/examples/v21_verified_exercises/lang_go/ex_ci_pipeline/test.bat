@echo off
go run . | findstr /C:"PASS_CI_PIPELINE"
