@echo off
cargo run | findstr /C:"PASS_DOCKER_PLAN"
