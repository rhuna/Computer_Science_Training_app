@echo off
sqlite3 practice.db < queries.sql | findstr /C:"PASS_CI_PIPELINE"
