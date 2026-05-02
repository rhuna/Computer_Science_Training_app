@echo off
go run . | findstr /C:"PASS_INCIDENT_POSTMORTEM"
