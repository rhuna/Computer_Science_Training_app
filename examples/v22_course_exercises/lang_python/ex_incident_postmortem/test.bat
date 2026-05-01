@echo off
python main.py | findstr /C:"PASS_INCIDENT_POSTMORTEM"
