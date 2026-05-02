@echo off
cargo run | findstr /C:"PASS_CI_PIPELINE"
